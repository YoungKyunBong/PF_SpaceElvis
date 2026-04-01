// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/FeedBackSoundActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AFeedBackSoundActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void AFeedBackSoundActor::PlayNarr()
{
	//float deleyTime = 5.0f;
	if(soundIDs.Num() != 0)
		deleyTime = stepManager->CallPlayNarrationByID(soundIDs[stepManager->BeforeSelectIndex]);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &AFeedBackSoundActor::SetTimer_PlayNarr, deleyTime + NarrEndDelay, false);
}

void AFeedBackSoundActor::SetTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(0);
	stepManager->CallSetNarrText(headerTextIDs[stepManager->BeforeSelectIndex], textIDs[stepManager->BeforeSelectIndex], true, true);
}

void AFeedBackSoundActor::SetNarrationPaused(bool IsPlay)
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

void AFeedBackSoundActor::SetTimer_PlayNarr()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SetTimer_PlayNarr"));
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	stepManager->NextStep();
}
