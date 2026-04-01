// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/SendThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendDataBox.h"
#include "../../Protocols.h"
//#include <sstream>

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

void SendThread::SetMessage(uint8 main, uint8 sub, uint8 type)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage = FString::FromInt(type);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, uint8 type, int count)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(type) + " " + FString::FromInt(count));

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, int guideActorNum, int targetActorNum)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(guideActorNum) + " " + FString::FromInt(targetActorNum));

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, int guideActorNum, int targetActorNum, int IsFirstSetting)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(guideActorNum) + " " + FString::FromInt(targetActorNum) + " " + FString::FromInt(IsFirstSetting));

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, int FishNum, FTransform CurrentTransform)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(FishNum) +
		" " + FString::SanitizeFloat(CurrentTransform.GetLocation().X) + " " + FString::SanitizeFloat(CurrentTransform.GetLocation().Y) + " " + FString::SanitizeFloat(CurrentTransform.GetLocation().Z) +
		" " + FString::SanitizeFloat(CurrentTransform.GetRotation().Rotator().Roll) + " " + FString::SanitizeFloat(CurrentTransform.GetRotation().Rotator().Pitch) + " " + FString::SanitizeFloat(CurrentTransform.GetRotation().Rotator().Yaw) +
		" " + FString::SanitizeFloat(CurrentTransform.GetScale3D().X) + " " + FString::SanitizeFloat(CurrentTransform.GetScale3D().Y) + " " + FString::SanitizeFloat(CurrentTransform.GetScale3D().Z));

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}