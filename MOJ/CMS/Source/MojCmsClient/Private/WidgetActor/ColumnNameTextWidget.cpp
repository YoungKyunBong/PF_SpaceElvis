// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/ColumnNameTextWidget.h"
#include "WidgetActor/ValueTextWidget.h"
#include "Components/HorizontalBox.h"

void UColumnNameTextWidget::Init(UProcessInmateWidget* _InmateWidget)
{
	InmateWidget = _InmateWidget;
}

void UColumnNameTextWidget::RecvSearchData(const TArray<FString> datas, const TArray<FVector2D> Vector2DSizes, const TArray<FSlateFontInfo> SlateFontInfos)
{
	for (int i = 0; i < datas.Num(); i++)
	{
		auto* tempWidget = CreateWidget<UValueTextWidget>(GetOwningPlayer(), TUValueTextWidget);
		tempWidget->CreateObject(datas[i], Vector2DSizes[i], SlateFontInfos[i]);

		SetWidgetData(tempWidget);
	}
}