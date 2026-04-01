// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InmateSelectEmotionButtonWidget.h"
#include "Widget/InmateSelectEmotionMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInmateSelectEmotionButtonWidget::DataInit(UInmateSelectEmotionMainWidget* _inmateSelectEmotionMainWidget, FSelectButton buttonType)
{
	MainWidget = _inmateSelectEmotionMainWidget;
	selectButtonType = buttonType;
}

void UInmateSelectEmotionButtonWidget::Call_SelectButton_OnClick()
{
	this->SetIsEnabled(false);
	switch (selectButtonType.buttonType)
	{
	case SelectButtonType::WrongNarr:
	{
		SetWrongImage();
	}
	case SelectButtonType::Positive:
	{
		this->SetIsEnabled(false);
	}
	break;
	default:
		break;
	}

	MainWidget->CallSelectButton(selectButtonType);
}
