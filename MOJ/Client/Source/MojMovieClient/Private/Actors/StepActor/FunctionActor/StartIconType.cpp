// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/StartIconType.h"
#include "Manager/StepManager.h"

void AStartIconType::SetIconType()
{
	stepManager->CallSetWidgetSwitchIndex(3);
	stepManager->CallSetIconType(checkIconType);
}
