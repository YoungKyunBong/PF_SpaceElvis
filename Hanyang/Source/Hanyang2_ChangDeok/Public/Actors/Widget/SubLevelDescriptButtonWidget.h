// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubLevelDescriptButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API USubLevelDescriptButtonWidget : public UUserWidget
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

	UFUNCTION(BlueprintCallable)
	void SetDescriptButtonText(FString Name) { DescriptButtonText = Name; }

	int GetStepManagerNumber() { return MyStepManagerNumber; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DescriptButtonText;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MyStepManagerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetSwitcher* C_WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly)
	FString LauncherPath = "C:/UnrealProject/ChangDeok/Windows/Hanyang2_ChangDeok.exe";
};
