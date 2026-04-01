// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataLoadTextWidget.generated.h"

class UInmateWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UDataLoadTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnText();
	UFUNCTION(BlueprintCallable)
	virtual void OnText_Implementation() {}

	UFUNCTION(BlueprintCallable)
	void Init(UInmateWidget* _inmateWidget);

protected:
	UFUNCTION(BlueprintCallable)
	void Call_SetInmateInfoData();

private:
	UInmateWidget* InmateWidget;
};
