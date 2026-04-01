// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

#pragma region InfoMovieBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvMovieLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE(FRecvInfoMovieEnd);
#pragma endregion

#pragma region CleaningOceanBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCleaningLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvWallSpawnWhale, SIDE_TYPE);
DECLARE_MULTICAST_DELEGATE(FRecvChangeWhaleDirection);
DECLARE_MULTICAST_DELEGATE(FRecvWallSpawnWhaleEnd);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvPlayWhaleSound, WHALE_SOUND_DISTANCE_TYPE);
DECLARE_MULTICAST_DELEGATE_TwoParams(FRecvFloorSpawnWhale, SIDE_TYPE, bool);
DECLARE_MULTICAST_DELEGATE(FRecvCleaningOceanEnd);
#pragma endregion

#pragma region CoralForestBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCoralLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCoralOverlap, CORAL_TYPE)
DECLARE_MULTICAST_DELEGATE(FRecvCoralWhiteSwitch);
DECLARE_MULTICAST_DELEGATE(FRecvCoralEnd);
#pragma endregion

#pragma region KelpForestBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvKelpLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvOilCount, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvOilOverlap, int32);
DECLARE_MULTICAST_DELEGATE(FRecvKelpLevelPlaySequence);
DECLARE_MULTICAST_DELEGATE(FRecvOilEnd);
#pragma endregion

#pragma region OceanVillageBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvOceanVillageLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FRecvGuideActorTargetChange, int, int);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FRecvFishActorTargetChange, int, int, bool);
DECLARE_MULTICAST_DELEGATE_TwoParams(FRecvFishActorTransform, int, FTransform);
#pragma endregion

#pragma region CamouFishBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCamouFlageFishLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE(FRecvCamouFishEnd);
#pragma endregion

#pragma region LuminaryFishBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvLuminaryFishLevelLoadingEnd, bool);
DECLARE_MULTICAST_DELEGATE(FRecvLumiFishEnd);
#pragma endregion

#pragma region CmsBindingDatas
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerStart);
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerStop);
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerSkip);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCmsControllerReset, RESET_TYPE);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCmsControllerNewPlayer, FString);
#pragma endregion

#pragma region PlayEffectSoundBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvPlayEffectSound, EFFECT_SOUND_TYPE);
#pragma endregion

#pragma region LoadBindingDatas
DECLARE_MULTICAST_DELEGATE(FRecvLoadPNG);
#pragma endregion

#pragma region ChangeEnvBindingDatas
DECLARE_MULTICAST_DELEGATE(FRecvOceanCleanChange);
DECLARE_MULTICAST_DELEGATE(FRecvPlayTimeOutEvent);
#pragma endregion
/**
 * 
 */

UCLASS()
class FUTUREOCEAN_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
private:
	FString ServerIP;

	void FileLoadIP();

	SIDE_TYPE curr_WhaleSpawnSideType;
	uint8 placeType = 255;
	uint8 nodeType = 255;

	bool SetSceneTypeOnce = true;

protected:
	UPROPERTY(EditAnyWhere)
	bool IsLocalGame;

	UPROPERTY(EditAnyWhere)
	bool IsTestGame;

	virtual void Init() override;
	virtual void Shutdown();

public:
	UFUNCTION(BlueprintCallable)
	void CheckSceneType(bool isWall, ClientNodeType ClientNodeType);

	UFUNCTION(BlueprintCallable)
	void Send_SetSceneType(bool isWall, ClientNodeType ClientNodeType);

	SIDE_TYPE GetCurrSideType() { return curr_WhaleSpawnSideType; }

	inline PROTOCOLSUB_TYPE GetPlaceType() { return  PROTOCOLSUB_TYPE(placeType);}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline ClientNodeType GetNodeType() { return ClientNodeType(nodeType); }

	inline bool GetIsLocalGame() { return IsLocalGame; }

	inline bool GetIsTestGame() { return IsTestGame; }

