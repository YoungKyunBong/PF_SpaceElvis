// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/SocketManager.h"

SocketManager* SocketManager::Instance = nullptr;

SocketManager::SocketManager()
{
	ConnectionSocket = nullptr;
	RecvMessageCount = 0;
	IsSend = RECV;
	IsSpawn = false;
	IsEnd = false;
}

SocketManager::~SocketManager()
{
}

void SocketManager::Init(FString ServerIP)
{
	Connect(ServerIP);
}

void SocketManager::Connect(FString ServerIP)
{
	if (ConnectionSocket == nullptr)
	{
		ConnectionSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, "ConnectionSocket", false);
		if (ConnectionSocket == NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fail Create Socket")));
			return;
		}

		FIPv4Address ip;
		FIPv4Address::Parse(ServerIP, ip);

		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);
		addr->SetPort(SERVERPORT);

		if (!(*addr).IsValid())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fail Create Addr")));
			return;
		}

		if (bool isConnet = !ConnectionSocket->Connect(*addr))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fail Connet")));
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Success Create Socket")));
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Already Socket")));
}

bool SocketManager::IsConnected()
{
	if (RecvMessageCount <= 5 || SendMessageCount <= 5)
		return false;

	return true;
}

//void SocketManager::SendMessage(PACKET data)
//{
//	int32 sent;
//
//	ConnectionSocket->Send(reinterpret_cast<const uint8*>(&data), sizeof(PACKET), sent);
//
//	IsSend = SEND;
//}

bool SocketManager::QuitConnection()
{
	if (!bRecvConnected || !bSendConnected)
		return false;

	IsEnd = true;

	if (ConnectionSocket != nullptr)
	{
		RecvMessageCount = 0;
		SendMessageCount = 0;

		ConnectionSocket->Close();
	}
	delete ConnectionSocket;
	ConnectionSocket = nullptr;

	bRecvConnected = false;
	bSendConnected = false;

	delete Instance;
	Instance = NULL;

	return true;
}
