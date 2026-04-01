// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/MainWidget.h"
#include "Manager/GameManager.h"
#include "WidgetActor/StartLoginWidget.h"
#include "WidgetActor/ManagerWidget.h"
#include "WidgetActor/InmateWidget.h"
#include "WidgetActor/SwitchButtonWidget.h"
#include "Components/WidgetSwitcher.h"

void UMainWidget::Init()
{
//	GameIns->RecvLoginChangePW.AddUFunction(this, FName("RecvChangePW"));
//	GameIns->RecvLoginCheckPW.AddUFunction(this, FName("RecvCheckPW"));
	GameIns->RecvInmateLogin.AddUFunction(this, FName("RecvInmateLogin"));

	GameIns->RecvInmateADD.AddUFunction(this, FName("RecvInmateADD"));
	GameIns->RecvInmateUpdate.AddUFunction(this, FName("RecvInmateUpdate"));
	GameIns->RecvInmateSearch.AddUFunction(this, FName("RecvInmateSearch"));

	GameIns->RecvTrackingNum.AddUFunction(this, FName("RecvTrackingNum"));
	GameIns->RecvCmsControllerNextRound.AddUFunction(this, FName("RecvTempNextRound"));

	GameIns->RecvHeartRate.AddUFunction(this, FName("RecvHeartRate"));
}

#pragma region RECVINFO

#pragma region LOGIN
void UMainWidget::RecvCheckPW(bool isSuccess) { startLoginWidget->PrintLoginCheck(isSuccess); }
void UMainWidget::RecvChangePW(bool isSuccess) { managerWidget->ProcessChangePW(isSuccess); }
void UMainWidget::RecvInmateLogin(bool isSuccess) { inmateWidget->PrintLoginCheck(isSuccess); }
#pragma endregion

#pragma region INMATE
void UMainWidget::RecvInmateADD(SEND_TEXT_TYPE printType) { managerWidget->RecvInmateADD(printType); }
void UMainWidget::RecvInmateUpdate(SEND_TEXT_TYPE type, FString data) { managerWidget->RecvInmateUpdate(type, data); }
void UMainWidget::RecvInmateSearch(FString data) { managerWidget->RecvInmateSearch(data); }
#pragma endregion

void UMainWidget::RecvTrackingNum(int num) { inmateWidget->RecvTrackingNum(num); }

void UMainWidget::RecvTempNextRound() { inmateWidget->RecvCmsNextRound(); }

void UMainWidget::RecvHeartRate(FString rate) { inmateWidget->RecvHeartRate(rate); }

#pragma endregion

#pragma region SENDINFO

#pragma region LOGIN
void UMainWidget::SendStartLogin(FString pinNum) { GameIns->Send_LoginCheckPW(pinNum); }
void UMainWidget::SendChangePW(FString currPW, FString newPW) { GameIns->Send_ChangePW(currPW, newPW); }
void UMainWidget::SendInmateLogin(FString inmateNum) { GameIns->Send_InmateLogin(inmateNum); }
#pragma endregion

#pragma region INMATE
void UMainWidget::SendInmateADD(FString InmateNum, FString InmateName) { GameIns->Send_InmateADD(InmateNum); }
void UMainWidget::SendInmateSearch() { GameIns->Send_InmateSearch(); }
void UMainWidget::SendInmateUpdate(INMATE_UPDATE_TYPE _type, FString prisonerNum, FString data) { GameIns->Send_InmateUpdate(data); }
#pragma endregion

#pragma region CMS
void UMainWidget::SendCmsControllerStart() { GameIns->Send_CmsControllerStart(); }
void UMainWidget::SendCmsControllerPlay() { GameIns->Send_CmsControllerPlay(); }
void UMainWidget::SendCmsControllerStop() { GameIns->Send_CmsControllerStop(); }
#pragma endregion

void UMainWidget::Call_ManagerLogin_OnClick()
{
	WidgetSwitcher->SetActiveWidgetIndex(ClinetLogin::MANAGER_LOGIN);
}

void UMainWidget::Call_InmateLogin_OnClick()
{
	WidgetSwitcher->SetActiveWidgetIndex(ClinetLogin::INMATE_LOGIN);
}

void UMainWidget::ChangeWidgetIndex(ClinetLogin _type)
{
	WidgetSwitcher->SetActiveWidgetIndex(_type);
}