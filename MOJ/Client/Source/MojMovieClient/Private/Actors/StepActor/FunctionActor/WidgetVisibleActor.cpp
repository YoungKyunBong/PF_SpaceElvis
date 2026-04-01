// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/WidgetVisibleActor.h"
#include "Manager/StepManager.h"

void AWidgetVisibleActor::SetWidgetVisible()
{
	stepManager->CallWidgetVisible(Option);
}
