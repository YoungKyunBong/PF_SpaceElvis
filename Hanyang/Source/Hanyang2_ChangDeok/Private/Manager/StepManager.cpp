// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/StepManager.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/StepActors/SqeStep.h"
#include "Hanyang2_ChangDeok/GameManager.h"

void AStepManager::SetNameCheck(AActor* checkActor, FString appendName)
{
#if WITH_EDITOR

	//editor only code -- doesn't appear in final game
	checkActor->SetActorLabel(appendName);
#endif
}

void AStepManager::StepStart()
{
	if (CheckStepCount())
	{
		sqeSteps[StepCount++]->CheckStep(this);
	}
	//else {
	//	if (!Cast<UGameManager>(GetGameInstance())->IsEvent)
	//	{
	//		StepCount = 0;
	//		sqeSteps[StepCount++]->CheckStep(this);
	//	}
	//}
}

void AStepManager::Init()
{
	for (int i = 0; i < sqeSteps.Num(); i++)
	{
		sqeSteps[i]->Init(this);
	}
}

void AStepManager::NextStep()
{
	if (!IsGameEnd)
		StepStart();
}

void AStepManager::SkipStep()
{
	if (!IsGameEnd) {
		if (CheckStepCount())
			sqeSteps[StepCount - 1]->SkipStep();
	}
}

void AStepManager::RewindStep()
{
	if (CheckStepCount())
		sqeSteps[StepCount - 1]->RewindStep();
}

void AStepManager::Reset_Skip_Implementation()
{
	for (int i = 0; i < sqeSteps.Num(); i++)
	{
		sqeSteps[i]->ResetSkip();
	}
}

void AStepManager::CallResetSkip()
{
	Reset_Skip();
}

void AStepManager::SetIsGameEnd(bool IsCheck)
{
	IsGameEnd = IsCheck;
}

bool AStepManager::CheckStepCount()
{
	return StepCount != sqeSteps.Num();
}
