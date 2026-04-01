// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/FadeActor.h"
#include "Manager/StepManager.h"
#include "GameMode/DefaultGameMode.h"

void AFadeActor::CallCustomFade()
{
	if(IsFadeIn)
		stepManager->GetGameMode()->GetWidgetActor()->CustomFadeIn();
	else
		stepManager->GetGameMode()->GetWidgetActor()->CustomFadeOut();
}
