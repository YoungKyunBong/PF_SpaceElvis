// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/StopTraningActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AStopTraningActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void AStopTraningActor::SetTextToWidget(FString TextID)
{
	stepManager->CallSetWidgetSwitchIndex(0);
	stepManager->CallSetNarrText("", TextID, true, true);
}

void AStopTraningActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton("", OptionButtonTextID, false);
}

void AStopTraningActor::Call_PlayMovie(ProcessIconType _type)
{
	PlayMovie(_type);
	stepManager->CallWidgetVisible(ESlateVisibility::Hidden);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), stepManager->MultSelectMovieIndex.Num()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), stepManager->MultNoneSelectMovieIndex.Num()));
}

void AStopTraningActor::ChangeScene()
{
	switch (processIconType)
	{
	case ProcessIconType::ProcessStart:
	{
		if (isSelect)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), 1));
			stepManager->CallChangeMovieScene(startSceneTypes[stepManager->MultSelectMovieIndex[processIndex]]);
		}
		else
			stepManager->CallChangeMovieScene(startSceneTypes[stepManager->MultNoneSelectMovieIndex[processIndex]]);
	}
		break;
	case ProcessIconType::ProcessStop:
		stepManager->CallChangeMovieScene(stopStartSceneTypes);
		break;
	case ProcessIconType::ProcessPick:
	{
		if(isSelect)
			stepManager->CallChangeMovieScene(cureSceneTypes[stepManager->MultSelectMovieIndex[processIndex]]);
		else
			stepManager->CallChangeMovieScene(cureSceneTypes[stepManager->MultNoneSelectMovieIndex[processIndex]]);
	}
		break;
	default:
		break;
	}
}

void AStopTraningActor::SetMovieDelay()
{
	float movieTime = stepManager->CallMediaPlayTime();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), movieTime));

	GetWorldTimerManager().SetTimer(Handle, this, &AStopTraningActor::SetTimer_MovieDelay, movieTime + NarrEndDelay, false);
}

void AStopTraningActor::SetMovieDelayPaused(bool IsPlay)
{
	stepManager->CallSetNarrationPaused(IsPlay);

	if (IsPlay)
	{
		stepManager->CallMoviePause();

	}
	else
	{
		stepManager->CallMoviePlay();
	}

	if (IsPlay)
	{
		GetWorldTimerManager().PauseTimer(Handle);
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(Handle);
	}
}

void AStopTraningActor::SetThinkText(ProcessIconType _type)
{
	processIconType = _type;
	if (isSelect)
	{
		SetTextToWidget(ThinkButtonTextID[stepManager->MultSelectMovieIndex[processIndex]].feedBackText);
		PlayNarr(ThinkButtonTextID[stepManager->MultSelectMovieIndex[processIndex]].feedBackSound);
	}
	else
	{
		SetTextToWidget(ThinkButtonTextID[stepManager->MultNoneSelectMovieIndex[processIndex]].feedBackText);
		PlayNarr(ThinkButtonTextID[stepManager->MultNoneSelectMovieIndex[processIndex]].feedBackSound);
	}
}

void AStopTraningActor::SetOptionText(ProcessIconType _type)
{
	processIconType = _type;
	SetButtonTextToWidget();
}

void AStopTraningActor::PlayNarr(FString SoundID)
{
	float deleyTime = stepManager->CallPlayNarrationByID(SoundID);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PlayNarr"));

	GetWorldTimerManager().SetTimer(Handle, this, &AStopTraningActor::SetTimer_PlayNarr, deleyTime + NarrEndDelay, false);
}

void AStopTraningActor::SetNarrationPaused(bool IsPlay)
{
}

void AStopTraningActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < OptionButtonTextID.Num(); i++)
	{
		if (OptionButtonTextID[i].feedBackText == selectButton.feedBackText)
		{
			CureIndex = i;
		}
	}
}

void AStopTraningActor::PlayMovie_Implementation(ProcessIconType _type)
{
	processIconType = _type;
}

void AStopTraningActor::SetTimer_MovieDelay()
{
	GetWorldTimerManager().ClearTimer(Handle);

	switch (processIconType)
	{
	case ProcessIconType::ProcessStart:
	case ProcessIconType::ProcessStop:
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), 1));
		stepManager->CallWidgetVisible(ESlateVisibility::Visible);
		stepManager->CallSetWidgetSwitchIndex(3);
	}
		break;
	case ProcessIconType::ProcessPick:
	{
		if (isSelect)
		{
			if (processIndex < stepManager->MultSelectMovieIndex.Num() - 1)
			{
				processIndex++;
				PlayMovie(ProcessIconType::ProcessStart);
			}
			else
			{
				processIndex = 0;
				stepManager->CallSetWidgetSwitchIndex(6);
				isSelect = false;
			}
		}
		else
		{
			if (processIndex < stepManager->MultNoneSelectMovieIndex.Num() - 1)
			{
				processIndex++;
				PlayMovie(ProcessIconType::ProcessStart);
			}
			else
			{
				stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
				stepManager->NextStep();
			}
		}
	}
		break;
	default:
		break;
	}
}

void AStopTraningActor::SetTimer_PlayNarr()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->CallSetWidgetSwitchIndex(3);
}
