// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterRequestTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AAfterRequestTextActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void AAfterRequestTextActor::SetTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(6);
	stepManager->CallSetNarrText("", AskTextID.feedBackText, true, false);
}

void AAfterRequestTextActor::ChangeScene()
{
	SetWidgetInterControl(false);

	stepManager->CallChangeMovieScene(AskTextID.movieType);
}

void AAfterRequestTextActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		stepManager->CallMoviePause();
		GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
		GetWorldTimerManager().PauseTimer(NextStep_Handle);
	}
	else
	{
		stepManager->CallMoviePlay();
		GetWorldTimerManager().UnPauseTimer(MovieDelay_Handle);
		GetWorldTimerManager().UnPauseTimer(NextStep_Handle);
	}
}

void AAfterRequestTextActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &AAfterRequestTextActor::SetTimer_MovieDelay, movieTime, false);
}

void AAfterRequestTextActor::SetTimer_MovieDelay()
{
	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AAfterRequestTextActor::SetTimer_NextStepDelay, NarrEndDelay, false);
}

void AAfterRequestTextActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));
	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}
