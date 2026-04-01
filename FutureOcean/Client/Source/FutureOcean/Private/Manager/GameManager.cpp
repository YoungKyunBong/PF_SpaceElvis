// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GameManager.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendThread.h"
#include "../../Public/Server/RecvThread.h"
#include "../../Public/Server/ProcessThread.h"
#include "Misc/FileHelper.h"

void UGameManager::FileLoadIP()
{
	FString SaveDirectory = *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString FileName = FString("ServerIP") + FString(".txt");
	FString FolderName = FString("LoadFile");
	FString AbsoluteFilePath_2 = SaveDirectory + FolderName;

	TArray<FString> TempArrayName;
	TempArrayName.Empty();
	TArray<FString> TempTextName;
	TempTextName.Empty();

	FString AbsoluteFilePath = AbsoluteFilePath_2 + "/" + FileName;

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsoluteFilePath))
	{
		FFileHelper::LoadFileToStringArray(TempArrayName, *AbsoluteFilePath);

		TempTextName = TArray<FString>(TempArrayName);

		if (TempArrayName.Num() != 0)
		{
			ServerIP = TempArrayName[0];
		}
	}
}

void UGameManager::Init()
{
	Super::Init();

	if (IsLocalGame)return;
	FileLoadIP();
	SocketManager::GetInst()->Init(ServerIP);

	RecvThread::GetInst()->MakeThread();
	SendThread::GetInst()->MakeThread();
	ProcessThread::GetInst()->MakeThread();

#pragma region InfoMovieBindingDatas

	ProcessThread::GetInst()->GetFMovieLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvMovieLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFInfoMovieEnd()->AddUFunction(this, FName("Fuc_RecvInfoMovieEnd"));

#pragma endregion

#pragma region CleaningOceanBindingDatas

	ProcessThread::GetInst()->GetFCleaningLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvCleaningLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFWallSpawnWhale()->AddUFunction(this, FName("Fuc_RecvWallSpawnWhale"));
	ProcessThread::GetInst()->GetFWallSpawnWhaleEnd()->AddUFunction(this, FName("Fuc_RecvWallSpawnWhaleEnd"));
	ProcessThread::GetInst()->GetFPlayWhaleSound()->AddUFunction(this, FName("Fuc_RecvPlayWhaleSound"));
	ProcessThread::GetInst()->GetFFloorSpawnWhale()->AddUFunction(this, FName("Fuc_RecvFloorSpawnWhale"));
	ProcessThread::GetInst()->GetFCleaningOceanEnd()->AddUFunction(this, FName("Fuc_RecvCleaningOceanEnd"));

#pragma endregion

#pragma region CoralForestBindingDatas

	ProcessThread::GetInst()->GetFCoralLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvCoralLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFCoralOverlap()->AddUFunction(this, FName("Fuc_RecvCoralOverlap"));
	ProcessThread::GetInst()->GetFCoralWhiteSwitch()->AddUFunction(this, FName("Fuc_RecvCoralWhiteSwitch"));
	ProcessThread::GetInst()->GetFCoralEnd()->AddUFunction(this, FName("Fuc_RecvCoralEnd"));

#pragma endregion

#pragma region KelpForestBindingDatas
	ProcessThread::GetInst()->GetFKelpLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvKelpLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFOilCount()->AddUFunction(this, FName("Fuc_RecvOilCount"));
	ProcessThread::GetInst()->GetFOilOverlap()->AddUFunction(this, FName("Fuc_RecvOilOverlap"));
	ProcessThread::GetInst()->GetFKelpLevelPlaySequence()->AddUFunction(this, FName("Fuc_RecvKelpLevelPlaySequence"));
	ProcessThread::GetInst()->GetFOilEnd()->AddUFunction(this, FName("Fuc_RecvOilEnd"));
#pragma endregion

#pragma region OceanVillageBindingDatas
	ProcessThread::GetInst()->GetFOceanVillageLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvOceanVillageLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFGuideActorTargetChange()->AddUFunction(this, FName("Fuc_RecvGuideActorTargetChange"));
	ProcessThread::GetInst()->GetFFishActorTargetChange()->AddUFunction(this, FName("Fuc_RecvFishActorTargetChange"));
	ProcessThread::GetInst()->GetFFishActorTransform()->AddUFunction(this, FName("Fuc_RecvFishActorTransform"));
#pragma endregion

#pragma region CamouFishBindingDatas
	ProcessThread::GetInst()->GetFCamouFlageFishLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvCamouFlageFishLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFCamouFishEnd()->AddUFunction(this, FName("Fuc_RecvCamouFishEnd"));
#pragma endregion

#pragma region LuminaryFishBindingDatas
	ProcessThread::GetInst()->GetFLuminaryFishLevelLoadingEnd()->AddUFunction(this, FName("Fuc_RecvLuminaryFishLevelLoadingEnd"));
	ProcessThread::GetInst()->GetFLumiFishEnd()->AddUFunction(this, FName("Fuc_RecvLumiFishEnd"));
#pragma endregion

#pragma region CmsBindingDatas
	ProcessThread::GetInst()->GetFCmsControllerStart()->AddUFunction(this, FName("Fuc_RecvCmsControllerStart"));
	ProcessThread::GetInst()->GetFCmsControllerStop()->AddUFunction(this, FName("Fuc_RecvCmsControllerStop"));
	ProcessThread::GetInst()->GetFCmsControllerSkip()->AddUFunction(this, FName("Fuc_RecvCmsControllerSkip"));
	ProcessThread::GetInst()->GetFCmsControllerReset()->AddUFunction(this, FName("Fuc_RecvCmsControllerReset"));
	ProcessThread::GetInst()->GetFCmsControllerNewPlayer()->AddUFunction(this, FName("Fuc_RecvCmsControllerNewPlayer"));
#pragma endregion

#pragma region PlayEffectSoundBindingDatas
	ProcessThread::GetInst()->GetFPlayEffectSound()->AddUFunction(this, FName("Fuc_RecvPlayEffectSound"));
#pragma endregion

#pragma region LoadBindingDatas
	ProcessThread::GetInst()->GetFLoadPNG()->AddUFunction(this, FName("Fuc_RecvLoadPNG"));
#pragma endregion

#pragma region ChangeEnvBindingDatas
	ProcessThread::GetInst()->GetFOceanCleanChange()->AddUFunction(this, FName("Fuc_RecvOceanCleanChange"));
	ProcessThread::GetInst()->GetFPlayTimeOutEvent()->AddUFunction(this, FName("Fuc_RecvPlayTimeOutEvent"));
#pragma endregion
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Recv %d"), 1));
}

