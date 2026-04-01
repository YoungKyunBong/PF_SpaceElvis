// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void CustomFadeIn();
	UFUNCTION(BlueprintCallable)
	virtual void CustomFadeIn_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void CustomFadeOut();
	UFUNCTION(BlueprintCallable)
	virtual void CustomFadeOut_Implementation() {}
};
