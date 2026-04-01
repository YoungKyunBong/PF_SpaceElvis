// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/CardTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void ACardTextActor::ReplayStep_Implementation(FSelectButton selectButton)
{
	FeedBackText = stepManager->GetNarrText(selectButton.feedBackText);
	FeedBackTextSub = stepManager->GetNarrText(selectButton.feedBackText_Sub);
}

void ACardTextActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void ACardTextActor::ChangeScene(MovieSceneType movieType)
{
	stepManager->CallChangeMovieScene(movieType);
}

void ACardTextActor::SetButtonTextToWidget()
{
	SetWidgetInterControl(true);
	stepManager->CallSetWidgetSwitchIndex(8);
	stepManager->CallInmateKeywordCardButton(ButtonTextID);
}

void ACardTextActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &ACardTextActor::SetTimer_MovieDelay, movieTime, false);
}

void ACardTextActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		stepManager->CallMoviePause();
		GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
	}
	else
	{
		stepManager->CallMoviePlay();
		GetWorldTimerManager().UnPauseTimer(MovieDelay_Handle);
	}
}

void ACardTextActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].movieType == selectButton.movieType)
		{
			stepManager->BeforeSelectIndex = i;
		}
	}
}

void ACardTextActor::SetTimer_MovieDelay()
{
	stepManager->CallMoviePause();
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	if (processIndex < ButtonTextID.Num() - 1)
	{
		GetWorldTimerManager().SetTimer(NextStep_Handle, this, &ACardTextActor::SetTimer_AnotherStepDelay, NarrEndDelay, false);
	}
	else
	{
		stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
		GetWorldTimerManager().SetTimer(NextStep_Handle, this, &ACardTextActor::SetTimer_NextStepDelay, NarrEndDelay, false);
	}
}

void ACardTextActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));

	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}

void ACardTextActor::SetTimer_AnotherStepDelay()
{
	TempClose();
	processIndex++;
	stepManager->CallSetWidgetSwitchIndex(8);
	Call_WidgetInterControl(true);
}