void UGameManager::Shutdown()
{
	Super::Shutdown();

	//FPlatformProcess::Sleep(0.05f);

	//Send_SetSceneType(true);

	if (SocketManager::GetInst()->QuitConnection())
	{
		if (SendThread::GetInst() != nullptr)
			SendThread::GetInst()->StopListen(false);

		if (RecvThread::GetInst() != nullptr)
			RecvThread::GetInst()->StopListen(false);

		if (ProcessThread::GetInst() != nullptr)
			ProcessThread::GetInst()->StopListen(false);
	}
}

void UGameManager::CheckSceneType(bool isWall, ClientNodeType ClientNodeType)
{
	if(placeType == 255)
		Send_SetSceneType(isWall, ClientNodeType);
}

void UGameManager::Send_SetSceneType(bool isWall, ClientNodeType ClientNodeType)
{
	if (SetSceneTypeOnce)
	{
		SetSceneTypeOnce = false;
		if (isWall)
			placeType = (uint8)PROTOCOLSUB_TYPE::Wall;
		else
			placeType = (uint8)PROTOCOLSUB_TYPE::Floor;

		if (SendThread::GetInst() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("SendThread instance is null."));
			return;
		}

		nodeType = (uint8)ClientNodeType;
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::SetSceneType, placeType, nodeType);
	}
}

#pragma region InfoMovieBindingDatas

inline void UGameManager::Fuc_RecvMovieLevelLoadingEnd(bool isA) { RecvMovieLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvInfoMovieEnd() { RecvInfoMovieEnd.Broadcast(); }

inline void UGameManager::Send_MovieLevelLoadingEnd() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::InfoMovie, (uint8)PROTOCOLSUB_INFOMOVIE::InfoMovieLevelLoadingEnd, (uint8)placeType); }
inline void UGameManager::Send_ChangeScript(PROTOCOLSUB_CMS scriptType) { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::InfoMovie, (uint8)PROTOCOLSUB_INFOMOVIE::ChangeScript, (uint8)scriptType); }
void UGameManager::Send_InfoMovieEnd()
{
	if (IsLocalGame)
		Fuc_RecvInfoMovieEnd();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::InfoMovie, (uint8)PROTOCOLSUB_INFOMOVIE::InfoMovieEnd);
}

#pragma endregion

#pragma region CleaningOceanBindingDatas

