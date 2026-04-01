// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/ValueTextWidget.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

void UValueTextWidget::CreateObject(FString _text, FVector2D _canvasSize, FSlateFontInfo _textFontInfo)
{
	text = _text;
	canvasSize = _canvasSize;
	textFontInfo = _textFontInfo;
	SetWidgetData();
}

void UValueTextWidget::SetText(FString data)
{
	text = data;
	SetTextData();
}
