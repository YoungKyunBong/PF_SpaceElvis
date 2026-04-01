#include "Manager/CoralForest/CleaningOilManager.h"
#include "Actors/StepActor/KelpForest/CleaningOilActor.h"
#include "Manager/CoralForest/PollutedCoralManager.h"
#include "Manager/GameManager.h"
#include "kismet/GameplayStatics.h"
#include "TimerManager.h"

void UCleaningOilManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
		
	/*CheckFloorLevel();
	SendSceneTypeToServer();*/
}

void UCleaningOilManager::Deinitialize()
{
	Super::Deinitialize();
}

void UCleaningOilManager::RegisterCleaningOilActor(ACleaningOilActor* CleaningOilActor)
{
	CleaningOilActors.Add(CleaningOilActor);
	
}

void UCleaningOilManager::SendSceneTypeToServer()
{
	if (bFloorLevel)
	{
				
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(false);
		}
	}
}

void UCleaningOilManager::SendOilOverlapToServer()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_OilOverlap();
		}
	}
}

void UCleaningOilManager::SendActorCountToServer()
{
	TArray<AActor*> MyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACleaningOilActor::StaticClass(), MyActors);
	CleaningOilCnt = MyActors.Num();
	
	
	if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
	{		
		GameManager->Send_OilCount(CleaningOilCnt);
	}
}

void UCleaningOilManager::PollutedCoralChangeOpValue()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		UPollutedCoralManager* PollutedCoralManager = GetWorld()->GetSubsystem<UPollutedCoralManager>();
		if (PollutedCoralManager)
		{
			PollutedCoralManager->ChangeOpValue();
		}
	}
}

const TArray<TObjectPtr<ACleaningOilActor>>& UCleaningOilManager::GetCleaningOilActors() const
{
	return CleaningOilActors;
}

void UCleaningOilManager::CheckFloorLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("KelpForest_Floor_Dev"))
		{
			bFloorLevel = true;
		}
	}
}
