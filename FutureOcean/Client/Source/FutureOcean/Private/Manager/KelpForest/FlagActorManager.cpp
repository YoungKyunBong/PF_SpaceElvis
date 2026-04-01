#include "Manager/KelpForest/FlagActorManager.h"
#include "Actors/StepActor/CoralForest/FlagCoralActor.h"
#include "Manager/GameManager.h"

void UFlagActorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//CheckWallLevel();
	//SendSceneTypeToServer();
	//RecvOverlapFromServer();
	
}

void UFlagActorManager::Deinitialize()
{
	Super::Deinitialize();
}

void UFlagActorManager::RegisterFlagCoraltActor(AFlagCoralActor* FlagCoralActor)
{
	FlagCoralActors.Add(FlagCoralActor);
}

void UFlagActorManager::SendSceneTypeToServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->Send_SetSceneType(true);
		}
	}
}

void UFlagActorManager::RecvOverlapFromServer()
{
	if (bWallLevel)
	{
		if (UGameManager* GameManager = Cast<UGameManager>(GetWorld()->GetGameInstance()))
		{
			//GameManager->RecvCoralOverlap.AddUFunction(this, FName("RecvCoralType"));
			GameManager->RecvCoralOverlap.AddUFunction(this, FName("OverlapInteraction"));
		}
	}
}

const TArray<AFlagCoralActor*>& UFlagActorManager::GetPollutedCoralActors() const
{
	return FlagCoralActors;
}

void UFlagActorManager::RecvCoralType(CORAL_TYPE _Type)
{
	CoralType = _Type;
}

void UFlagActorManager::OverlapInteraction(CORAL_TYPE _Type)
{
	for (AFlagCoralActor* FlagCoralActor : FlagCoralActors) 
	{
		if (FlagCoralActor->Get_CoralType() == _Type)
		{		
			
			FlagCoralActor->FadeSwitch();
		}
	}
	++InteractionCnt;
	if (InteractionCnt >= 6)
	{
		ChangeOpValue();
	}
}

void UFlagActorManager::ChangeOpValue()
{
	for (AFlagCoralActor* FlagCoralActor : FlagCoralActors)
	{
		//FlagCoralActor->SetOpValue();		
	}
}

void UFlagActorManager::CheckWallLevel()
{
	// 현재 월드의 레벨 이름을 가져와서 특정 레벨인지 확인
	UWorld* World = GetWorld();
	if (World)
	{
		// 레벨의 이름 확인
		FString LevelName = World->GetMapName();
		if (LevelName.Contains("CoralForest_Wall_Dev"))
		{
			bWallLevel = true;
		}
	}
}