inline void UGameManager::Fuc_RecvCleaningLevelLoadingEnd(bool isA) { RecvCleaningLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvWallSpawnWhale(SIDE_TYPE type)
{
	curr_WhaleSpawnSideType = type;
	RecvWallSpawnWhale.Broadcast(type);
}
inline void UGameManager::Fuc_RecvChangeWhaleDirection() { RecvChangeWhaleDirection.Broadcast(); }
inline void UGameManager::Fuc_RecvWallSpawnWhaleEnd() { RecvWallSpawnWhaleEnd.Broadcast(); }
inline void UGameManager::Fuc_RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE type) { RecvPlayWhaleSound.Broadcast(type); }
inline void UGameManager::Fuc_RecvFloorSpawnWhale(SIDE_TYPE type, bool IsSuccess)
{
	RecvFloorSpawnWhale.Broadcast(type, IsSuccess);
	//switch (placeType)
	//{
	//case (uint8)PROTOCOLSUB_TYPE::Wall:
	//	Send_FloorSpawnWhale();
	//	break;
	//case (uint8)PROTOCOLSUB_TYPE::Floor:
	//	RecvFloorSpawnWhale.Broadcast(curr_WhaleSpawnSideType);
	//	break;
	//default:
	//	break;
	//}
}
inline void UGameManager::Fuc_RecvCleaningOceanEnd() { RecvCleaningOceanEnd.Broadcast(); }

void UGameManager::Send_CleaningLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvCleaningLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::CleaningLevelLoadingEnd, (uint8)placeType);
}
inline void UGameManager::Send_WallSpawnWhale(int count) { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::WallSpawnWhale, count); }
inline void UGameManager::Send_ChangeWhaleDirection() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::ChangeWhaleDirection); }
inline void UGameManager::Send_WallSpawnWhaleEnd() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::WallWhaleSpawnEnd); }
inline void UGameManager::Send_PlayWhaleSound() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::PlayWhaleSound); }
inline void UGameManager::Send_FloorSpawnWhale()
{
	if (IsLocalGame)
		Fuc_RecvFloorSpawnWhale((SIDE_TYPE)curr_WhaleSpawnSideType, true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::FloorSpawnWhale, (uint8)curr_WhaleSpawnSideType);
}
inline void UGameManager::Send_CleaningOceanEnd() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CleaningOcean, (uint8)PROTOCOLSUB_CLEANING::CleaningOceanEnd); }

#pragma endregion

#pragma region CoralForestBindingDatas

inline void UGameManager::Fuc_RecvCoralLevelLoadingEnd(bool isA) { RecvCoralLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvCoralOverlap(CORAL_TYPE coralType) { RecvCoralOverlap.Broadcast(coralType); }
inline void UGameManager::Fuc_RecvCoralWhiteSwitch() { RecvCoralWhiteSwitch.Broadcast(); }
inline void UGameManager::Fuc_RecvCoralEnd() { RecvCoralEnd.Broadcast(); }

void UGameManager::Send_CoralLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvCoralLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CoralForest, (uint8)PROTOCOLSUB_CORAL::CoralLevelLoadingEnd, (uint8)placeType);
}
inline void UGameManager::Send_CoralOverlap(CORAL_TYPE coralType) { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CoralForest, (uint8)PROTOCOLSUB_CORAL::CoralOverlap, (uint8)coralType); }
void UGameManager::Send_CoralWhiteSwitch()
{
	if (IsLocalGame)
		Fuc_RecvCoralWhiteSwitch();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CoralForest, (uint8)PROTOCOLSUB_CORAL::CoralWhiteSwitch);
}
void UGameManager::Send_CoralEnd()
{
	if (IsLocalGame)
		Fuc_RecvCoralEnd();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CoralForest, (uint8)PROTOCOLSUB_CORAL::CoralEnd);
}

#pragma endregion

#pragma region KelpForestBindingDatas

