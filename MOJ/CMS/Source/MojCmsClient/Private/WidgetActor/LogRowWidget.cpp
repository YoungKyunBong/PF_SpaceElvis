// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/LogRowWidget.h"



void ULogRowWidget::SetData(const FLogItem& Data)
{
	Txt_Type->SetText(FText::FromString(Data.Type));
	Txt_TimeActor->SetText(
		FText::FromString(FString::Printf(TEXT("%s · %s"), *Data.Time, *Data.Actor))
	);
}
