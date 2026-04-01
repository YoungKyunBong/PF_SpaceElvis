// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/RecvThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/RecvDataBox.h"
#include "../../Protocols.h"

RecvThread* RecvThread::Instance = nullptr;

RecvThread::RecvThread()
{
	Thread = nullptr;
	bRun = true;
	IsSpawn = false;
}

RecvThread::~RecvThread()
{
}

bool RecvThread::Init()
{
	return true;
}

uint32 RecvThread::Run()
{
	while (StopTaskCounter.GetValue() == 0 && bRun)
	{
		if (SocketManager::GetInst() != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" RecvThread")); // 화면출력
			if (!RecvMessage())
			{
				// 수신 실패 시 연결 상태 확인
				if (!SocketManager::GetInst()->IsConnected())
				{
					SocketManager::GetInst()->RecvMessageCount = 0;
				}

				// 연결이 끊어진 경우 재연결 대기
				FPlatformProcess::Sleep(0.1f);
			}
		}
		else
		{
			break;
		}
	}
	return 0;
}

void RecvThread::Stop()
{
	StopTaskCounter.Increment();
	bRun = false;
}

bool RecvThread::RecvMessage()
{
	int32 Recv = 0;
	PACKET recvPacket;
	FMemory::Memzero(&recvPacket, sizeof(PACKET));

	if (SocketManager::GetInst()->ConnectionSocket != nullptr && bRun)
	{
		if (!SocketManager::GetInst()->IsEnd)
		{
			uint8* PacketPtr = reinterpret_cast<uint8*>(&recvPacket);
			int32 TotalReceived = 0;

			// 서버가 send()하는 크기와 동일하게 고정 블로킹 수신
			// 서버 SendMsg: send(sock, buf, BUFSIZE, 0) → 항상 2048바이트 전송
			// Main(1) + Sub(1) + Flag(1) + Buffer(2045) = 2048바이트
			const int32 ServerSendSize = 2048;

			while (TotalReceived < ServerSendSize)
			{
				Recv = 0;
				if (!SocketManager::GetInst()->ConnectionSocket->Recv(
					PacketPtr + TotalReceived,
					ServerSendSize - TotalReceived,
					Recv))
				{
					return false;
				}

				if (Recv <= 0)
				{
					return false;
				}

				TotalReceived += Recv;
			}

			RecvDataBox::GetInst()->Data_Enqueue(recvPacket);
		}

		FPlatformProcess::Sleep(0.01f);
	}
	else
	{
		return false;
	}

	return true;
}

void RecvThread::MakeThread()
{
	if (Thread != nullptr && Thread->GetThreadName().Contains("RecvThread"))
	{
		bRun = true;
	}
	else
	{
		Thread = FRunnableThread::Create(this, TEXT("RecvThread"), 0, TPri_BelowNormal);
		bRun = (nullptr != Thread);
	}

	SocketManager::GetInst()->bRecvConnected = true;
}

void RecvThread::StopListen(bool bReset)
{
	if (!bReset)
	{
		Stop();
		if (Thread != nullptr)
		{
			Thread->WaitForCompletion();
		}
		delete Instance;
		Instance = NULL;
		RecvDataBox::GetInst()->ClearQueue();
	}
}
