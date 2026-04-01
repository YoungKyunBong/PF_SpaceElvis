// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Protocols.h"
#include "Components/TextBlock.h"
#include "ProcessInmateWidget.generated.h"

enum ProcessInmate : int
{
	INMATE_DEFAULT = 0,
	INMATE_ADD = 1,
	INMATE_SEARCH = 2,
};

enum UpdateInmateIndex : int
{
	INMATE_NUM = 1,
	INMATE_NAME = 2,
	INMATE_CODE = 3,
};

class UManagerWidget;
class USearchWidget;
class UColumnNameTextWidget;
class UScrollBox;
class UBackSpaceWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UProcessInmateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

public:
	UFUNCTION(BlueprintCallable)
	void Init(UManagerWidget* _managerWidget);

public:
#pragma region RECVINFO

	void RecvInmateADD(SEND_TEXT_TYPE printType);

	void RecvInmateUpdate(SEND_TEXT_TYPE type, FString data);

	void RecvInmateSearch(FString datas);

#pragma endregion

public:
	void GetInmateUpdateData(USearchWidget* dataWidget);

protected:
#pragma region INMATE_ADD

	UPROPERTY(BlueprintReadWrite)
	FString InmateNum;

	UPROPERTY(BlueprintReadWrite)
	FString InmateName;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlock_InmateADD;

#pragma endregion

#pragma region INMATE_Search

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlock_InmateSearch;

	UPROPERTY(BlueprintReadWrite)
	UScrollBox* C_ScrollBox_ColumnText;

	UPROPERTY(BlueprintReadWrite)
	UScrollBox* C_ScrollBox_ValueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USearchWidget> TUSearchWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UColumnNameTextWidget> TUColumnNameTextWidget;

	UPROPERTY(BlueprintReadWrite)
	UBackSpaceWidget* BackSpaceWidget;

	UPROPERTY(BlueprintReadWrite)
	FString UpdateInamteName;

	UPROPERTY(BlueprintReadWrite)
	FString UpdateInmateCode;

#pragma endregion

protected:
	TArray<FVector2D> InmateSearch_Vector2DSizes;
	TArray<FSlateFontInfo> InmateSearch_SlateFontInfos;

	UPROPERTY(EditAnywhere)
	FSlateFontInfo SlateFontInfo;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_BackSpace_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_InmateAdd_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_InmateSearch_OnClick();

#pragma region SENDINFO

	UFUNCTION(BlueprintCallable)
	void Call_SendInmateAdd_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_SendInmateSearch_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_SendInmateUpdate_OnClick();

#pragma endregion

private:
	UManagerWidget* managerWidget;

	ProcessInmate currSwitcherWidget = ProcessInmate::INMATE_DEFAULT;

	TMap<USearchWidget*, TArray<FString>> SearchWidgets;
	TArray<FString> UpdateInmateData;
	USearchWidget* UpdateInmateWidget;
	int updateInmateIndex;
	FString updateInmateText;
};
