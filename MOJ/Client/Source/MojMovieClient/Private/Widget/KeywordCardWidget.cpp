// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/KeywordCardWidget.h"
#include "Widget/MainWidget.h"

void UKeywordCardWidget::Init(UMainWidget* _mainWidget)
{
	MainWidget = _mainWidget;
}

void UKeywordCardWidget::CallSelectButton(FSelectButton text)
{
	MainWidget->CallSelectButton(text);
}
