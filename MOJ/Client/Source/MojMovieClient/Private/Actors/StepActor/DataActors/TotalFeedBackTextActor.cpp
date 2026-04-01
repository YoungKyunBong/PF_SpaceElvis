// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/TotalFeedBackTextActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void ATotalFeedBackTextActor::ReplayStep_Implementation(FSelectButton selectButton)
{
	FString WordFirst = stepManager->GetNarrText(WordFirstID);
	FString FeedText = stepManager->GetNarrText(selectButton.feedBackText);
	FString WordEnd = stepManager->GetNarrText(WordEndID);

	stepManager->TotalFeedBackText.Add(WordFirst + FeedText + WordEnd);

	for (int i = 0; i < ButtonTextID.Num(); i++)
	{
		if (ButtonTextID[i].feedBackText == selectButton.feedBackText && ButtonTextID[i].movieType == selectButton.movieType)
		{
			stepManager->BeforeSelectIndex = i;
		}
	}

	stepManager->NextStep();
}

void ATotalFeedBackTextActor::SetButtonTextToWidget()
{
	SetWidgetInterControl(true);
	//BlurActor->SetActorHiddenInGame(false);
	stepManager->CallSetWidgetSwitchIndex(1);
	stepManager->CallInmateSelectButton(HeaderTextID, ButtonTextID, false);
}
