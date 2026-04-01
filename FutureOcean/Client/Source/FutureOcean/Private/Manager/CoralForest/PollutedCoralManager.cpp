#include "Manager/CoralForest/PollutedCoralManager.h"
#include "Actors/StepActor/KelpForest/PollutedCoralActor.h"
#include "Manager/GameManager.h"
#include "kismet/GameplayStatics.h"
#include <Windows.h>

void UPollutedCoralManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	/*CheckWallLevel();
	SendSceneTypeToServer();
	RecvOilCountFromServer();*/
}


void UPollutedCoralManager::Deinitialize()
{
	Super::Deinitialize();
}

void UPollutedCoralManager::RegisterPollutedCoraltActor(APollutedCoralActor* PollutedCoralActor)
{
	PollutedCoralActors.Add(PollutedCoralActor);
}

void UPollutedCoralManager::ChangeOpValue()
{
	for (APollutedCoralActor* PollutedCoralActor : PollutedCoralActors)
	{
		if (PollutedCoralActor == nullptr)
		{
			MessageBox(NULL, TEXT("Failed::FindOilObjects"), TEXT("Failed"), MB_OK);
			return;
		}
		else
		{
			PollutedCoralActor->ChangeOpValue(OilCount);
		}
	}
}

void UPollutedCoralManager::CleaningOilCount(int32 _Count)
{
	OilCount = _Count;
}

void UPollutedCoralManager::SendSceneTypeToServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(true);			
		}
	}
}

void UPollutedCoralManager::RecvOilCountFromServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->RecvOilCount.AddUFunction(this, FName("CleaningOilCount"));
			GameManager->RecvOilOverlap.AddUFunction(this, FName("ChangeOpValue"));
		}
	}
}

const TArray<APollutedCoralActor*>& UPollutedCoralManager::GetPollutedCoralActors() const
{
	return PollutedCoralActors;
}

void UPollutedCoralManager::CheckWallLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("KelpForest_Wall_Dev"))
		{
			bWallLevel = true;
		}
	}
}
