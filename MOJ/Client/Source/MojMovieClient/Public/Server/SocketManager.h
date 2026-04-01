// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include <sstream>

#define SERVERIP "192.168.0.46"

//#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 256
#define SEND 1
#define RECV 0
/**
 * 
 */
class MOJMOVIECLIENT_API SocketManager
{
public:
	FSocket* ConnectionSocket;
	bool bRecvConnected;
	bool bSendConnected;
	int RecvMessageCount;
	int SendMessageCount;
	bool IsSend;
	bool IsSpawn;
	bool IsEnd;

	FString sendMessage;

	SocketManager();
	~SocketManager();

	void Init(FString ServerIP);

	void Connect(FString ServerIP);
	bool IsConnected();

	//void SendMessage(PACKET data);

	bool QuitConnection();

	inline FSocket* getSocket() { return ConnectionSocket; }

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

	inline bool GetIsSpawn() { return IsSpawn; }

private:
	static SocketManager* Instance;

public:
	static SocketManager* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new SocketManager();
		}
		return Instance;
	}
};
