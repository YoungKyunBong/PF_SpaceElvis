// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/DeviceSettingGuideWidget.h"
#include "WidgetActor/InmateWidget.h"
#include "WidgetActor/BackSpaceWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UDeviceSettingGuideWidget::Init(UInmateWidget* _inmateWidget)
{
	InmateWidget = _inmateWidget;

	EditableTextBox->SetText(FText::FromString(TEXT("체험 진행을 위해 재소자의 HMD(VR)기기의\n착용 가이드를 진행하겠습니다.")));
}

void UDeviceSettingGuideWidget::Call_BackSpace_OnClick()
{
	switch (currSwitcherWidget)
	{
	case Guide_Start:
	{
		InmateWidget->ChangeWidgetIndex(ProcessInmateLogin::INMATE_INFO_CHECK);
		currSwitcherWidget = ProcessDeviceGuide::Guide_Start;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("체험 진행을 위해 재소자의 HMD(VR)기기의\n착용 가이드를 진행하겠습니다.")));

		InmateWidget->SetBackSpaceText_InmateWidget(TEXT("제소자 정보 확인"));
	}
		break;
	case Guide_Strap:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Start;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("체험 진행을 위해 재소자의 HMD(VR)기기의\n착용 가이드를 진행하겠습니다.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드"));
	}
		break;
	case Guide_View:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Strap;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("첫번쨰\nHMD(VR)기기의 스트랩 조절입니다.\n재소자의 머리크기에 맞춰 스트랩(상단부, 후면부)을 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 스트랩 조절"));
	}
		break;
	case Guide_Sound:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_View;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("두번째\nHMD(VR)기기의 시야각 조절입니다.\n기기의 하단부 좌측(재소자를 바라보는 기준이면 우측)의\n휠을 돌려서 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 시야각 조절"));
	}
		break;
	case Guide_Mirroring:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Sound;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("세번째\nHMD(VR)기기의 소리 조절입니다.\n기기의 하단부 우측(재소자를 바라보는 기준이면 좌측)의\n버튼(좌 - , 우 + )을 눌러 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 소리 조절"));
	}
		break;
	default:
		break;
	}
}

void UDeviceSettingGuideWidget::Call_Next_OnClick()
{
	switch (currSwitcherWidget)
	{
	case Guide_Start:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Strap;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("첫번쨰\nHMD(VR)기기의 스트랩 조절입니다.\n재소자의 머리크기에 맞춰 스트랩(상단부, 후면부)을 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 스트랩 조절"));
	}
	break;
	case Guide_Strap:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_View;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("두번째\nHMD(VR)기기의 시야각 조절입니다.\n기기의 하단부 좌측(재소자를 바라보는 기준이면 우측)의\n휠을 돌려서 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 시야각 조절"));
	}
	break;
	case Guide_View:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Sound;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("세번째\nHMD(VR)기기의 소리 조절입니다.\n기기의 하단부 우측(재소자를 바라보는 기준이면 좌측)의\n버튼(좌 - , 우 + )을 눌러 조절해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 소리 조절"));
	}
	break;
	case Guide_Sound:
	{
		currSwitcherWidget = ProcessDeviceGuide::Guide_Mirroring;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("마지막\nHMD(VR)기기의 미러링 확인입니다.\n재소자가 보고 있는 화면이 모니터상에 잘 보이는지 확인해 주세요.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드 : 미러링 확인"));
	}
	break;
	case Guide_Mirroring:
	{
		InmateWidget->UseDataLoadWidget();
		InmateWidget->ChangeWidgetIndex(ProcessInmateLogin::MOVIE_CONTROLL);
		currSwitcherWidget = ProcessDeviceGuide::Guide_Start;
		WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);
		EditableTextBox->SetText(FText::FromString(TEXT("체험 진행을 위해 재소자의 HMD(VR)기기의\n착용 가이드를 진행하겠습니다.")));

		BackSpaceWidget->SetText(TEXT("장비 설정 가이드"));

		InmateWidget->SetBackSpaceText_InmateWidget(TEXT("제소자 제어 페이지"));
	}
	break;
	default:
		break;
	}
}
