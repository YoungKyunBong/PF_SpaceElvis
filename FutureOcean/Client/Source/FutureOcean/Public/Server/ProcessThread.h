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
class FUTUREOCEAN_API ProcessThread : public FRunnable
{
private:
	FRunnableThread* Thread;
	bool bRun;
	FThreadSafeCounter StopTaskCounter;

public:
	bool IsSpawn;

	ProcessThread();
	~ProcessThread();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	//bool ProcessMessage();

	void InfoMovie(uint8 Sub, std::string CastBuffer);
	void CleaningOcean(uint8 Sub, std::string CastBuffer);
	void CoralForest(uint8 Sub, std::string CastBuffer);
	void KelpForest(uint8 Sub, std::string CastBuffer);
	void OceanVillage(uint8 Sub, std::string CastBuffer);
	void CamouFlageFish(uint8 Sub, std::string CastBuffer);
	void LuminaryFish(uint8 Sub, std::string CastBuffer);
	void PlayEffectSound(uint8 Sub, std::string CastBuffer);
	void ChangeEnv(uint8 Sub, std::string CastBuffer);
	void LoadData(uint8 Sub, std::string CastBuffer);
	void CmsController(uint8 Sub, std::string CastBuffer);

	inline FString StringToFString(std::string s) { return FString(UTF8_TO_TCHAR(s.c_str())); }

#pragma region InfoMovieBindingDatas
	InfoMovieBindingData infoMovieBindingData;

	inline InfoMovieBindingData::FMovieLevelLoadingEnd* GetFMovieLevelLoadingEnd() { return &infoMovieBindingData.movieLevelLoadingEnd; }
	inline InfoMovieBindingData::FInfoMovieEnd* GetFInfoMovieEnd() { return &infoMovieBindingData.infoMovieEnd; }
#pragma endregion

#pragma region CleaningOceanBindingDatas
	CleaningOceanBindingData cleaningOceanBindingData;

	inline CleaningOceanBindingData::FCleaningLevelLoadingEnd* GetFCleaningLevelLoadingEnd() { return &cleaningOceanBindingData.cleaningLevelLoadingEnd; }
	inline CleaningOceanBindingData::FWallSpawnWhale * GetFWallSpawnWhale() { return &cleaningOceanBindingData.wallSpawnWhale; }
	inline CleaningOceanBindingData::FChangeWhaleDirection* GetFChangeWhaleDirection() { return &cleaningOceanBindingData.changeWhaleDirection; }
	inline CleaningOceanBindingData::FWallSpawnWhaleEnd * GetFWallSpawnWhaleEnd() { return &cleaningOceanBindingData.wallSpawnWhaleEnd; }
	inline CleaningOceanBindingData::FPlayWhaleSound * GetFPlayWhaleSound() { return &cleaningOceanBindingData.playWhaleSound; }
	inline CleaningOceanBindingData::FFloorSpawnWhale * GetFFloorSpawnWhale() { return &cleaningOceanBindingData.floorSpawnWhale; }
	inline CleaningOceanBindingData::FCleaningOceanEnd * GetFCleaningOceanEnd() { return &cleaningOceanBindingData.cleaningOceanEnd; }
#pragma endregion

#pragma region CoralForestBindingDatas
	CoralForestBindingData coralForestBindingData;
	
	inline CoralForestBindingData::FCoralLevelLoadingEnd* GetFCoralLevelLoadingEnd() { return &coralForestBindingData.coralLevelLoadingEnd; }
	inline CoralForestBindingData::FCoralOverlap* GetFCoralOverlap() { return &coralForestBindingData.coralOverlap; }
	inline CoralForestBindingData::FCoralWhiteSwitch* GetFCoralWhiteSwitch() { return &coralForestBindingData.coralWhiteSwitch; }
	inline CoralForestBindingData::FCoralEnd* GetFCoralEnd() { return &coralForestBindingData.coralEnd; }
#pragma endregion

#pragma region KelpForestBindingDatas
	KelpForestBindingData kelpForestBindingData;

