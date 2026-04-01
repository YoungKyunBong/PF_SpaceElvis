// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "InmateSelectButtonWidget.generated.h"

class UInmateSelectMainWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UInmateSelectButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DataInit(UInmateSelectMainWidget* _inmateSelectMainWidget, FSelectButton buttonType);

protected:	
	UFUNCTION(BlueprintCallable)
	void Call_SelectButton_OnClick();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SetWrongImage();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SetWrongImage_Implementation() {}

protected:
	UPROPERTY(BlueprintReadOnly)
	FSelectButton selectButtonType;

	UPROPERTY(BlueprintReadOnly)
	FString Text;

private:
	UInmateSelectMainWidget* MainWidget;
};
