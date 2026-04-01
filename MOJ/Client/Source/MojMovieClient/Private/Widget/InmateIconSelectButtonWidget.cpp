// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InmateIconSelectButtonWidget.h"
#include "Widget/MainWidget.h"

void UInmateIconSelectButtonWidget::Init(UMainWidget* _mainWidget)
{
	MainWidget = _mainWidget;
}

void UInmateIconSelectButtonWidget::Call_SetIconButton(CheckIconType _type)
{
	switch (_type)
	{
	case CheckIconType::CheckStop:
		PlayAnimStop();
		break;
	case CheckIconType::CheckThink:
		PlayAnimThink();
		break;
	case CheckIconType::CheckOptions:
		PlayAnimOptions();
		break;
	case CheckIconType::CheckPick:
		PlayAnimPick();
		break;
	default:
		break;
	}
}

void UInmateIconSelectButtonWidget::Call_IconButton_OnClick(CheckIconType _type)
{
	switch (_type)
	{
	case CheckIconType::CheckStop:
		PlayAnimStop();
		break;
	case CheckIconType::CheckThink:
		PlayAnimThink();
		break;
	case CheckIconType::CheckOptions:
		PlayAnimOptions();
		break;
	case CheckIconType::CheckPick:
		PlayAnimPick();
		break;
	default:
		break;
	}
	MainWidget->CallIconButton();
}
