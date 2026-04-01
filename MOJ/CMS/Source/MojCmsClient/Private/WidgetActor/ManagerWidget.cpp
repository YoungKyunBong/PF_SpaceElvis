// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/ManagerWidget.h"
#include "WidgetActor/MainWidget.h"
#include "WidgetActor/ProcessInmateWidget.h"
#include "WidgetActor/BackSpaceWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UManagerWidget::Init(UMainWidget* _mainWidget)
{
	mainWidget = _mainWidget;
}

void UManagerWidget::ProcessChangePW(bool isSuccess)
{
	if (isSuccess)
	{
		CurrPwText = NewPwText = NewPwCheckText = "";
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("비밀번호가 변경되었습니다!")));
		TextBlock_ChangePW->SetColorAndOpacity(FLinearColor::White);
	}
	else
	{
		CurrPwText = "";
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("현재 비밀번호가 다릅니다.\n다시 입력해 주세요.")));
		TextBlock_ChangePW->SetColorAndOpacity(FLinearColor::Red);
	}
}

void UManagerWidget::ChangeWidgetIndex(ProcessManager _type)
{
	WidgetSwitcher->SetActiveWidgetIndex(_type);
}

void UManagerWidget::SetBackSpaceText_ManagerWidget(FString _text)
{
	BackSpaceWidget->SetText(_text);
}

#pragma region RECVINFO

void UManagerWidget::RecvInmateADD(SEND_TEXT_TYPE printType) { ProcessInmateWidget->RecvInmateADD(printType); }
void UManagerWidget::RecvInmateUpdate(SEND_TEXT_TYPE type, FString data) { ProcessInmateWidget->RecvInmateUpdate(type, data); }
void UManagerWidget::RecvInmateSearch(FString data) { ProcessInmateWidget->RecvInmateSearch(data); }

#pragma endregion

#pragma region SENDINFO

void UManagerWidget::InmateADD(FString InmateNum, FString InmateName) {	mainWidget->SendInmateADD(InmateNum, InmateName); }
void UManagerWidget::InmateSearch() { mainWidget->SendInmateSearch(); }
void UManagerWidget::InmateUpdate(INMATE_UPDATE_TYPE _type, FString prisonerNum, FString data) { mainWidget->SendInmateUpdate(_type, prisonerNum, data); }

#pragma endregion


void UManagerWidget::Call_BackSpace_OnClick()
{
	switch (currSwitcherWidget)
	{
	case MANAGER_DEFAULT:
	{
		mainWidget->ChangeWidgetIndex(ClinetLogin::SELECT_LOGIN);
	}
		break;
	case CHANGE_PW:
	{
		CurrPwText = NewPwText = NewPwCheckText = "";
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("")));
	}
		break;
	default:
		break;
	}

	currSwitcherWidget = ProcessManager::MANAGER_DEFAULT;
	WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

	BackSpaceWidget->SetText(TEXT("관리자 페이지"));
}

void UManagerWidget::Call_ChangePW_OnClick()
{
	currSwitcherWidget = ProcessManager::CHANGE_PW;
	WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

	BackSpaceWidget->SetText(TEXT("비밀번호 변경"));
}

void UManagerWidget::Call_SetChangePW_OnClick()
{
	TextBlock_ChangePW->SetColorAndOpacity(FLinearColor::Red);
	if (CurrPwText == "")
	{
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("현재 비밀번호를 입력해 주세요")));
	}
	else if (NewPwText == "")
	{
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("새 비밀번호를 입력해 주세요")));
	}
	else if (NewPwCheckText == "")
	{
		TextBlock_ChangePW->SetText(FText::FromString(TEXT("새 비밀번호 확인을 입력해 주세요")));
	}
	else
	{
		mainWidget->SendChangePW(CurrPwText, NewPwText);
	}
}

void UManagerWidget::Call_Inmate_OnClick()
{
	currSwitcherWidget = ProcessManager::PROCESS_INMATE;
	WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

	BackSpaceWidget->SetText(TEXT(""));
}
