// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/MovieControlWidget.h"
#include "WidgetActor/InmateWidget.h"
#include "WidgetActor/InmatePlayRoundWidget.h"
#include "WidgetActor/InmateProgramLogWidget.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"

void UMovieControlWidget::Init(UInmateWidget* _inmateWidget)
{
	InmateWidget = _inmateWidget;
}

void UMovieControlWidget::SetInmateDataInfo()
{
	EditableTextBox_InmateName->SetText(FText::FromString(TEXT("홍길동")));
	EditableTextBox_InmateNum->SetText(FText::FromString(TEXT("1111")));
	EditableTextBox_CrimeType->SetText(FText::FromString(TEXT("성폭력")));
	EditableTextBox_SituationNum->SetText(FText::FromString(TEXT("5번")));

	bool isOnce = true;
	for (int i = 0; i < TempPlayerRoundDatas.Num(); i++)
	{
		auto* tempWidget = CreateWidget<UInmatePlayRoundWidget>(GetOwningPlayer(), TUInmatePlayRoundWidget);
		tempWidget->Init(this);
		tempWidget->SetPlayerRoundData(TempPlayerRoundDatas[i].SessionNum, TempPlayerRoundDatas[i].PlayRoundNum, TempPlayerRoundDatas[i].StatusCode);
		VerticalBox->AddChild(tempWidget);
		InmatePlayRoundWidgets.Add(tempWidget);

		if (isOnce)
		{
			if (TempPlayerRoundDatas[i].StatusCode == TEXT("진행대기"))
			{
				isOnce = false;
				tempWidget->SetActiveButton();
			}
		}
	}

	//RecvCmsNextRound();
}

void UMovieControlWidget::RecvCmsNextRound()
{
	for (int i = 0; i < InmatePlayRoundWidgets.Num(); i++)
	{
		if (InmatePlayRoundWidgets[i]->StatusCode == TEXT("진행대기"))
		{
			InmatePlayRoundWidgets[i - 1]->StatusCode = TEXT("진행완료");
			InmatePlayRoundWidgets[i - 1]->SetDeActiveButton();
			InmatePlayRoundWidgets[i - 1]->SetPlayerRoundData(InmatePlayRoundWidgets[i - 1]->SessionNum, InmatePlayRoundWidgets[i - 1]->PlayRoundNum, InmatePlayRoundWidgets[i - 1]->StatusCode);

			InmatePlayRoundWidgets[i]->SetActiveButton();
			//tempWidget->SetActiveButton();
			break;
		}
	}
}

void UMovieControlWidget::RecvHeartRate(FString rate)
{
	EditableTextBox_InmateHeartRate->SetText(FText::FromString(rate));
}

void UMovieControlWidget::CallProgramStartOnClick_Implementation()
{
	FDateTime CurrentTime = FDateTime::Now();
	FString TimestampString = CurrentTime.ToString();

	auto* tempWidget = CreateWidget<UInmateProgramLogWidget>(GetOwningPlayer(), TUInmateProgramLogWidget);
	//tempWidget->Init(this);
	tempWidget->SetLogData(TimestampString, "Start");
	C_ScrollBox_LogText->AddChild(tempWidget);

	InmateWidget->CmsControllerStart();
}

void UMovieControlWidget::TempChangeCode(UInmatePlayRoundWidget* _widget)
{
	int index = 0;
	if (InmatePlayRoundWidgets.Find(_widget, index))
	{
		InmatePlayRoundWidgets[index]->StatusCode = _widget->StatusCode;
	}
}

void UMovieControlWidget::Call_Play_OnClick()
{
	FDateTime CurrentTime = FDateTime::Now();
	FString TimestampString = CurrentTime.ToString();

	auto* tempWidget = CreateWidget<UInmateProgramLogWidget>(GetOwningPlayer(), TUInmateProgramLogWidget);
	//tempWidget->Init(this);
	tempWidget->SetLogData(TimestampString, "Play");
	C_ScrollBox_LogText->AddChild(tempWidget);

	InmateWidget->CmsControllerPlay();
}

void UMovieControlWidget::Call_Pause_OnClick()
{
	FDateTime CurrentTime = FDateTime::Now();
	FString TimestampString = CurrentTime.ToString();

	auto* tempWidget = CreateWidget<UInmateProgramLogWidget>(GetOwningPlayer(), TUInmateProgramLogWidget);
	//tempWidget->Init(this);
	tempWidget->SetLogData(TimestampString, "Pause");
	C_ScrollBox_LogText->AddChild(tempWidget);

	InmateWidget->CmsControllerStop();
}
