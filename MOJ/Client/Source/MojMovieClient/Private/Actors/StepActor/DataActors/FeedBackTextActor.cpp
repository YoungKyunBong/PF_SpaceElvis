// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/FeedBackTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void AFeedBackTextActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void AFeedBackTextActor::PlayNarr(FString SoundID)
{
	float deleyTime = 0.0f;
	if(!SoundID.IsEmpty())
		deleyTime = stepManager->CallPlayNarrationByID(SoundID);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &AFeedBackTextActor::SetTimer_PlayNarr, deleyTime + NarrEndDelay, false);
}

void AFeedBackTextActor::WrongNarr(FString SoundID)
{
	float deleyTime = 0.0f;

	if(!IsVisibleNarrNextButton)
		deleyTime = 2.0f;

	if (!SoundID.IsEmpty())
		deleyTime = stepManager->CallPlayNarrationByID(SoundID);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &AFeedBackTextActor::SetTimer_WrongNarr, deleyTime + NarrEndDelay, false);
}

void AFeedBackTextActor::SetTextToWidget(FString TextID)
{
	stepManager->CallSetWidgetSwitchIndex(0);
	stepManager->CallSetNarrText("", TextID, true, IsVisibleNarrNextButton);
}

void AFeedBackTextActor::SetButtonTextToWidget()
{
	//stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextID, ButtonTextID, IsVisibleNextButton);
}

void AFeedBackTextActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].feedBackText == selectButton.feedBackText && ButtonTextID[i].movieType == selectButton.movieType)
		{
			stepManager->BeforeSelectIndex = i;
		}
	}
}

void AFeedBackTextActor::SetTimer_PlayNarr()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);

	//if(!UKismetMathLibrary::NearlyEqual_FloatFloat(FeedBackDuration, 0.0f))
	stepManager->NextStep();
}

void AFeedBackTextActor::SetTimer_WrongNarr()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->CallSetWidgetSwitchIndex(1);
}