#pragma region InfoMovieBindingDatas

	FRecvMovieLevelLoadingEnd RecvMovieLevelLoadingEnd;
	FRecvInfoMovieEnd RecvInfoMovieEnd;

	UFUNCTION()
	inline void Fuc_RecvMovieLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvInfoMovieEnd();

	inline void Send_MovieLevelLoadingEnd();
	inline void Send_ChangeScript(PROTOCOLSUB_CMS scriptType);
	inline void Send_InfoMovieEnd();
#pragma endregion

#pragma region CleaningOceanBindingDatas

	FRecvCleaningLevelLoadingEnd RecvCleaningLevelLoadingEnd;
	FRecvWallSpawnWhale RecvWallSpawnWhale;
	FRecvChangeWhaleDirection RecvChangeWhaleDirection;
	FRecvWallSpawnWhaleEnd RecvWallSpawnWhaleEnd;
	FRecvPlayWhaleSound RecvPlayWhaleSound;
	FRecvFloorSpawnWhale RecvFloorSpawnWhale;
	FRecvCleaningOceanEnd RecvCleaningOceanEnd;

	UFUNCTION()
	inline void Fuc_RecvCleaningLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvWallSpawnWhale(SIDE_TYPE type);
	UFUNCTION()
	inline void Fuc_RecvChangeWhaleDirection();
	UFUNCTION()
	inline void Fuc_RecvWallSpawnWhaleEnd();
	UFUNCTION()
	inline void Fuc_RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE type); // Floor
	UFUNCTION()
	inline void Fuc_RecvFloorSpawnWhale(SIDE_TYPE type, bool IsSuccess); // Floor
	UFUNCTION()
	inline void Fuc_RecvCleaningOceanEnd();

	void Send_CleaningLevelLoadingEnd();
	inline void Send_WallSpawnWhale(int count); // Floor -> Wall
	inline void Send_ChangeWhaleDirection();
	inline void Send_WallSpawnWhaleEnd();
	inline void Send_PlayWhaleSound();
	inline void Send_FloorSpawnWhale(); // Wall -> Floor
	inline void Send_CleaningOceanEnd();

#pragma endregion

#pragma region CoralForestBindingDatas
	
	FRecvCoralLevelLoadingEnd RecvCoralLevelLoadingEnd;
	FRecvCoralOverlap RecvCoralOverlap;
	FRecvCoralWhiteSwitch RecvCoralWhiteSwitch;
	FRecvCoralEnd RecvCoralEnd;

	UFUNCTION()
	inline void Fuc_RecvCoralLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvCoralOverlap(CORAL_TYPE coralType);
	UFUNCTION()
	inline void Fuc_RecvCoralWhiteSwitch();
	UFUNCTION()
	inline void Fuc_RecvCoralEnd();

	void Send_CoralLevelLoadingEnd();
	inline void Send_CoralOverlap(CORAL_TYPE coralType);
	inline void Send_CoralWhiteSwitch();
	inline void Send_CoralEnd();

#pragma endregion

#pragma region KelpForestBindingDatas

	FRecvKelpLevelLoadingEnd RecvKelpLevelLoadingEnd;
	FRecvOilCount RecvOilCount;
	FRecvOilOverlap RecvOilOverlap;
	FRecvKelpLevelPlaySequence RecvKelpLevelPlaySequence;
	FRecvOilEnd RecvOilEnd;

	UFUNCTION()
	inline void Fuc_RecvKelpLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvOilCount(int32 count);
	UFUNCTION()
	inline void Fuc_RecvOilOverlap(int32 cnt);
	UFUNCTION()
	inline void Fuc_RecvKelpLevelPlaySequence();
	UFUNCTION()
	inline void Fuc_RecvOilEnd();

	void Send_KelpLevelLoadingEnd();
	inline void Send_OilCount(int32 count);
	inline void Send_OilOverlap(int32 cnt);
	inline void Send_KelpLevelPlaySequence();
	inline void Send_OilEnd();

#pragma endregion

