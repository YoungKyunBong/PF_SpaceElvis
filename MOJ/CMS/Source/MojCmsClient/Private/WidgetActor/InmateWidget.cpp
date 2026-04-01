// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetActor/InmateWidget.h"
#include "WidgetActor/MainWidget.h"
#include "WidgetActor/InmateInfoCheckWidget.h"
#include "WidgetActor/DataLoadTextWidget.h"
#include "WidgetActor/DeviceSettingGuideWidget.h"
#include "WidgetActor/MovieControlWidget.h"
#include "WidgetActor/BackSpaceWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UInmateWidget::Init(UMainWidget* _mainWidget)
{
	mainWidget = _mainWidget;
}

void UInmateWidget::PrintLoginCheck(bool isSuccess)
{
	if (isSuccess)
	{
		PrintLoginSuccess();
		StatusText->SetText(FText::FromString(TEXT("로그인에 성공했습니다!")));
	}
	else
	{
		PrintLoginFail();
		StatusText->SetText(FText::FromString(TEXT("로그인에 실패했습니다!\n재소자 번호를 확인해주세요.")));
	}
}

void UInmateWidget::CallInmateCheckInfo()
{
	switch (currSwitcherWidget)
	{
	case INMATE_LOGIN_DEFAULT:
		break;
	case INMATE_INFO_CHECK:
		InmateInfoCheckWidget->SetInmateCheckInfo();
		break;
	case DEVICE_CHECK:
		break;
	case MOVIE_CONTROLL:
		MovieControlWidget->SetInmateDataInfo();
		break;
	case SAVE:
		break;
	default:
		break;
	}
}

void UInmateWidget::ChangeWidgetIndex(ProcessInmateLogin _type)
{
	currSwitcherWidget = _type;
	WidgetSwitcher->SetActiveWidgetIndex(_type);
}

void UInmateWidget::UseDataLoadWidget()
{
	DataLoadTextWidget->OnText();
}

void UInmateWidget::SetBackSpaceText_InmateWidget(FString _text)
{
	BackSpaceWidget->SetText(_text);
}

#pragma region SENDINFO
void UInmateWidget::CmsControllerStart()
{
	mainWidget->SendCmsControllerStart();
}

void UInmateWidget::CmsControllerPlay()
{
	mainWidget->SendCmsControllerPlay();
}

void UInmateWidget::CmsControllerStop()
{
	mainWidget->SendCmsControllerStop();
}

#pragma endregion

void UInmateWidget::RecvTrackingNum(int num)
{
	MovieControlWidget->RecvTrackingNum(num);
}

void UInmateWidget::RecvCmsNextRound()
{
	MovieControlWidget->RecvCmsNextRound();
}

void UInmateWidget::RecvHeartRate(FString rate)
{
	MovieControlWidget->RecvHeartRate(rate);
}

void UInmateWidget::Call_BackSpace_OnClick()
{
	switch (currSwitcherWidget)
	{
	case INMATE_LOGIN_DEFAULT:
	{
		mainWidget->ChangeWidgetIndex(ClinetLogin::SELECT_LOGIN);
		currSwitcherWidget = ProcessInmateLogin::INMATE_LOGIN_DEFAULT;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

		BackSpaceWidget->SetText(TEXT("재소자 페이지"));
	}
	break;
	case INMATE_INFO_CHECK:
	{
		InmateInfoCheckWidget->SetTextDataClear();
		currSwitcherWidget = ProcessInmateLogin::INMATE_LOGIN_DEFAULT;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

		BackSpaceWidget->SetText(TEXT("재소자 페이지"));
	}
	break;
	case DEVICE_CHECK:
	{
		currSwitcherWidget = ProcessInmateLogin::INMATE_INFO_CHECK;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
	}
	break;
	case MOVIE_CONTROLL:
	{
		currSwitcherWidget = ProcessInmateLogin::DEVICE_CHECK;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

		BackSpaceWidget->SetText(TEXT(""));
	}
	break;
	default:
		break;
	}
}

void UInmateWidget::Call_Login_OnClick()
{
	mainWidget->SendInmateLogin(inmateNumText);
}

void UInmateWidget::SuccessInmateLogin()
{
	inmateNumText = "";
	UseDataLoadWidget();
	currSwitcherWidget = ProcessInmateLogin::INMATE_INFO_CHECK;
	WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

	BackSpaceWidget->SetText(TEXT("제소자 정보 확인"));
}
