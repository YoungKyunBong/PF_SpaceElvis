// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChiJoButtonWidget.generated.h"

/**
 * 
 */

class UChiJoMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API UChiJoButtonWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonText;

	UFUNCTION(BlueprintCallable)
	void MovePlace();

public:
	UFUNCTION(BlueprintCallable)
	void Init(FString _ButtonText, int _MyStepManagerNumber, UChiJoMainWidget* _MainWidget) { ButtonText = _ButtonText; MyStepManagerNumber = _MyStepManagerNumber; MainWidget = _MainWidget; }

	//int GetStepManagerNumber() { return MyStepManagerNumber; }

private:
	UChiJoMainWidget* MainWidget;
	int MyStepManagerNumber;
};
