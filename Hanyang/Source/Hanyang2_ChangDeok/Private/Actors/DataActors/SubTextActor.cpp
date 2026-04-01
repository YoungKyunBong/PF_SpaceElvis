// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DataActors/SubTextActor.h"
#include "Manager/StepManager.h"
#include "GameMode/DefaultGameMode.h"

void ASubTextActor::SetSubTextToWidget()
{
	stepManager->GetGameMode()->GetWidgetActor()->SetSubTextToWidget(TextID, margin_Top, fontSize);
}

void ASubTextActor::CheckSkip()
{
	stepManager->GetGameMode()->GetWidgetActor()->SetSubWidgetHidden();
}
