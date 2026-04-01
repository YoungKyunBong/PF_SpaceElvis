// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include <sstream>

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

/**
 * 
 */
class MOJCMSCLIENT_API RecvThread : public FRunnable
{
public:
private:
	FRunnableThread* Thread;
	bool bRun;
	FThreadSafeCounter StopTaskCounter;
	bool IsSpawn;
	mutable FCriticalSection DataGuard;

public:
	RecvThread();
	~RecvThread();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	bool RecvMessage();

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

	void MakeThread();
	void StopListen(bool bReset);
private:
	static RecvThread* Instance;

public:
	static RecvThread* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new RecvThread();
		}
		return Instance;
	}

	static void Destroy()
	{
		SAFE_DELETE(Instance);
	}
};
