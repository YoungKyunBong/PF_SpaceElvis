// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include "stringapiset.h"
#include <sstream>

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

/**
 * 
 */
class MOJMOVIECLIENT_API ProcessThread : public FRunnable
{
private:
	FRunnableThread* Thread;
	bool bRun;
	FThreadSafeCounter StopTaskCounter;

	FString ListData;

public:
	bool IsSpawn;

	ProcessThread();
	~ProcessThread();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	void ProgramSetting(uint8 Sub, std::string CastBuffer);
	void CmsController(uint8 Sub, std::string CastBuffer);

	void MakeThread();
	void StopListen(bool bReset);

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

	FString ToFStringFromANSI(const char* payload, int len, UINT codepage = CP_ACP /*=949*/)
	{
		int wlen = MultiByteToWideChar(codepage, 0, payload, len, nullptr, 0);
		FString out;
		out.GetCharArray().SetNumUninitialized(wlen + 1);
		MultiByteToWideChar(codepage, 0, payload, len, out.GetCharArray().GetData(), wlen);
		out.GetCharArray()[wlen] = 0;
		return out;
	}

#pragma region ProgramBindingDatas

	ProgramSettingBindingData programSettingBindingData;

	inline ProgramSettingBindingData::FRequestMovieNum* GetFRequestMovieNum() { return &programSettingBindingData.RequestMovieNum; }

#pragma endregion

#pragma region CmsBindingDatas
	CmsBindingData cmsBindingData;

	inline CmsBindingData::FCmsControllerStart* GetFCmsControllerStart() { return &cmsBindingData.CmsControllerStart; }
	inline CmsBindingData::FCmsControllerPlay* GetFCmsControllerPlay() { return &cmsBindingData.CmsControllerPlay; }
	inline CmsBindingData::FCmsControllerStop* GetFCmsControllerStop() { return &cmsBindingData.CmsControllerStop; }
	inline CmsBindingData::FCmsControllerPause* GetFCmsControllerPause() { return &cmsBindingData.CmsControllerPause; }

	inline CmsBindingData::FCmsMovieNum* GetFCmsMovieNum() { return &cmsBindingData.CmsMovieNum; }
	inline CmsBindingData::FCmsNextRound* GetFCmsNextRound() { return &cmsBindingData.CmsNextRound; }

#pragma endregion

private:
	static ProcessThread* Instance;

public:
	static ProcessThread* GetInst()
	{
		if (Instance == NULL)
		{
			Instance = new ProcessThread();
		}
		return Instance;
	}

	static void Destroy()
	{
		SAFE_DELETE(Instance);
	}
};
