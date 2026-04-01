// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InmateProgramLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UInmateProgramLogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetLogData(FString _currTimeText, FString _logText);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetWidgetData();
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetData_Implementation() {}

protected:
	UPROPERTY(BlueprintReadOnly)
	FString CurrTimeText;

	UPROPERTY(BlueprintReadOnly)
	FString LogText;
};
