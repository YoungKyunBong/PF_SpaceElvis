// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"

void ADefaultGameMode::SetStartStepManager(AStepManager* _StepManager)
{
	StartStepManager = _StepManager;
	InWorldAllManager.Add(_StepManager->StepManagerNumber, _StepManager);
}

void ADefaultGameMode::SetStepManagers(TArray<AStepManager*> _StepManagers)
{
	//epManagers = _StepManagers;
	for (int i = 0; i < _StepManagers.Num(); i++)
	{
		InWorldAllManager.Add(_StepManagers[i]->StepManagerNumber, _StepManagers[i]);
	}
}

AStepManager* ADefaultGameMode::GetCurrentStepManager(int StepManagerNum)
{
	if(InWorldAllManager.Contains(StepManagerNum))
		return InWorldAllManager[StepManagerNum];

	return nullptr;
}

void ADefaultGameMode::ProcessStartStepManager()
{
	if (StartStepManager != nullptr)
		StartStepManager->StepStart();
}

void ADefaultGameMode::PlayNotFirst()
{
	GetWidgetActor()->SetMainWidgetDefault();
}
 