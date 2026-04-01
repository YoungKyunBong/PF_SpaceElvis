// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/SwitchButtonWidget.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Styling/SlateTypes.h"

void USwitchButtonWidget::SetText(UTextBlock* _textBlock)
{
	_textBlock->SetText(FText::FromString(text));
}

void USwitchButtonWidget::SetCanvasSize(UCanvasPanelSlot* _canvasSlot)
{
	_canvasSlot->SetSize(canvasSize);
}

void USwitchButtonWidget::SetTextFont(UTextBlock* _textBlock)
{
	_textBlock->SetFont(textFontInfo);
}

void USwitchButtonWidget::SetButtonImage(UButton* SwitchButton)
{
	FButtonStyle ButtonStyle = SwitchButton->WidgetStyle;

	ButtonStyle.Normal.SetResourceObject(SwitchButton_NormalImage);

	ButtonStyle.Hovered.SetResourceObject(SwitchButton_HoverImage);

	ButtonStyle.Pressed.SetResourceObject(SwitchButton_PressImage);

	SwitchButton->SetStyle(ButtonStyle);
}