#pragma region OceanVillageBindingDatas
	FRecvOceanVillageLevelLoadingEnd RecvOceanVillageLevelLoadingEnd;
	FRecvGuideActorTargetChange RecvGuideActorTargetChange;
	FRecvFishActorTargetChange RecvFishActorTargetChange;
	FRecvFishActorTransform RecvFishActorTransform;

	UFUNCTION()
	inline void Fuc_RecvOceanVillageLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvGuideActorTargetChange(int guideActorNum, int targetActorNum);
	UFUNCTION()
	inline void Fuc_RecvFishActorTargetChange(int fishActorNum, int guideActorNum, bool IsFirst);
	UFUNCTION()
	inline void Fuc_RecvFishActorTransform(int fishActorNum, FTransform transform);

	void Send_OceanVillageLevelLoadingEnd();
	void Send_GuideActorTargetChange(int guideActorNum, int targetActorNum);
	void Send_FishActorTargetChange(int fishActorNum, int guideActorNum, bool IsFirstSetting);
	void Send_FishActorTransform(int fishActorNum, FTransform tranform);
#pragma endregion

#pragma region CamouFishBindingDatas
	FRecvCamouFlageFishLevelLoadingEnd RecvCamouFlageFishLevelLoadingEnd;
	FRecvCamouFishEnd RecvCamouFishEnd;

	UFUNCTION()
	inline void Fuc_RecvCamouFlageFishLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvCamouFishEnd();

	void Send_CamouFlageFishLevelLoadingEnd();
	void Send_CamouFlageFishCount(int count);
	inline void Send_CamouFishFind();
#pragma endregion

#pragma region LuminaryFishBindingDatas
	FRecvLuminaryFishLevelLoadingEnd RecvLuminaryFishLevelLoadingEnd;
	FRecvLumiFishEnd RecvLumiFishEnd;

	UFUNCTION()
	inline void Fuc_RecvLuminaryFishLevelLoadingEnd(bool isA);
	UFUNCTION()
	inline void Fuc_RecvLumiFishEnd();

	void Send_LuminaryFishLevelLoadingEnd();
	void Send_LuminaryFishCount(int count);
	inline void Send_LumiFishFind();
#pragma endregion

#pragma region CmsBindingDatas
	FRecvCmsControllerStart RecvCmsControllerStart;
	FRecvCmsControllerStop RecvCmsControllerStop;
	FRecvCmsControllerSkip RecvCmsControllerSkip;
	FRecvCmsControllerReset RecvCmsControllerReset;
	FRecvCmsControllerNewPlayer RecvCmsControllerNewPlayer;
	
	UFUNCTION()
	inline void Fuc_RecvCmsControllerStart();
	UFUNCTION()
	inline void Fuc_RecvCmsControllerStop();
	UFUNCTION()
	inline void Fuc_RecvCmsControllerSkip();
	UFUNCTION()
	inline void Fuc_RecvCmsControllerReset(RESET_TYPE type);
	UFUNCTION()
	void Fuc_RecvCmsControllerNewPlayer(FString _levelName);

	//>>--------------------------------------------------------- CMS 테스트 부분

	void Send_CmsControllerStart();
	void Send_CmsControllerStop();
	void Send_CmsControllerSkip();
	void Send_CmsControllerReset(RESET_TYPE type);
	void Send_TempBG_Wall();
	void Send_TempBG_Floor();

	//<<---------------------------------------------------------
#pragma endregion

#pragma region PlayEffectSoundBindingDatas
	FRecvPlayEffectSound RecvPlayEffectSound;

	UFUNCTION()
	inline void Fuc_RecvPlayEffectSound(EFFECT_SOUND_TYPE _type);

	void Send_PlayEffectSound(EFFECT_SOUND_TYPE _type);
#pragma endregion

#pragma region LoadBindingDatas
	FRecvLoadPNG RecvLoadPNG;

	UFUNCTION()
	inline void Fuc_RecvLoadPNG();

	void Send_LoadPNG();
#pragma endregion

#pragma region ChangeEnvBindingDatas
	FRecvOceanCleanChange RecvOceanCleanChange;
	FRecvPlayTimeOutEvent RecvPlayTimeOutEvent;

	UFUNCTION()
	inline void Fuc_RecvOceanCleanChange();

	UFUNCTION()
	inline void Fuc_RecvPlayTimeOutEvent();


	void Send_OceanCleanChange();
	inline void Send_PlayTimeOutEvent();
#pragma endregion
};
