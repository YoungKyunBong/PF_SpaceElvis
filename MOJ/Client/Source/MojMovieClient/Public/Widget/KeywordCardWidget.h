// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "KeywordCardWidget.generated.h"

class UMainWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UKeywordCardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UMainWidget* _mainWidget);

public:
	void CallDataSetting(const TArray<FSelectButton>& buttonText) { DataSetting(buttonText); }

protected:
	UFUNCTION(BlueprintCallable)
	void CallSelectButton(FSelectButton text);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void DataSetting(const TArray<FSelectButton>& buttonText);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void DataSetting_Implementation(const TArray<FSelectButton>& buttonText) {}

private:
	UMainWidget* MainWidget;
};
