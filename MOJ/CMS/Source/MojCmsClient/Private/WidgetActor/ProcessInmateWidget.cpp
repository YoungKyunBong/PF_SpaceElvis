// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/ProcessInmateWidget.h"
#include "WidgetActor/ManagerWidget.h"
#include "WidgetActor/SearchWidget.h"
#include "WidgetActor/ColumnNameTextWidget.h"
#include "WidgetActor/BackSpaceWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"

void UProcessInmateWidget::Init(UManagerWidget* _managerWidget)
{
	managerWidget = _managerWidget;

	InmateSearch_Vector2DSizes.Add(FVector2D(75, 75));
	InmateSearch_Vector2DSizes.Add(FVector2D(250, 75));
	InmateSearch_Vector2DSizes.Add(FVector2D(225, 75));
	InmateSearch_Vector2DSizes.Add(FVector2D(350, 75));
	InmateSearch_Vector2DSizes.Add(FVector2D(425, 75));
	InmateSearch_Vector2DSizes.Add(FVector2D(425, 75));

	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
	InmateSearch_SlateFontInfos.Add(SlateFontInfo);
}

#pragma region RECVINFO

void UProcessInmateWidget::RecvInmateADD(SEND_TEXT_TYPE printType)
{
	switch (printType)
	{
	case SEND_TEXT_TYPE::TYPE_TRUE:
	{
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("신규 재소자 등록을 완료했습니다.")));
		TextBlock_InmateADD->SetColorAndOpacity(FLinearColor::White);
	}
	break;
	case SEND_TEXT_TYPE::TYPE_FALSE:
	{
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("신규 재소자 등록을 실패했습니다.\n정보를 다시 입력해 주세요.")));
		TextBlock_InmateADD->SetColorAndOpacity(FLinearColor::Red);
	}
	break;
	case SEND_TEXT_TYPE::TYPE_SAME:
	{
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("중복되는 재소자 고유번호가 존재합니다.\n다시 입력해 주세요.")));
		TextBlock_InmateADD->SetColorAndOpacity(FLinearColor::Red);
	}
	break;
	default:
		break;
	}
}

void UProcessInmateWidget::RecvInmateUpdate(SEND_TEXT_TYPE type, FString data)
{
	switch (type)
	{
	case SEND_TEXT_TYPE::TYPE_TRUE:
	{
		UpdateInmateWidget->RecvUpdateData(updateInmateIndex, updateInmateText);
		SearchWidgets[UpdateInmateWidget][updateInmateIndex] = updateInmateText;
		TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::White);
	}
		break;
	case SEND_TEXT_TYPE::TYPE_FALSE:
		TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::Red);
		break;
	default:
		break;
	}
	TextBlock_InmateSearch->SetText(FText::FromString(data));
}

void UProcessInmateWidget::RecvInmateSearch(FString datas)
{
	if (C_ScrollBox_ValueText->GetChildrenCount() == 0 && C_ScrollBox_ColumnText->GetChildrenCount() == 0)
	{
		TextBlock_InmateSearch->SetText(FText::FromString(TEXT("조회가 완료 되었습니다!")));
		TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::White);
	}

	C_ScrollBox_ValueText->SetAlwaysShowScrollbar(true);
	
	TArray<FString> Columns;
	datas.ParseIntoArray(Columns, TEXT("$"));

	TArray<TArray<FString>> Values;
	for (int i = 0; i < Columns.Num(); i++)
	{
		TArray<FString> temp;
		Columns[i].ParseIntoArray(temp, TEXT("#"));
		Values.Add(temp);
	}

	for (int i = 0; i < Values.Num(); i++)
	{
		if (i == 0)
		{
			auto* tempWidget = CreateWidget<UColumnNameTextWidget>(GetOwningPlayer(), TUColumnNameTextWidget);
			tempWidget->Init(this);
			tempWidget->RecvSearchData(Values[i], InmateSearch_Vector2DSizes, InmateSearch_SlateFontInfos);
			C_ScrollBox_ColumnText->AddChild(tempWidget);
		}
		else
		{
			auto* tempWidget = CreateWidget<USearchWidget>(GetOwningPlayer(), TUSearchWidget);
			tempWidget->Init(this);
			tempWidget->RecvSearchData(Values[i], InmateSearch_Vector2DSizes, InmateSearch_SlateFontInfos);
			C_ScrollBox_ValueText->AddChild(tempWidget);
			SearchWidgets.Add(tempWidget, Values[i]);
		}
	}
}

