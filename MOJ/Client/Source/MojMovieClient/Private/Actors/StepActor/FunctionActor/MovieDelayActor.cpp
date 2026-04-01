// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/MovieDelayActor.h"
#include "Manager/StepManager.h"

void AMovieDelayActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	//if(IsNextStep)
	//	GetWorldTimerManager().SetTimer(NextSetting_Handle, this, &AMovieDelayActor::SetTimer_NextSetting, movieTime + NarrEndDelay, false);

	GetWorldTimerManager().SetTimer(MovieDelay_Handle, this, &AMovieDelayActor::SetTimer_MovieDelay, movieTime - PauseTime, false);

	if (IsReturn)
		stepManager->SetReturnStepIndex();
}

void AMovieDelayActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		GetWorldTimerManager().PauseTimer(NextSetting_Handle);
		GetWorldTimerManager().PauseTimer(MovieDelay_Handle);
		stepManager->CallMoviePause();
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(NextSetting_Handle);
		GetWorldTimerManager().UnPauseTimer(MovieDelay_Handle);
		stepManager->CallMoviePlay();
	}
}

void AMovieDelayActor::ReturnStep_Implementation()
{
	isReturn = true;
	if (!GetWorldTimerManager().IsTimerActive(NextSetting_Handle))
	{
		stepManager->NextStep();
	}
}

void AMovieDelayActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(NextSetting_Handle);
	GetWorldTimerManager().PauseTimer(MovieDelay_Handle);

	GetWorldTimerManager().ClearTimer(NextStep_Handle);
	GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
}

void AMovieDelayActor::SetTimer_NextSetting()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 1.0f));
	GetWorldTimerManager().ClearTimer(NextSetting_Handle);

	if (isReturn)
	{
		TempClose();
		GetWorldTimerManager().ClearTimer(MovieDelay_Handle);

		GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AMovieDelayActor::SetTimer_NextStepDelay, NarrEndDelay, false);
	}
}

void AMovieDelayActor::SetTimer_MovieDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Debug %f"), 2.0f));

	//if (!IsNextStep)
	{
		stepManager->CallMoviePause();
		GetWorldTimerManager().ClearTimer(MovieDelay_Handle);
	}

	GetWorldTimerManager().SetTimer(NextStep_Handle, this, &AMovieDelayActor::SetTimer_NextStepDelay, NarrEndDelay, false);
}

void AMovieDelayActor::SetTimer_NextStepDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Debug %f"), 3.0f));

	TempClose();
	GetWorldTimerManager().ClearTimer(NextStep_Handle);

	stepManager->NextStep();
}
