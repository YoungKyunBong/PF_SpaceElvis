// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Protocols.h"
#include "Components/TextBlock.h"
#include "ManagerWidget.generated.h"

enum ProcessManager : int
{
	MANAGER_DEFAULT = 0,
	CHANGE_PW = 1,
	PROCESS_INMATE = 2,
	PROCESS_CODE = 3,
	PROCESS_LOG = 4,
	PROCESS_PROGRAM = 5,
	PROCESS_TREATMENT = 6,
};

class UMainWidget;
class UBackSpaceWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

public:
	UFUNCTION(BlueprintCallable)
	void Init(UMainWidget* _mainWidget);

public:
	void ProcessChangePW(bool isSuccess);

	void ChangeWidgetIndex(ProcessManager _type);

	void SetBackSpaceText_ManagerWidget(FString _text);

#pragma region RECVINFO

	UFUNCTION()
	void RecvInmateADD(SEND_TEXT_TYPE printType);

	UFUNCTION()
	void RecvInmateUpdate(SEND_TEXT_TYPE type, FString data);

	UFUNCTION()
	void RecvInmateSearch(FString data);

#pragma endregion

#pragma region SENDINFO

	void InmateADD(FString InmateNum, FString InmateName);

	void InmateSearch();

	void InmateUpdate(INMATE_UPDATE_TYPE _type, FString prisonerNum, FString data);

#pragma endregion

protected:
	UPROPERTY(BlueprintReadWrite)
	FString CurrPwText;

	UPROPERTY(BlueprintReadWrite)
	FString NewPwText;

	UPROPERTY(BlueprintReadWrite)
	FString NewPwCheckText;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlock_Main;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlock_ChangePW;

	UPROPERTY(BlueprintReadWrite)
	UBackSpaceWidget* BackSpaceWidget;

	UPROPERTY(BlueprintReadWrite)
	class UProcessInmateWidget* ProcessInmateWidget;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_BackSpace_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_ChangePW_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_SetChangePW_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_Inmate_OnClick();

private:
	UMainWidget* mainWidget;

	ProcessManager currSwitcherWidget = ProcessManager::MANAGER_DEFAULT;
};
