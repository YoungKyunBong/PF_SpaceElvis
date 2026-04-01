#include "GameMode/KelpForestGameMode.h"
#include "Manager/CoralForest/PollutedCoralManager.h"
#include "Manager/CoralForest/CleaningOilManager.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

void AKelpForestGameMode::BeginPlay()
{
	Super::BeginPlay();
	init();
}

void AKelpForestGameMode::init()
{
	if (UCleaningOilManager* Manager = Cast<UCleaningOilManager>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UCleaningOilManager::StaticClass())))
	{
		bool bFloorLevel = Manager->GetFloorLevel();
		if (bFloorLevel)
		{
			Manager->SendActorCountToServer();
		}
	}

	/*if (UPollutedCoralManager* Manager = Cast<UPollutedCoralManager>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UPollutedCoralManager::StaticClass())))
	{
		bool bWallLevel = Manager->GetWallLevel();
		if (bWallLevel)
		{
			Manager->RecvOilCountFromServer();
		}
	}*/
}
