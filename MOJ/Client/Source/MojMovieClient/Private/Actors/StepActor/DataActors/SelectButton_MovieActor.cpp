// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/SelectButton_MovieActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void ASelectButton_MovieActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void ASelectButton_MovieActor::ChangeScene(MovieSceneType movieType)
{
	stepManager->CallChangeMovieScene(movieType);
}

void ASelectButton_MovieActor::SetButtonTextToWidget()
{
	SetWidgetInterControl(true);
	//BlurActor->SetActorHiddenInGame(false);
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextID, ButtonTextID, false);
}

void ASelectButton_MovieActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &ASelectButton_MovieActor::SetTimer_MovieDelay, movieTime, false);
}

void ASelectButton_MovieActor::SetWrongMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(WrongMovieDelay_Handle, this, &ASelectButton_MovieActor::SetTimer_WrongMovieDelay, movieTime, false);
}

void ASelectButton_MovieActor::SetMovieDelayPaused(bool IsPlay)
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

void ASelectButton_MovieActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].movieType == selectButton.movieType)
		{
			stepManager->BeforeSelectIndex = i;
		}
	}
}

void ASelectButton_MovieActor::SetTimer_MovieDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 1.0f));

	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &ASelectButton_MovieActor::SetTimer_NextStepDelay, NarrEndDelay, false);

}

void ASelectButton_MovieActor::SetTimer_WrongMovieDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 2.0f));

	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(WrongMovieDelay_Handle);
	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &ASelectButton_MovieActor::SetTimer_WrongStepDelay, NarrEndDelay, false);
}

void ASelectButton_MovieActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));

	TempClose();
	SetWidgetInterControl(false);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}

void ASelectButton_MovieActor::SetTimer_WrongStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 4.0f));

	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);

	if (ButtonTextID[0].emojiType == FEmojiType::NoneEmotion)
		stepManager->CallSetWidgetSwitchIndex(1);
	else
		stepManager->CallSetWidgetSwitchIndex(9);

	//BlurActor->SetActorHiddenInGame(false);
	SetWidgetInterControl(true);
}
