// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include "stringapiset.h"
#include <sstream>

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

/**
 * 
 */
class MOJMOVIECLIENT_API SendThread : public FRunnable
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

	inline std::string ToStdStringFromANSI(const FString& src, UINT codepage = CP_ACP /*=949*/)
	{
		if (src.IsEmpty()) return {};

		const wchar_t* w = src.GetCharArray().GetData();   // = *src 와 동일(널 포함)
		const int      n = src.Len();                      // 널 제외한 길이

		// 1) 필요한 바이트 수
		const int need = ::WideCharToMultiByte(codepage, 0, w, n, nullptr, 0, nullptr, nullptr);
		std::string out;
		out.resize(FMath::Max(need, 0));

		// 2) 실제 변환 (널 미포함)
		if (need > 0)
			::WideCharToMultiByte(codepage, 0, w, n, out.data(), need, nullptr, nullptr);

		return out;
	}

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
