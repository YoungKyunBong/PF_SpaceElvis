// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InmateSelectMainWidget.h"
#include "Widget/MainWidget.h"
#include "Widget/InmateSelectButtonWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UInmateSelectMainWidget::Init(UMainWidget* _mainWidget)
{
	MainWidget = _mainWidget;
}

void UInmateSelectMainWidget::InmateSelectButton(FString _HeaderText, const TArray<FSelectButton>& buttonText, bool _IsVisibleNextButton)
{
	isVisibleNextButton = _IsVisibleNextButton;

	NextButtonCanvas->SetVisibility(_IsVisibleNextButton ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	for(int i = 0; i < HorizonBoxs.Num(); i++)
		HorizonBoxs[i]->ClearChildren();

	HeaderText = _HeaderText;

	for (int i = 0, j = -1; i < buttonText.Num(); i++)
	{
		auto* tempWidget = CreateWidget<UInmateSelectButtonWidget>(GetOwningPlayer(), TUInmateSelectButtonWidget);
		tempWidget->DataInit(this, buttonText[i]);

		if (i % 2 == 0)
		{
			j++;
		}
		HorizonBoxs[j]->AddChild(tempWidget);
	}

	//MainCanvasSlot->SetOffsets(FMargin(0.0f, 0.0f, 1000.0f, buttonText.Num() * 100));

	SetChildFill(_HeaderText != "" ? true : false, buttonText.Num());
}

void UInmateSelectMainWidget::CallSelectButton(FSelectButton text)
{
	if (isVisibleNextButton)
	{
		NextButtonCanvas->SetIsEnabled(true);
		return;
	}

	MainWidget->CallSelectButton(text);
}

void UInmateSelectMainWidget::Call_NextButton_OnClick()
{
	MainWidget->CallNextButton();
	//NextButtonCanvas->SetVisibility(ESlateVisibility::Hidden);
}
