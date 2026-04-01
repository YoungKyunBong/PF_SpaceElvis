// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/MultFeedBackTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"

void AMultFeedBackTextActor::SetTextToWidget(FString TextID)
{
	stepManager->CallSetWidgetSwitchIndex(6);
	stepManager->CallSetNarrText("", TextID, true, true);
}

void AMultFeedBackTextActor::SetButtonTextToWidget()
{
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextID, ButtonTextID, false);

	stepManager->InterMovieIndex.Empty();
}

void AMultFeedBackTextActor::SetBeforeSelectIndex(FSelectButton selectButton)
{
	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		//if (ButtonTextID[i].feedBackText == selectButton.feedBackText && ButtonTextID[i].movieType == selectButton.movieType)
		if (ButtonTextID[i].movieType == selectButton.movieType)
		{
			stepManager->InterMovieIndex.Add(i);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), i));
		}
	}
	
	if (stepManager->InterMovieIndex.Num() == NextStepMaxCount)
	{
		//stepManager->InterMovieIndex.Empty();
		stepManager->CallWidgetVisible(ESlateVisibility::Hidden);
		stepManager->NextStep();
	}
	else
	{
		stepManager->CallWidgetVisible(ESlateVisibility::Visible);
	}
}