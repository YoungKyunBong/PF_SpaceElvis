// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/InmateProgramLogWidget.h"

void UInmateProgramLogWidget::SetLogData(FString _currTimeText, FString _logText)
{
	CurrTimeText = _currTimeText;
	LogText = _logText;

	SetWidgetData();
}
