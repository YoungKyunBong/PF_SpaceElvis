// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Protocols.h"
#include "MainWidget.generated.h"

enum ClinetLogin : int
{
	MAIN_DEFAULT = 0,
	SELECT_LOGIN = 1,
	MANAGER_LOGIN = 2,
	INMATE_LOGIN = 3,
};

class UGameManager;
class USwitchButtonWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
#pragma region RECVINFO

#pragma region LOGIN
	UFUNCTION()
	void RecvCheckPW(bool isSuccess);

	UFUNCTION()
	void RecvChangePW(bool isSuccess);

	UFUNCTION()
	void RecvInmateLogin(bool isSuccess);
#pragma endregion

#pragma region INMATE
	UFUNCTION()
	void RecvInmateADD(SEND_TEXT_TYPE printType);

	UFUNCTION()
	void RecvInmateUpdate(SEND_TEXT_TYPE type, FString data);

	UFUNCTION()
	void RecvInmateSearch(FString data);
#pragma endregion
	UFUNCTION()
	void RecvTrackingNum(int num);

	UFUNCTION()
	void RecvTempNextRound();

	UFUNCTION()
	void RecvHeartRate(FString rate);
#pragma endregion

public:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

public:
	UFUNCTION(BlueprintCallable)
	UGameManager* GetGameManager() { return GameIns; }

#pragma region SENDINFO

#pragma region LOGIN
	void SendStartLogin(FString pinNum);
	void SendChangePW(FString currPW, FString newPW);
	void SendInmateLogin(FString inmateNum);
#pragma endregion

#pragma region INMATE
	void SendInmateADD(FString InmateNum, FString InmateName);
	void SendInmateSearch();
	void SendInmateUpdate(INMATE_UPDATE_TYPE _type, FString prisonerNum, FString data);
#pragma endregion

#pragma region CMS
	void SendCmsControllerStart();
	void SendCmsControllerPlay();
	void SendCmsControllerStop();
#pragma endregion

#pragma endregion

	UFUNCTION(BlueprintCallable)
	void Call_ManagerLogin_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_InmateLogin_OnClick();

	void ChangeWidgetIndex(ClinetLogin _type);

protected:	
	UFUNCTION(BlueprintCallable)
	void SetGameManager(UGameManager* _GameIns) { GameIns = _GameIns; }

	UPROPERTY(BlueprintReadWrite)
	class UStartLoginWidget* startLoginWidget;

	UPROPERTY(BlueprintReadWrite)
	class UManagerWidget* managerWidget;

	UPROPERTY(BlueprintReadWrite)
	class UInmateWidget* inmateWidget;

protected:
	UFUNCTION(BlueprintCallable)
	void Init();

private:
	UGameManager* GameIns;
};
