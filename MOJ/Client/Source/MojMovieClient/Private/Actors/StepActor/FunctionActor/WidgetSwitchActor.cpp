// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/WidgetSwitchActor.h"
#include "Manager/StepManager.h"

void AWidgetSwitchActor::SetWidgetSwitchIndex()
{
	stepManager->CallSetWidgetSwitchIndex(index);
}