inline void UGameManager::Fuc_RecvKelpLevelLoadingEnd(bool isA) { RecvKelpLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvOilCount(int32 count) { RecvOilCount.Broadcast(count); }
inline void UGameManager::Fuc_RecvOilOverlap(int32 cnt) { RecvOilOverlap.Broadcast(cnt); }
inline void UGameManager::Fuc_RecvKelpLevelPlaySequence() { RecvKelpLevelPlaySequence.Broadcast(); }
inline void UGameManager::Fuc_RecvOilEnd() { RecvOilEnd.Broadcast(); }

void UGameManager::Send_KelpLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvKelpLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::KelpForest, (uint8)PROTOCOLSUB_KELP::KelpLevelLoadingEnd, (uint8)placeType);
}
inline void UGameManager::Send_OilCount(int32 count) { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::KelpForest, (uint8)PROTOCOLSUB_KELP::OilCount, count); }
inline void UGameManager::Send_OilOverlap(int32 cnt) { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::KelpForest, (uint8)PROTOCOLSUB_KELP::OilOverlap, cnt); }
inline void UGameManager::Send_KelpLevelPlaySequence() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::KelpForest, (uint8)PROTOCOLSUB_KELP::KelpLevelPlaySequence); }
inline void UGameManager::Send_OilEnd()
{
	if (IsLocalGame)
		Fuc_RecvOilEnd();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::KelpForest, (uint8)PROTOCOLSUB_KELP::OilEnd);
}

#pragma endregion

#pragma region OceanVillageBindingDatas

inline void UGameManager::Fuc_RecvOceanVillageLevelLoadingEnd(bool isA) { RecvOceanVillageLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvGuideActorTargetChange(int guideActorNum, int targetActorNum) { RecvGuideActorTargetChange.Broadcast(guideActorNum, targetActorNum); }
inline void UGameManager::Fuc_RecvFishActorTargetChange(int fishActorNum, int guideActorNum, bool IsFirst) { RecvFishActorTargetChange.Broadcast(fishActorNum, guideActorNum, IsFirst); }

inline void UGameManager::Fuc_RecvFishActorTransform(int fishActorNum, FTransform transform) { RecvFishActorTransform.Broadcast(fishActorNum, transform); }

void UGameManager::Send_OceanVillageLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvOceanVillageLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::OceanVillage, (uint8)PROTOCOLSUB_OceanVillage::OceanVillageLevelLoadingEnd, (uint8)placeType);
}
void UGameManager::Send_GuideActorTargetChange(int guideActorNum, int targetActorNum)
{
	//if (!IsLocalGame)
	//	if (nodeType != (uint8)ClientNodeType::Node0)
	//		return;

	if (IsLocalGame)
		Fuc_RecvGuideActorTargetChange(guideActorNum, targetActorNum);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::OceanVillage, (uint8)PROTOCOLSUB_OceanVillage::GuideActorTargetChange, guideActorNum, targetActorNum);
}

void UGameManager::Send_FishActorTargetChange(int fishActorNum, int guideActorNum, bool IsFirstSetting)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	if (IsLocalGame)
		Fuc_RecvFishActorTargetChange(fishActorNum, guideActorNum, IsFirstSetting);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::OceanVillage, (uint8)PROTOCOLSUB_OceanVillage::FishActorTargetChange, fishActorNum, guideActorNum, IsFirstSetting ? 0 : 1);
}

void UGameManager::Send_FishActorTransform(int fishActorNum, FTransform tranform)
{
	if (IsLocalGame)
		Fuc_RecvFishActorTransform(fishActorNum, tranform);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::OceanVillage, (uint8)PROTOCOLSUB_OceanVillage::FishTransform, fishActorNum, tranform);
}

#pragma endregion

#pragma region CamouFishBindingDatas

inline void UGameManager::Fuc_RecvCamouFlageFishLevelLoadingEnd(bool isA) { RecvCamouFlageFishLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvCamouFishEnd() { RecvCamouFishEnd.Broadcast(); }

void UGameManager::Send_CamouFlageFishLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvCamouFlageFishLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CamouFlageFish, (uint8)PROTOCOLSUB_CamouFlageFish::CamouFlageFishLevelLoadingEnd, (uint8)placeType);
}
void UGameManager::Send_CamouFlageFishCount(int count)
{
	if (nodeType != (uint8)ClientNodeType::Node0)
		return;

	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CamouFlageFish, (uint8)PROTOCOLSUB_CamouFlageFish::CamouFlageFishCount, count);
}
inline void UGameManager::Send_CamouFishFind() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CamouFlageFish, (uint8)PROTOCOLSUB_CamouFlageFish::CamouFishFind); }

#pragma endregion

#pragma region LuminaryFishBindingDatas

