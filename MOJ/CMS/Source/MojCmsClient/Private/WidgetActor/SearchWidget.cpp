// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/SearchWidget.h"
#include "WidgetActor/ProcessInmateWidget.h"
#include "WidgetActor/ValueTextWidget.h"
#include "Components/HorizontalBox.h"


void USearchWidget::Init(UProcessInmateWidget* _InmateWidget)
{
	InmateWidget = _InmateWidget;
}

void USearchWidget::RecvSearchData(const TArray<FString> datas, const TArray<FVector2D> Vector2DSizes, const TArray<FSlateFontInfo> SlateFontInfos)
{
	for (int i = 0; i < datas.Num(); i++)
	{
		auto* tempWidget = CreateWidget<UValueTextWidget>(GetOwningPlayer(), TUValueTextWidget);
		tempWidget->CreateObject(datas[i], Vector2DSizes[i], SlateFontInfos[i]);

		valueWidgets.Add(tempWidget);

		SetWidgetData(tempWidget);
	}
}

void USearchWidget::RecvUpdateData(int index, FString data)
{
	valueWidgets[index]->SetText(data);
}

void USearchWidget::Call_InmateData_OnClick()
{
	InmateWidget->GetInmateUpdateData(this);
}
