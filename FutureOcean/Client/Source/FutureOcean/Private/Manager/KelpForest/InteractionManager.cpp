#include "Manager/KelpForest/InteractionManager.h"
#include "Actors/StepActor/CoralForest/InteractionActor.h"
#include "Manager/GameManager.h"


void UInteractionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CheckFloorLevel();
	SendSceneTypeToServer();
}

void UInteractionManager::Deinitialize()
{
	Super::Deinitialize();
}

void UInteractionManager::RegisterInteractionActor(AInteractionActor* InteractionActor)
{
	InteractionActors.Add(InteractionActor);
}

void UInteractionManager::SendSceneTypeToServer()
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(false);
		}
	}
}

void UInteractionManager::SendOverlapToServer(CORAL_TYPE _Type)
{
	if (bFloorLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			GameManager->Send_CoralOverlap(_Type);
		}
	}
}

void UInteractionManager::DepthSwitch(bool bEnable)
{
	//InteractionActors[0]->DepthSwitch();
}

void UInteractionManager::VisibilitySwitch(bool bEnable)
{

}

void UInteractionManager::CheckFloorLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("CoralForest_Floor_Dev"))
		{
			bFloorLevel = true;
		}
	}
}

const TArray<TObjectPtr<AInteractionActor>>& UInteractionManager::GetInteractionActors() const
{
	return InteractionActors;
}
