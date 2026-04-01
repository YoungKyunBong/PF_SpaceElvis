// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DataActors/TextActor.h"
#include "Manager/StepManager.h"
#include "GameMode/DefaultGameMode.h"

void ATextActor::SetTextToWidget()
{
	stepManager->GetGameMode()->GetWidgetActor()->SetTextToWidget(TextID);
}