	inline KelpForestBindingData::FKelpLevelLoadingEnd* GetFKelpLevelLoadingEnd() { return &kelpForestBindingData.kelpLevelLoadingEnd; }
	inline KelpForestBindingData::FOilCount* GetFOilCount() { return &kelpForestBindingData.OilCount; }
	inline KelpForestBindingData::FOilOverlap* GetFOilOverlap() { return &kelpForestBindingData.OilOverlap; }
	inline KelpForestBindingData::FKelpLevelPlaySequence* GetFKelpLevelPlaySequence() { return &kelpForestBindingData.KelpLevelPlaySequence; }
	inline KelpForestBindingData::FOilEnd* GetFOilEnd() { return &kelpForestBindingData.OilEnd; }
#pragma endregion

#pragma region OceanVillageBindingDatas
	OceanVillageBindingData oceanVillageBindingData;

	inline OceanVillageBindingData::FOceanVillageLevelLoadingEnd* GetFOceanVillageLevelLoadingEnd() { return &oceanVillageBindingData.oceanVillageLevelLoadingEnd; }
	inline OceanVillageBindingData::FGuideActorTargetChange* GetFGuideActorTargetChange() { return &oceanVillageBindingData.guideActorTargetChange; }
	inline OceanVillageBindingData::FFishActorTargetChange* GetFFishActorTargetChange() { return &oceanVillageBindingData.fishActorTargetChange; }
	inline OceanVillageBindingData::FFishTransform* GetFFishActorTransform() { return &oceanVillageBindingData.fishTransform; }
#pragma endregion

#pragma region CamouFishBindingDatas
	CamouFishBindingData camouFishBindingData;

	inline CamouFishBindingData::FCamouFlageFishLevelLoadingEnd* GetFCamouFlageFishLevelLoadingEnd() { return &camouFishBindingData.camouFlageFishLevelLoadingEnd; }
	//inline CamouFishBindingData::FCamouFlageFishCount* GetFCamouFlageFishCount() { return &camouFishBindingData.camouFlageFishCount; }
	//inline CamouFishBindingData::FCamouFishFind* GetFCamouFishFind() { return &camouFishBindingData.camouFishFind; }
	inline CamouFishBindingData::FCamouFishEnd* GetFCamouFishEnd() { return &camouFishBindingData.camouFishEnd; }
#pragma endregion

#pragma region LuminaryFishBindingDatas
	LuminaryFishBindingData luminaryFishBindingData;

	inline LuminaryFishBindingData::FLuminaryFishLevelLoadingEnd* GetFLuminaryFishLevelLoadingEnd() { return &luminaryFishBindingData.luminaryFishLevelLoadingEnd; }
	inline LuminaryFishBindingData::FLumiFishEnd* GetFLumiFishEnd() { return &luminaryFishBindingData.lumiFishEnd; }
#pragma endregion

#pragma region CmsBindingDatas
	CmsBindingData cmsBindingData;

	inline CmsBindingData::FCmsControllerStart* GetFCmsControllerStart() { return &cmsBindingData.CmsControllerStart; }
	inline CmsBindingData::FCmsControllerStop* GetFCmsControllerStop() { return &cmsBindingData.CmsControllerStop; }
	inline CmsBindingData::FCmsControllerSkip* GetFCmsControllerSkip() { return &cmsBindingData.CmsControllerSkip; }
	inline CmsBindingData::FCmsControllerReset* GetFCmsControllerReset() { return &cmsBindingData.CmsControllerReset; }
	inline CmsBindingData::FCmsControllerNewPlayer* GetFCmsControllerNewPlayer() { return &cmsBindingData.CmsControllerNewPlayer; }
#pragma endregion

#pragma region PlayEffectSoundBindingDatas
	PlayEffectSoundBindingData playEffectSoundBindingData;

	inline PlayEffectSoundBindingData::FPlayEffectSound* GetFPlayEffectSound() { return &playEffectSoundBindingData.PlayEffectSound; }
#pragma endregion

#pragma region LoadBindingDatas
	LoadBindingData loadBindingData;

	inline LoadBindingData::FLoadPNG* GetFLoadPNG() { return &loadBindingData.LoadPNG; }
#pragma endregion

#pragma region ChangeEnvBindingDatas
	ChangeEnvBindingData changeEnvBindingData;

	inline ChangeEnvBindingData::FOceanCleanChange* GetFOceanCleanChange() { return &changeEnvBindingData.OceanCleanChange; }
	inline ChangeEnvBindingData::FPlayTimeOutEvent* GetFPlayTimeOutEvent() { return &changeEnvBindingData.PlayTimeOutEvent; }
#pragma endregion

	void MakeThread();
	void StopListen(bool bReset);

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
