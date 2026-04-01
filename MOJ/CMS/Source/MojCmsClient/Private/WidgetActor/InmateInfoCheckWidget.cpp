// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/InmateInfoCheckWidget.h"
#include "WidgetActor/InmateWidget.h"

void UInmateInfoCheckWidget::Init(UInmateWidget* _inmateWidget)
{
	InmateWidget = _inmateWidget;
}

void UInmateInfoCheckWidget::SetTextDataClear()
{
	EditableTextBox_InmateName->SetText(FText::FromString(TEXT("")));
	EditableTextBox_InmateNum->SetText(FText::FromString(TEXT("")));
	EditableTextBox_InmateIdentyNum->SetText(FText::FromString(TEXT("")));
	EditableTextBox_InmateRegistDay->SetText(FText::FromString(TEXT("")));
	EditableTextBox_CrimeType->SetText(FText::FromString(TEXT("")));
	EditableTextBox_SituationNum->SetText(FText::FromString(TEXT("")));
	EditableTextBox_SessionNum->SetText(FText::FromString(TEXT("")));
}

void UInmateInfoCheckWidget::SetInmateCheckInfo()
{
	EditableTextBox_InmateName->SetText(FText::FromString(TEXT("홍길동")));
	EditableTextBox_InmateNum->SetText(FText::FromString(TEXT("1111"))); 
	EditableTextBox_InmateIdentyNum->SetText(FText::FromString(TEXT("123456-7890123")));
	EditableTextBox_InmateRegistDay->SetText(FText::FromString(TEXT("2025-07-17 16:51:49")));
	EditableTextBox_CrimeType->SetText(FText::FromString(TEXT("성폭력")));
	EditableTextBox_SituationNum->SetText(FText::FromString(TEXT("5번")));
	EditableTextBox_SessionNum->SetText(FText::FromString(TEXT("1회기")));
}

void UInmateInfoCheckWidget::Call_Next_OnClick()
{
	InmateWidget->ChangeWidgetIndex(ProcessInmateLogin::DEVICE_CHECK);

	InmateWidget->SetBackSpaceText_InmateWidget(TEXT(""));
}
