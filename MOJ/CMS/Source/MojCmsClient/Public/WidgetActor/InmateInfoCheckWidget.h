// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "InmateInfoCheckWidget.generated.h"

class UInmateWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UInmateInfoCheckWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UInmateWidget* _inmateWidget);

public:
	void SetTextDataClear();

	void SetInmateCheckInfo();

protected:
	UFUNCTION(BlueprintCallable)
	void Call_Next_OnClick();

protected:
	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateName;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateNum;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateIdentyNum;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateRegistDay;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_CrimeType;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_SituationNum;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_SessionNum;

private:
	UInmateWidget* InmateWidget;
};
