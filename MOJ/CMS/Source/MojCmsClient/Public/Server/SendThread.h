// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include <sstream>

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

/**
 * 
 */
class MOJCMSCLIENT_API SendThread : public FRunnable
{
private:
	FRunnableThread* Thread;
	bool bRun;
	FThreadSafeCounter StopTaskCounter;
	FString sendMessage;

	//bool IsAnim;

	uint8 Send_MainProtocol;
	uint8 Send_SubProtocol;

public:
	SendThread();
	~SendThread();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

	inline std::string ToStdStringFromANSI(const FString& src, int codepage = 0 /*=949*/);

	void BuildTextPacket(PACKET& out, const FString& Text);

	void MakeThread();
	void StopListen(bool bReset);

	void SetMessage(uint8 main, uint8 sub, int none = -1);
	void SetMessage(uint8 main, uint8 sub, FText test);
	void SetMessage(uint8 main, uint8 sub, FString num);
	void SetMessage(uint8 main, uint8 sub, FString text1, FString text2);
	void SetMessage(uint8 main, uint8 sub, int type, FString prisonerNum, FString data);

private:
	static SendThread* Instance;

public:
	static SendThread* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new SendThread();
		}
		return Instance;
	}

	static void Destroy()
	{
		SAFE_DELETE(Instance);
	}
};
