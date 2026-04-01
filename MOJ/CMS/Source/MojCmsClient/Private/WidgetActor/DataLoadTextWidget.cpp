// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/DataLoadTextWidget.h"
#include "WidgetActor/InmateWidget.h"

void UDataLoadTextWidget::Init(UInmateWidget* _inmateWidget)
{
	InmateWidget = _inmateWidget;
}

void UDataLoadTextWidget::Call_SetInmateInfoData()
{
	InmateWidget->CallInmateCheckInfo();
}
