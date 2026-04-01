// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/BackSpaceWidget.h"
#include "Components/TextBlock.h"

void UBackSpaceWidget::SetText(FString _text)
{
	TextBlock->SetText(FText::FromString(_text));
}
