// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/InmatePlayRoundWidget.h"
#include "WidgetActor/MovieControlWidget.h"

void UInmatePlayRoundWidget::Init(UMovieControlWidget* _movieControlWidget)
{
	MovieControlWidget = _movieControlWidget;
}

void UInmatePlayRoundWidget::SetPlayerRoundData(FString _sessionNum, FString _playRoundNum, FString _statusCode)
{
	SessionNum = _sessionNum;
	PlayRoundNum = _playRoundNum;
	StatusCode = _statusCode;

	SetWidgetData();
}

void UInmatePlayRoundWidget::ChangeStatusCode(FString text)
{
	StatusCode = text;
	MovieControlWidget->TempChangeCode(this);
}

void UInmatePlayRoundWidget::Call_ProgramStart_OnClick()
{
	MovieControlWidget->CallProgramStartOnClick();
	

}
