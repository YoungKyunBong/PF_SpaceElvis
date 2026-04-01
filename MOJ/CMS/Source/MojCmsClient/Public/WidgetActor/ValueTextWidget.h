// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ValueTextWidget.generated.h"

class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UValueTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetWidgetData();
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetData_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void SetTextData();
	UFUNCTION(BlueprintCallable)
	virtual void SetTextData_Implementation() {}

public:
	void CreateObject(FString _text, FVector2D _canvasSize, FSlateFontInfo _textFontInfo);

	void SetText(FString data);

protected:
	UPROPERTY(BlueprintReadOnly)
	FString text;

	UPROPERTY(BlueprintReadOnly)
	FVector2D canvasSize;

	UPROPERTY(BlueprintReadOnly)
	FSlateFontInfo textFontInfo;
};
