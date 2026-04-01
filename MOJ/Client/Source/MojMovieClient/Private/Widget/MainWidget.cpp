// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Manager/WidgetManager.h"
#include "Widget/InmateSelectButtonWidget.h"
#include "Widget/InmateSelectMainWidget.h"
#include "Widget/InmateSelectEmotionMainWidget.h"
#include "Widget/KeywordCardWidget.h"
#include "Widget/InmateIconSelectButtonWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"

void UMainWidget::Init(AWidgetManager* _WidgetManager)
{
	WidgetManager = _WidgetManager;
}

void UMainWidget::SetWidgetSwitchIndex(int index)
{
	this->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher->SetActiveWidgetIndex(index);
}

void UMainWidget::SetNarrText(FString _HeaderText, FString _text, bool _IsVisibleNarrNextButton)
{
	this->SetVisibility(ESlateVisibility::Visible);
	NarrNextButtonCanvas->SetVisibility(_IsVisibleNarrNextButton ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	HeaderText = _HeaderText;
	Text = _text;

	SetFillHeaderText(_HeaderText != "" ? true : false);
}

void UMainWidget::InmateSelectButton(FString _HeaderText, const TArray<FSelectButton>& buttonText, bool _IsVisibleNextButton)
{
	this->SetVisibility(ESlateVisibility::Visible);

	if (buttonText[0].emojiType == FEmojiType::NoneEmotion)
	{
		InmateSelectMainWidget->InmateSelectButton(_HeaderText, buttonText, _IsVisibleNextButton);
		SetWidgetSwitchIndex(1);
	}
	else
	{
		InmateSelectEmotionMainWidget->InmateSelectButton(_HeaderText, buttonText, _IsVisibleNextButton);
		SetWidgetSwitchIndex(9);
	}
}

void UMainWidget::InmateKeywordCardButton(const TArray<FSelectButton>& buttonText)
{
	KeywordCardWidget->CallDataSetting(buttonText);
}

void UMainWidget::SetWidgetVisible(ESlateVisibility option)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NextStep"));
	this->SetVisibility(option);
}

void UMainWidget::SetIconType(CheckIconType _checkIconType)
{
	InmateIconSelectButtonWidget->Call_SetIconButton(_checkIconType);
}

void UMainWidget::CallSelectButton(FSelectButton text)
{
	switch (text.buttonType)
	{
	case SelectButtonType::Normal:
	{	
		this->SetVisibility(ESlateVisibility::Hidden);
		WidgetManager->CallNextStep();
	}
	break;
	case SelectButtonType::WrongNarr:
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		WidgetManager->CallReplayStep(text);
	}
	break;
	case SelectButtonType::Positive:
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		WidgetManager->CallReplayStep(text);
	}
	case SelectButtonType::Negative:
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		WidgetManager->CallReplayStep(text);
	}
	break;
	case SelectButtonType::FeedBack:
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		WidgetManager->CallReplayStep(text);
	}
	break;
	default:
		break;
	}
}

void UMainWidget::CallIconButton()
{
	WidgetManager->CallRewindStep();
	this->SetVisibility(ESlateVisibility::Hidden);
	WidgetManager->CallNextStep();
}

void UMainWidget::CallNextButton()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	WidgetManager->CallNextStep();
}

void UMainWidget::Call_InmateReadyButton_OnClick()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	WidgetManager->CallNextStep();
}

void UMainWidget::Call_SelectYes_OnClick()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), 1));
	WidgetManager->CallRewindStep();
}

