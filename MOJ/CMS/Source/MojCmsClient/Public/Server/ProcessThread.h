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
class MOJCMSCLIENT_API ProcessThread : public FRunnable
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

	void DefaultSetting(uint8 Sub, uint8 Flag, std::string CastBuffer);
	void LoginSetting(uint8 Sub, std::string CastBuffer);
	void InmateSetting(uint8 Sub, uint8 Flag, std::string CastBuffer);
	void ProgramSetting(uint8 Sub, uint8 Flag, std::string CastBuffer);
	void LogSetting(uint8 Sub, uint8 Flag, std::string CastBuffer);
	void CmsController(uint8 Sub, std::string CastBuffer);

	void MakeThread();
	void StopListen(bool bReset);

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

	FString ToFStringFromANSI(const std::string castBuffer);

#pragma region DefaultBindingDatas

	DefaultSettingBindingData defaultSettingBindingData;

	inline DefaultSettingBindingData::FDefaultSearch* GetFDefaultSearch() { return &defaultSettingBindingData.defaultSearch; }
	inline DefaultSettingBindingData::FDefaultSetting* GetFDefaultSetting() { return &defaultSettingBindingData.defaultSetting; }

#pragma endregion

#pragma region LoginBindingDatas
	LoginSettingBindingData loginSettingBindingData;

	inline LoginSettingBindingData::FManageChangePW* GetFManageChangePW() { return &loginSettingBindingData.manageChangePW; }
	inline LoginSettingBindingData::FManageCheckPW* GetFManageCheckPW() { return &loginSettingBindingData.manageCheckPW; }
	inline LoginSettingBindingData::FInmateLogin* GetFInmateLogin() { return &loginSettingBindingData.inmateLogin; }
#pragma endregion

#pragma region InfoMovieBindingDatas

	InmateSettingBindingData inmateSettingBindingData;

	inline InmateSettingBindingData::FInmateADD* GetFInmateADD() { return &inmateSettingBindingData.inmateADD; }
	inline InmateSettingBindingData::FInmateUpdate* GetFInmateUpdate() { return &inmateSettingBindingData.inmateUpdate; }
	inline InmateSettingBindingData::FInmateSearch* GetFInmateSearch() { return &inmateSettingBindingData.inmateSearch; }

#pragma endregion

#pragma region ProgramBindingDatas

	ProgramSettingBindingData programSettingBindingData;

	inline ProgramSettingBindingData::FProgramUpdate* GetFProgramUpdate() { return &programSettingBindingData.ProgramUpdate; }

#pragma endregion

#pragma region LogBindingDatas

	LogSettingBindingData logSettingBindingData;

	inline LogSettingBindingData::FLogSearch* GetFLogSearch() { return &logSettingBindingData.logSearch; }

#pragma endregion

#pragma region CmsBindingDatas
	CmsBindingData cmsBindingData;

	inline CmsBindingData::FTrackingNumber* GetFTrackingNumber() { return &cmsBindingData.TrackingNumber; }
	inline CmsBindingData::FCmsNextRound* GetFCmsNextRound() { return &cmsBindingData.CmsNextRound; }
	inline CmsBindingData::FTutoEnd* GetFTutoEnd() { return &cmsBindingData.TutoEnd; }
	inline CmsBindingData::FRoundEnd* GetFRoundEnd() { return &cmsBindingData.RoundEnd; }

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
