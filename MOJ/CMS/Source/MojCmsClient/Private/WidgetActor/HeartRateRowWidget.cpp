// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/HeartRateRowWidget.h"
#include "Components/TextBlock.h"

void UHeartRateRowWidget::Setup(const FString& InTimeText, const FString& InBpmText)
{
	if (Txt_Time)
	{
		Txt_Time->SetText(FText::FromString(InTimeText));
	}

	if (Txt_Bpm)
	{
		Txt_Bpm->SetText(FText::FromString(InBpmText));
	}
}
