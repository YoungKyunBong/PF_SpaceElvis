// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/StartLoginWidget.h"
#include "WidgetActor/MainWidget.h"

void UStartLoginWidget::Init(UMainWidget* _mainWidget)
{
	mainWidget = _mainWidget;
}

void UStartLoginWidget::PrintLoginCheck(bool isSuccess)
{
	if (isSuccess)
	{
		PrintLoginSuccess();
		StatusText->SetText(FText::FromString(TEXT("로그인에 성공했습니다!")));
	}
	else
	{
		PrintLoginFail();
		StatusText->SetText(FText::FromString(TEXT("로그인에 실패했습니다!\n비밀번호를 확인해주세요.")));
	}
}

void UStartLoginWidget::Call_Login_OnClick()
{
	mainWidget->SendStartLogin(pinText);
}

void UStartLoginWidget::ChangeWidgetIndex()
{
	mainWidget->ChangeWidgetIndex(ClinetLogin::SELECT_LOGIN);
}
