#include "Manager/CleaningOcean/CleaningOceanWallManager.h"
#include "Manager/GameManager.h"

void UCleaningOceanWallManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//CheckWallLevel();
	//SendSceneTypeToServer();
	//RecvSideTypeFromServer();
}

void UCleaningOceanWallManager::Deinitialize()
{
	Super::Deinitialize();
}

void UCleaningOceanWallManager::SendSceneTypeToServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(true);
		}
	}
}

void UCleaningOceanWallManager::SendFloorSpawnTypeToServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->Send_FloorSpawnWhale();
		}
	}
}

void UCleaningOceanWallManager::RecvSideTypeFromServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->RecvWallSpawnWhale.AddUFunction(this, FName("SetSideType"));
		}
	}
}

SIDE_TYPE UCleaningOceanWallManager::Get_SideType()
{
	int32 TypeNum = FMath::RandRange(0, 1);

	return CurType[TypeNum];
}

void UCleaningOceanWallManager::SetSideType(SIDE_TYPE Type)
{
	CurType.Add(Type);
}

void UCleaningOceanWallManager::CheckWallLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("CleaningOcean_Wall_Dev"))
		{
			bWallLevel = true;
		}
	}
}
