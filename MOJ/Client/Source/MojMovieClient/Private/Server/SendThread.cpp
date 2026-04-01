// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/SendThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendDataBox.h"
#include "../../Protocols.h"
#include "Containers/StringConv.h"

SendThread* SendThread::Instance = nullptr;

SendThread::SendThread()
{
	Thread = nullptr;
	bRun = true;
	sendMessage.Empty();
}

SendThread::~SendThread()
{
}

bool SendThread::Init()
{
	return true;
}

uint32 SendThread::Run()
{
	while (StopTaskCounter.GetValue() == 0 && bRun)
	{
		if (SocketManager::GetInst() != nullptr)
		{
			PACKET data;
			if (SendDataBox::GetInst()->Data_DeQueue(data))
			{
				int32 sent;

				UE_LOG(LogTemp, Warning, TEXT("SendCheck"));

				UE_LOG(LogTemp, Warning, TEXT("SendData             Data : %s"), *StringToFString(std::string(data.Buffer).c_str()));

				SocketManager::GetInst()->getSocket()->Send(reinterpret_cast<const uint8*>(&data), MAX_BUFFER, sent);
			}

			if (!SocketManager::GetInst()->IsConnected())
			{
				SocketManager::GetInst()->SendMessageCount = 0;
			}
		}
		else
			break;
	}
	return 0;
}

void SendThread::Stop()
{
	StopTaskCounter.Increment();
	bRun = false;
}

void SendThread::MakeThread()
{
	if (Thread != nullptr && Thread->GetThreadName().Contains("SendThread"))
	{
		bRun = true;
	}
	else
	{
		Thread = FRunnableThread::Create(this, TEXT("SendThread"), 0, TPri_BelowNormal);
		bRun = (nullptr != Thread);
	}

	SocketManager::GetInst()->bSendConnected = true;
}

void SendThread::StopListen(bool bReset)
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
		SendDataBox::GetInst()->ClearQueue();
	}
}

void SendThread::SetMessage(uint8 main, uint8 sub, int none)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage = FString::FromInt(none);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FText test)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(test.ToString());

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FString num)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(num);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FString text1, FString text2)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(text1 + " " + text2);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, int type, FString prisonerNum, FString data)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(type) + " " + prisonerNum + " " + data);

	strcpy(sendPacket.Buffer, ToStdStringFromANSI(sendMessage).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}
