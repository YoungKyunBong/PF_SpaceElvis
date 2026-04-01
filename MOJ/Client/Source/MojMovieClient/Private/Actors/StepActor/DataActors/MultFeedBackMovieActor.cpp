// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/MultFeedBackMovieActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AMultFeedBackMovieActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);
	GetWorldTimerManager().PauseTimer(NextStep_Handle);

	GetWorldTimerManager().ClearTimer(Handle);
	GetWorldTimerManager().ClearTimer(NextStep_Handle);
}

void AMultFeedBackMovieActor::ChangeScene()
{
	stepManager->CallChangeMovieScene(sceneTypes[stepManager->InterMovieIndex[processIndex]]);
}

void AMultFeedBackMovieActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(Handle, this, &AMultFeedBackMovieActor::SetTimer_MovieDelay, movieTime, false);
}

void AMultFeedBackMovieActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		stepManager->CallMoviePause();
		GetWorldTimerManager().PauseTimer(Handle);
	}
	else
	{
		stepManager->CallMoviePlay();
		GetWorldTimerManager().UnPauseTimer(Handle);
	}
}

void AMultFeedBackMovieActor::SetTimer_MovieDelay()
{
	GetWorldTimerManager().ClearTimer(Handle);
	if (processIndex < stepManager->InterMovieIndex.Num() - 1)
	{
		processIndex++;
		PlayMovie();
	}
	else
	{
		//stepManager->InterMovieIndex.Empty();
		stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
		GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AMultFeedBackMovieActor::SetTimer_NextStepDelay, NarrEndDelay, false);
	}
}

void AMultFeedBackMovieActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));

	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	stepManager->NextStep();
}
