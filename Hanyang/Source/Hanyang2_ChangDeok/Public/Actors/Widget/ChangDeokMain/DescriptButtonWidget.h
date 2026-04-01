// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptButtonWidget.generated.h"

/**
 * 
 */

class UWidgetSwitcher;

UCLASS()
class HANYANG2_CHANGDEOK_API UDescriptButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void OnClickDescriptButton();

	UFUNCTION(BlueprintCallable)
	void OnClickTextHideButton();

	UFUNCTION(BlueprintCallable)
	void OnClickTextShowButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MyStepManagerNumber;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* C_WidgetSwitcher;
};
