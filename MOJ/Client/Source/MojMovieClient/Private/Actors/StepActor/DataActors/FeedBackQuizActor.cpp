// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/FeedBackQuizActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void AFeedBackQuizActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void AFeedBackQuizActor::ChangeScene(MovieSceneType movieType)
{
	stepManager->CallChangeMovieScene(movieType);
}

void AFeedBackQuizActor::SetButtonTextToWidget()
{
	SetWidgetInterControl(true);
	//BlurActor->SetActorHiddenInGame(false);
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextIDs[stepManager->BeforeSelectIndex], ButtonTextIDs[stepManager->BeforeSelectIndex].InnerArray, false);
}

void AFeedBackQuizActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &AFeedBackQuizActor::SetTimer_MovieDelay, movieTime, false);
}

void AFeedBackQuizActor::SetWrongMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(WrongMovieDelay_Handle, this, &AFeedBackQuizActor::SetTimer_WrongMovieDelay, movieTime, false);
}

void AFeedBackQuizActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		stepManager->CallMoviePause();
		GetWorldTimerManager().PauseTimer(WrongMovieDelay_Handle);
		GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	}
	else
	{
		stepManager->CallMoviePlay();
		GetWorldTimerManager().UnPauseTimer(WrongMovieDelay_Handle);
		GetWorldTimerManager().UnPauseTimer(MovieDelay_Handle);
	}
}

void AFeedBackQuizActor::SetTimer_MovieDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 1.0f));

	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AFeedBackQuizActor::SetTimer_NextStepDelay, NarrEndDelay, false);
}

void AFeedBackQuizActor::SetTimer_WrongMovieDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 2.0f));

	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AFeedBackQuizActor::SetTimer_WrongStepDelay, NarrEndDelay, false);
}

void AFeedBackQuizActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));

	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}

void AFeedBackQuizActor::SetTimer_WrongStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 4.0f));

	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->CallSetWidgetSwitchIndex(1);
	//BlurActor->SetActorHiddenInGame(false);
	SetWidgetInterControl(true);
}
