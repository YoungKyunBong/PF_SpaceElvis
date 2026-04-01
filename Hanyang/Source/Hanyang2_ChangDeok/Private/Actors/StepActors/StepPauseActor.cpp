// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/StepPauseActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActors/SqeStep.h"
#include "Manager/StepManager.h"

void AStepPauseActor::Init(AStepManager* Manager)
{
	Super::Init(Manager);
	for (int i = 0; i < stepManager->sqeSteps.Num(); i++)
	{
		if (stepManager->sqeSteps[i]->StepActor == this)
		{
			ReverseStepNumber = i + 1;
			break;
		}
	}
}

void AStepPauseActor::PlacePawnDefaultSetting()
{
	PlacePawn->SetActorTransform(FTransform(TargetActor->GetActorRotation(), TargetActor->GetActorLocation(), FVector(1.f, 1.f, 1.f)));
	stepManager->GetGameMode()->GetWidgetActor()->SetSkipButtonText(SkipText);
}

void AStepPauseActor::MyStep_Implementation(AStepManager* Manager)
{
	Manager->GetGameMode()->GetWidgetActor()->SetSkipButtonText(BackText);
}

void AStepPauseActor::ResetSkip_Implementation()
{
	stepManager->StepCount = ReverseStepNumber;
}
