// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/DataActors/TotalFeedbackPrintActor.h"
#include "Manager/StepManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void ATotalFeedbackPrintActor::CmsSectionMovement()
{
	GetWorldTimerManager().PauseTimer(Handle);

	GetWorldTimerManager().ClearTimer(Handle);
}

void ATotalFeedbackPrintActor::SetButtonTextToWidget()
{
	SetPrintText();
}

void ATotalFeedbackPrintActor::SetPrintText()
{
	TotalText += stepManager->TotalFeedBackText[index];

	if (index < stepManager->TotalFeedBackText.Num() - 1)
		TotalText += "\n";

	stepManager->CallSetWidgetSwitchIndex(0);
	stepManager->CallSetNarrText("", TotalText, false, index == stepManager->TotalFeedBackText.Num() - 1 ? true : false);

	GetWorldTimerManager().SetTimer(Handle, this, &ATotalFeedbackPrintActor::SetTimer_PrintText, index == stepManager->TotalFeedBackText.Num() - 1 ? 0.1f : TextDelay, false);
}

void ATotalFeedbackPrintActor::SetTimer_PrintText()
{
	GetWorldTimerManager().ClearTimer(Handle);

	if (index < stepManager->TotalFeedBackText.Num() - 1)
	{
		index++;
		SetPrintText();
	}
	else
	{
		SetWidgetInterControl(true);
	}
}
