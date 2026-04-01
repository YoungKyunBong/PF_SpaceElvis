// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterRequestMovieActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AAfterRequestMovieActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void AAfterRequestMovieActor::SetTextToWidget(FString TextID)
{
	SetWidgetInterControl(true);
	stepManager->CallSetWidgetSwitchIndex(6);
	stepManager->CallSetNarrText("", TextID, true, false);
}

void AAfterRequestMovieActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextID, ButtonTextID, false);
}

void AAfterRequestMovieActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].movieType != selectButton.movieType)
		{
			NoneSelectButtonID = ButtonTextID[i];
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SetBeforeSelectIndex %d"), NoneSelectButtonID.movieType));
		}
		else
		{
			SelectButtonID = ButtonTextID[i];
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SetBeforeSelectIndex %d"), SelectButtonID.movieType));
		}
	}

	Call_PlayMovie();
}

void AAfterRequestMovieActor::ChangeScene()
{
	if (isStart)
		stepManager->CallChangeMovieScene(SelectButtonID.movieType);
	else
		stepManager->CallChangeMovieScene(NoneSelectButtonID.movieType);
}

void AAfterRequestMovieActor::SetMovieDelayPaused(bool IsPlay)
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

void AAfterRequestMovieActor::SelectMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &AAfterRequestMovieActor::SetTimer_SelectMovieDelay, movieTime, false);
}

void AAfterRequestMovieActor::NoneSelectMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &AAfterRequestMovieActor::SetTimer_NoneSelectMovieDelay, movieTime, false);
}

void AAfterRequestMovieActor::PlayMovie_Implementation()
{
	SetWidgetInterControl(false);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);

	if (isStart)
		SelectMovieDelay();
	else
		NoneSelectMovieDelay();
}

void AAfterRequestMovieActor::SetTimer_SelectMovieDelay()
{
	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AAfterRequestMovieActor::SetTimer_SelectStepDelay, NarrEndDelay, false);
}

void AAfterRequestMovieActor::SetTimer_NoneSelectMovieDelay()
{
	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AAfterRequestMovieActor::SetTimer_NextStepDelay, NarrEndDelay, false);
}

void AAfterRequestMovieActor::SetTimer_SelectStepDelay()
{
	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	SetTextToWidget(NoneSelectButtonID.feedBackText);
	isStart = false;
}

void AAfterRequestMovieActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));
	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}
