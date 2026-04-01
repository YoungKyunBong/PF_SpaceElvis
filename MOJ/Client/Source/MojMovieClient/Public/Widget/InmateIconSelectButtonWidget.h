// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "InmateIconSelectButtonWidget.generated.h"

class UMainWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UInmateIconSelectButtonWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	FString HeaderText;

public:
	UFUNCTION(BlueprintCallable)
	void Init(UMainWidget* _mainWidget);

	UFUNCTION(BlueprintCallable)
	void Call_SetIconButton(CheckIconType _type);

	UFUNCTION(BlueprintCallable)
	void Call_IconButton_OnClick(CheckIconType _type);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void PlayAnimStop();
	UFUNCTION(BlueprintCallable)
	virtual void PlayAnimStop_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void PlayAnimThink();
	UFUNCTION(BlueprintCallable)
	virtual void PlayAnimThink_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void PlayAnimOptions();
	UFUNCTION(BlueprintCallable)
	virtual void PlayAnimOptions_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void PlayAnimPick();
	UFUNCTION(BlueprintCallable)
	virtual void PlayAnimPick_Implementation() {}

private:
	UMainWidget* MainWidget;
};
