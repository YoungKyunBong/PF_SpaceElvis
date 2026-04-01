// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextWidget.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API UTextWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void Init(FString PlayButtonText);

	UFUNCTION(BlueprintCallable)
	void OnPressed_PlayButton(FString PlayButtonText);

	UFUNCTION(BlueprintCallable)
	void OnPressed_StopButton(FString PlayButtonText);

	UFUNCTION(BlueprintCallable)
	void OnPressed_TimeChangeButton(int Index, float _TimeOfDay, float _TimeEmissive);

	UPROPERTY(BlueprintReadWrite)
	FString ChangeText;

	UPROPERTY(BlueprintReadWrite)
	FString SkipButtonText;

	UPROPERTY(BlueprintReadOnly)
	FString PlayChangeButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetSwitcher* C_WidgetSwitcher;

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetDefault();
	UFUNCTION(BlueprintCallable)
	virtual void SetDefault_Implementation();

	void SetChangeText(FString text) { ChangeText = text; }

	void SetSkipButtonText(FString _Text) { SkipButtonText = _Text; }

	void SetIsEnabled(bool isEnabled);

	bool IsPaused = true;

	float C_TimeOfDay;

	float C_TimeEmissive;
};
