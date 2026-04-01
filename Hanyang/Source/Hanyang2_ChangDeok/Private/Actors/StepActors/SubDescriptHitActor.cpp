// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/SubDescriptHitActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"


void ASubDescriptHitActor::BeginOverlapPawn()
{
	if (IsOverDefaultBox && IsOverCheckBox)
		GetGameMode()->GetCurrentStepManager(MyStepManagerNumber)->NextStep();

}

void ASubDescriptHitActor::EndOverlapPawn()
{
	IsOverDefaultBox = false;
	IsOverCheckBox = false;
	GetGameMode()->GetCurrentStepManager(MyStepManagerNumber)->Reset_Skip();
}
