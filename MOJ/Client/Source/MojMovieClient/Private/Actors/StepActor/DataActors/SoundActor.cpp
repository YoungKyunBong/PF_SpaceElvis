// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/SoundActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoundActor::PlayNarr()
{
	float deleyTime = 0.0f;
	float tempTime = stepManager->CallPlayNarrationByID(SoundID);
	if(isDelay)
		deleyTime = tempTime;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &ASoundActor::SetTimer_PlayNarr, deleyTime + NarrEndDelay, false);
}

float ASoundActor::CheckSkip()
{
	GetWorldTimerManager().ClearTimer(Handle);
	return stepManager->CallNarrationFadeOut(0.5f);
}

void ASoundActor::SetNarrationPaused(bool IsPlay)
{
	stepManager->CallSetNarrationPaused(IsPlay);

	if (IsPlay)
	{
		GetWorldTimerManager().PauseTimer(Handle);
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(Handle);
	}
}

void ASoundActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void ASoundActor::SetTimer_PlayNarr()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SetTimer_PlayNarr"));
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->NextStep();
}
