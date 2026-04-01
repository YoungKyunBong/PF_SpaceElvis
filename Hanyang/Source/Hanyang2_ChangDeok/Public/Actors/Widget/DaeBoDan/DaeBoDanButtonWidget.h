// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DaeBoDanButtonWidget.generated.h"

/**
 * 
 */

class UDaeBoDanMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API UDaeBoDanButtonWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonText;

	UFUNCTION(BlueprintCallable)
	void MovePlace();

public:
	UFUNCTION(BlueprintCallable)
	void Init(FString _ButtonText, int _MyStepManagerNumber, UDaeBoDanMainWidget* _MainWidget) { ButtonText = _ButtonText; MyStepManagerNumber = _MyStepManagerNumber; MainWidget = _MainWidget; }

	//int GetStepManagerNumber() { return MyStepManagerNumber; }

private:
	UDaeBoDanMainWidget* MainWidget;
	int MyStepManagerNumber;
};
