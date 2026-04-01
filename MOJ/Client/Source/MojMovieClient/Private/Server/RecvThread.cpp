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
			RecvMessage();
			if (!SocketManager::GetInst()->IsConnected())
			{
				SocketManager::GetInst()->RecvMessageCount = 0;
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
	uint32 BufferSize = 0;
	TArray<uint8> ReceiveBuffer;

	int32 Recv = 0;
	PACKET recvPacket;

	if (SocketManager::GetInst()->ConnectionSocket != nullptr && bRun)
	{
		if (!SocketManager::GetInst()->IsEnd)
		{
			ReceiveBuffer.SetNumUninitialized(BufferSize);

			SocketManager::GetInst()->ConnectionSocket->Recv(reinterpret_cast<uint8*>(&recvPacket), MAX_BUFFER, Recv);

			if (Recv != 0)
			{
				RecvDataBox::GetInst()->Data_Enqueue(recvPacket);
			}
		}
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