inline void UGameManager::Fuc_RecvLuminaryFishLevelLoadingEnd(bool isA) { RecvLuminaryFishLevelLoadingEnd.Broadcast(isA); }
inline void UGameManager::Fuc_RecvLumiFishEnd() { RecvLumiFishEnd.Broadcast(); GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Fuc_RecvLumiFishEnd")); }

void UGameManager::Send_LuminaryFishLevelLoadingEnd()
{
	if (IsLocalGame)
		Fuc_RecvLuminaryFishLevelLoadingEnd(true);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::LuminaryFish, (uint8)PROTOCOLSUB_LuminaryFish::LuminaryFishLevelLoadingEnd, (uint8)placeType);
}
void UGameManager::Send_LuminaryFishCount(int count)
{
	if (nodeType != (uint8)ClientNodeType::Node0)
		return;

	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::LuminaryFish, (uint8)PROTOCOLSUB_LuminaryFish::LumiFishCount, count);
}
inline void UGameManager::Send_LumiFishFind() { SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::LuminaryFish, (uint8)PROTOCOLSUB_LuminaryFish::LumiFishFind); }

#pragma endregion

#pragma region CmsBindingDatas

inline void UGameManager::Fuc_RecvCmsControllerStart() { RecvCmsControllerStart.Broadcast(); }
inline void UGameManager::Fuc_RecvCmsControllerStop() { RecvCmsControllerStop.Broadcast(); }
inline void UGameManager::Fuc_RecvCmsControllerSkip() { RecvCmsControllerSkip.Broadcast(); }
inline void UGameManager::Fuc_RecvCmsControllerReset(RESET_TYPE type) { RecvCmsControllerReset.Broadcast(type); }
void UGameManager::Fuc_RecvCmsControllerNewPlayer(FString _levelName)
{
	FString fullLevelName = "";
	switch (placeType)
	{
	case (uint8)PROTOCOLSUB_TYPE::Wall:
		fullLevelName = _levelName.Append("_Wall_Dev");
		break;
	case (uint8)PROTOCOLSUB_TYPE::Floor:
		fullLevelName = _levelName.Append("_Floor_Dev");
		break;
	default:
		break;
	}
	RecvCmsControllerNewPlayer.Broadcast(fullLevelName);
}

void UGameManager::Send_CmsControllerStart()
{
	if(IsLocalGame)
		Fuc_RecvCmsControllerStart();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::Play);
}

void UGameManager::Send_CmsControllerStop()
{
	if (IsLocalGame)
		Fuc_RecvCmsControllerStop();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::Stop);
}

void UGameManager::Send_CmsControllerSkip()
{
	if (IsLocalGame)
		Fuc_RecvCmsControllerSkip();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::Skip);
}

void UGameManager::Send_CmsControllerReset(RESET_TYPE type)
{
	if (IsLocalGame)
		Fuc_RecvCmsControllerReset(type);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::Reset, (uint8)type);
}

void UGameManager::Send_TempBG_Wall()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::ReStartWallClients);
}

void UGameManager::Send_TempBG_Floor()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::ReStartFloorClients);
}

inline void UGameManager::Fuc_RecvPlayEffectSound(EFFECT_SOUND_TYPE _type) { RecvPlayEffectSound.Broadcast(_type); }

void UGameManager::Send_PlayEffectSound(EFFECT_SOUND_TYPE _type)
{
	if (IsLocalGame)
		Fuc_RecvPlayEffectSound(_type);
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::PlayEffectSound, (uint8)PROTOCOLSUB_TYPE::Floor, (uint8)_type);
}

#pragma endregion

#pragma region LoadBindingDatas

inline void UGameManager::Fuc_RecvLoadPNG() { RecvLoadPNG.Broadcast(); }

void UGameManager::Send_LoadPNG()
{
	//if (nodeType != (uint8)ClientNodeType::Node0)
	//	return;

	if (IsLocalGame)
		Fuc_RecvLoadPNG();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::LoadData, (uint8)PROTOCOLSUB_LOADDATA::LoadPNG);
		
}

#pragma endregion

#pragma region ChangeEnvBindingDatas

inline void UGameManager::Fuc_RecvOceanCleanChange() { RecvOceanCleanChange.Broadcast(); }

inline void UGameManager::Fuc_RecvPlayTimeOutEvent() { RecvPlayTimeOutEvent.Broadcast(); }

void UGameManager::Send_OceanCleanChange()
{
	if (IsLocalGame)
		Fuc_RecvOceanCleanChange();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::ChangeLevelEnv, (uint8)PROTOCOLSUB_ChangeLevelEnv::OceanCleanChange);
}

void UGameManager::Send_PlayTimeOutEvent()
{
	if (IsLocalGame)
		Fuc_RecvPlayTimeOutEvent();
	else
		SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::ChangeLevelEnv, (uint8)PROTOCOLSUB_ChangeLevelEnv::PlayTimeOutEvent);
}

#pragma endregion