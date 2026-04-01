// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <sstream>
#include "Runtime/Core/Public/HAL/Runnable.h"

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

/**
 * 
 */
class FUTUREOCEAN_API SendThread : public FRunnable
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

	void MakeThread();
	void StopListen(bool bReset);

	void SetMessage(uint8 main, uint8 sub, int none = -1);
	void SetMessage(uint8 main, uint8 sub, uint8 type);
	void SetMessage(uint8 main, uint8 sub, uint8 type, int count);
	void SetMessage(uint8 main, uint8 sub, int guideActorNum, int targetActorNum);
	void SetMessage(uint8 main, uint8 sub, int guideActorNum, int targetActorNum, int IsFirstSetting);
	void SetMessage(uint8 main, uint8 sub, int FishNum, FTransform CurrentTransform);
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
