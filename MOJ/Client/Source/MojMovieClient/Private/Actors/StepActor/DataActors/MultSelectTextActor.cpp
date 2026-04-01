// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/MultSelectTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AMultSelectTextActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void AMultSelectTextActor::SetTextToWidget(FString TextID)
{
	stepManager->CallSetWidgetSwitchIndex(0);
	stepManager->CallSetNarrText("", TextID, true, true);
}

void AMultSelectTextActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton("", ButtonTextID, false);

	MultSelectText.Empty();
}

void AMultSelectTextActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	stepManager->CallWidgetVisible(ESlateVisibility::Visible);
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].feedBackText == selectButton.feedBackText)
		{
			if (stepManager->MultSelectMovieIndex.Num() == 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 3.0f));
				MultSelectText.Add(ButtonTextID[i]);
				stepManager->MultSelectMovieIndex.Add(i);
				break;
			}
			else if (stepManager->MultSelectMovieIndex.Find(i) == -1)
			{
				MultSelectText.Add(ButtonTextID[i]);
				stepManager->MultSelectMovieIndex.Add(i);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 2.0f));
				break;
			}
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), MultSelectText.Num()));

	if(isOnce)
		return;

	if (MultSelectText.Num() == 3)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 1.0f));
		for (int i = 0; i < ButtonTextID.Num(); i++)
		{
			if (!stepManager->MultSelectMovieIndex.Contains(i))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), i));
				MultNoneSelectText.Add(ButtonTextID[i]);
				stepManager->MultNoneSelectMovieIndex.Add(i);
			}
		}

		PlaySelectText();

		isOnce = true;
	}
}

void AMultSelectTextActor::ChangeScene()
{
	if (isStart)
		stepManager->CallChangeMovieScene(sceneTypes[stepManager->MultSelectMovieIndex[processIndex]]);
	else
		stepManager->CallChangeMovieScene(sceneTypes[stepManager->MultNoneSelectMovieIndex[processIndex]]);
}

void AMultSelectTextActor::SetMovieDelayPaused(bool IsPlay)
{
	if (IsPlay)
	{
		stepManager->CallMoviePause();

	}
	else
	{
		stepManager->CallMoviePlay();
	}
}

void AMultSelectTextActor::SetNarrationPaused(bool IsPlay)
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

void AMultSelectTextActor::PlaySelectText()
{
	float deleyTime = stepManager->CallPlayNarrationByID(MultSelectText[processIndex].feedBackSound);

	SetTextToWidget(MultSelectText[processIndex].feedBackText);
	PlayMovie();

	GetWorldTimerManager().SetTimer(Handle, this, &AMultSelectTextActor::CheckNextStep_Select, deleyTime + NarrEndDelay, false);
}

void AMultSelectTextActor::PlayNoneSelectText()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), processIndex));

	float deleyTime = DelayTextTime;

	SetTextToWidget(MultNoneSelectText[processIndex].feedBackText);
	PlayMovie();

	GetWorldTimerManager().SetTimer(Handle, this, &AMultSelectTextActor::CheckNextStep_NoneSelect, deleyTime + NarrEndDelay, false);
}

void AMultSelectTextActor::CheckNextStep_Select()
{
	GetWorldTimerManager().ClearTimer(Handle);
	if (processIndex < MultSelectText.Num() - 1)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), processIndex));
		processIndex++;
		PlaySelectText();
	}
	else
	{
		processIndex = 0;
		stepManager->CallSetWidgetSwitchIndex(6);
			
		isStart = false;
	}
}

void AMultSelectTextActor::CheckNextStep_NoneSelect()
{
	GetWorldTimerManager().ClearTimer(Handle);

	if (processIndex < MultNoneSelectText.Num() - 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), processIndex));
		processIndex++;
		PlayNoneSelectText();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), processIndex));
		stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
		stepManager->NextStep();
	}
}
