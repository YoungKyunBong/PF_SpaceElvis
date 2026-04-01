// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/AnswerTextActor.h"
#include "Manager/StepManager.h"

void AAnswerTextActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void AAnswerTextActor::PlayNarr(FString SoundID)
{
	float deleyTime = stepManager->CallPlayNarrationByID(SoundID);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &AAnswerTextActor::SetTimer_PlayNarr, deleyTime + NarrEndDelay, false);
}

void AAnswerTextActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton("", ButtonTextID, false);
}

void AAnswerTextActor::SetTimer_PlayNarr()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->NextStep();
}