void UProcessInmateWidget::GetInmateUpdateData(USearchWidget* dataWidget)
{
	UpdateInmateWidget = dataWidget;
	UpdateInmateData = SearchWidgets[dataWidget];
	UpdateInamteName = UpdateInmateData[UpdateInmateIndex::INMATE_NAME];
	UpdateInmateCode = UpdateInmateData[UpdateInmateIndex::INMATE_CODE];
}

#pragma endregion

void UProcessInmateWidget::Call_BackSpace_OnClick()
{
	switch (currSwitcherWidget)
	{
	case INMATE_DEFAULT:
	{
		managerWidget->ChangeWidgetIndex(ProcessManager::MANAGER_DEFAULT);
		managerWidget->SetBackSpaceText_ManagerWidget(TEXT("관리자 페이지"));
	}
	break;
	case INMATE_ADD:
	{
		InmateNum = InmateName = "";
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("")));
	}
	break;
	case INMATE_SEARCH:
	{
		UpdateInmateData.Empty();
		UpdateInmateWidget = NULL;
		updateInmateIndex = -1;
		updateInmateText.Empty();

		SearchWidgets.Empty();
		UpdateInamteName = UpdateInmateCode = "";
		C_ScrollBox_ColumnText->ClearChildren();
		C_ScrollBox_ValueText->ClearChildren();
		C_ScrollBox_ValueText->SetAlwaysShowScrollbar(false);
		TextBlock_InmateSearch->SetText(FText::FromString(TEXT("")));
	}
	default:
		break;
	}

	currSwitcherWidget = ProcessInmate::INMATE_DEFAULT;
	WidgetSwitcher->SetActiveWidgetIndex(currSwitcherWidget);

	BackSpaceWidget->SetText(TEXT("재소자 관리 페이지"));
}

void UProcessInmateWidget::Call_InmateAdd_OnClick()
{
	currSwitcherWidget = ProcessInmate::INMATE_ADD;
	WidgetSwitcher->SetActiveWidgetIndex(ProcessInmate::INMATE_ADD);

	BackSpaceWidget->SetText(TEXT("신규 재소자 등록"));
}

void UProcessInmateWidget::Call_InmateSearch_OnClick()
{
	currSwitcherWidget = ProcessInmate::INMATE_SEARCH;
	WidgetSwitcher->SetActiveWidgetIndex(ProcessInmate::INMATE_SEARCH);

	BackSpaceWidget->SetText(TEXT("재소자 조회/수정"));
}

#pragma region SENDINFO

void UProcessInmateWidget::Call_SendInmateAdd_OnClick()
{
	TextBlock_InmateADD->SetColorAndOpacity(FLinearColor::Red);
	if (InmateNum == "")
	{
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("재소자 번호를 입력해 주세요")));
	}
	else if (InmateName == "")
	{
		TextBlock_InmateADD->SetText(FText::FromString(TEXT("재소자 이름을 입력해 주세요")));
	}
	else
	{
		managerWidget->InmateADD(InmateNum, InmateName);
	}
}

void UProcessInmateWidget::Call_SendInmateSearch_OnClick()
{
	TextBlock_InmateSearch->SetText(FText::FromString(TEXT("조회 중 입니다.\n잠시만 기다려 주세요.")));
	TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::White);

	UpdateInamteName = UpdateInmateCode = "";
	C_ScrollBox_ColumnText->ClearChildren();
	C_ScrollBox_ValueText->ClearChildren();
	C_ScrollBox_ValueText->SetAlwaysShowScrollbar(false);

	managerWidget->InmateSearch();
}

void UProcessInmateWidget::Call_SendInmateUpdate_OnClick()
{
	if (UpdateInmateCode == "")
	{
		TextBlock_InmateSearch->SetText(FText::FromString(TEXT("입력값에 빈 공간이 존재합니다.\n수정 정보를 입력해 주세요.")));
		TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::Red);
		return;
	}
	
	if (UpdateInmateData[UpdateInmateIndex::INMATE_CODE] != UpdateInmateCode)
	{
		TextBlock_InmateSearch->SetText(FText::FromString(TEXT("정보를 수정 중 입니다.\n잠시만 기다려 주세요.")));
		TextBlock_InmateSearch->SetColorAndOpacity(FLinearColor::White);
		updateInmateIndex = UpdateInmateIndex::INMATE_CODE;
		updateInmateText = UpdateInmateCode;
		UpdateInmateData[UpdateInmateIndex::INMATE_CODE] = UpdateInmateCode;
		managerWidget->InmateUpdate(INMATE_UPDATE_TYPE::INMATE_STATUS_CODE, UpdateInmateData[UpdateInmateIndex::INMATE_NUM], UpdateInmateCode);
	}
}

#pragma endregion
