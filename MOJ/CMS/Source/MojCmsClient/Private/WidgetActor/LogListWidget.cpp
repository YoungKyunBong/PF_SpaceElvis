// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/LogListWidget.h"




void ULogListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GM = GetWorld()->GetGameInstance<UGameManager>();
	if (!GM) return;

	GM->OnLogUpdated.AddUObject(this, &ULogListWidget::OnLogUpdated);

	// 테스트용
	GM->CreateDummyLogs();
}

void ULogListWidget::OnLogUpdated()
{
	Rebuild();
}

void ULogListWidget::Rebuild()
{
	if (!SB_LogList || !RowWidgetClass || !GM) return;

	SB_LogList->ClearChildren();

	for (const FLogItem& Item : GM->GetLogItems())
	{
		ULogRowWidget* Row = CreateWidget<ULogRowWidget>(this, RowWidgetClass);
		Row->SetData(Item);
		SB_LogList->AddChild(Row);
	}
}
