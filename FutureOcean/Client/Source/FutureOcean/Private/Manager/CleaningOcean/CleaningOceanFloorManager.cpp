#include "Manager/CleaningOcean/CleaningOceanFloorManager.h"
#include "Manager/GameManager.h"

void UCleaningOceanFloorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//CheckFloorLevel();
	//SendSceneTypeToServer();
	//SendLeftSideToServer();
	//SendRightSideToServer();
	//RecvPlayWhaleSound();
}

void UCleaningOceanFloorManager::Deinitialize()
{
	Super::Deinitialize();
}

void UCleaningOceanFloorManager::SendSceneTypeToServer()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(false);
		}
	}
}

void UCleaningOceanFloorManager::CheckFloorLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("CleaningOcean_Floor_Dev"))
		{
			bFloorLevel = true;
		}
	}
}

void UCleaningOceanFloorManager::SendLeftSideToServer()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_WallSpawnWhale(SIDE_TYPE::LeftSide, 7);
		}
	}
}

void UCleaningOceanFloorManager::SendRightSideToServer()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_WallSpawnWhale(SIDE_TYPE::RightSide, 8);
		}
	}
}

void UCleaningOceanFloorManager::SendPlayWhaleSound()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->Send_PlayWhaleSound();
		}
	}
}

void UCleaningOceanFloorManager::RecvPlayWhaleSound()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->RecvPlayWhaleSound.AddUFunction(this, FName("SetWhaleSoundType"));
		}
	}
}

void UCleaningOceanFloorManager::SetWhaleSoundType(WHALE_SOUND_DISTANCE_TYPE Type)
{
	SoundType = Type;
}
