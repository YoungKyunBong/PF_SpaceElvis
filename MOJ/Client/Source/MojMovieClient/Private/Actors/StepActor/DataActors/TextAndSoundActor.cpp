// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/TextAndSoundActor.h"
#include "Manager/StepManager.h"

void ATextAndSoundActor::PlayNarr()
{
	float deleyTime = stepManager->CallPlayNarrationByID(SoundID);
}

void ATextAndSoundActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton("", ButtonTextID, false);
}
