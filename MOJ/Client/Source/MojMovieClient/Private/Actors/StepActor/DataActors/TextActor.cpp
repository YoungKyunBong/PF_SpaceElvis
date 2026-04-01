// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/TextActor.h"
#include "Manager/StepManager.h"

void ATextActor::SetTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(switchIndex);
	stepManager->CallSetNarrText(HeaderTextID, TextID, true, true);
}

void ATextActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton("", ButtonTextID, false);
}
