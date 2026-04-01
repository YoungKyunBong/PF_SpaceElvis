// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InmateSelectButtonWidget.h"
#include "Widget/InmateSelectMainWidget.h"
#include "Components/TextBlock.h"

void UInmateSelectButtonWidget::DataInit(UInmateSelectMainWidget* _inmateSelectMainWidget, FSelectButton buttonType)
{
	MainWidget = _inmateSelectMainWidget;
	selectButtonType = buttonType;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Debug FontSize : %f"), fontSize));
}

void UInmateSelectButtonWidget::Call_SelectButton_OnClick()
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

