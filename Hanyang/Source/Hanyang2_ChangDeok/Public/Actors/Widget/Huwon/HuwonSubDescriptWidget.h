// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HuwonSubDescriptWidget.generated.h"

/**
 * 
 */

class UWidgetAnimation;
class USizeBoxSlot;
class UTextBlock;

UCLASS()
class HANYANG2_CHANGDEOK_API UHuwonSubDescriptWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	void NativeTick(const FGeometry& MyGeometry, float deltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	FString text;

	UPROPERTY(BlueprintReadWrite)
	USizeBoxSlot* C_SizeBoxSlot;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* C_TextBlock;

	UPROPERTY(BlueprintReadWrite)
	FSlateFontInfo C_FontInfo;

	UPROPERTY(BlueprintReadOnly)
	float AnimCurrTime;

	UPROPERTY(BlueprintReadWrite)
	float AnimEndTime;

public:
	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* C_OpenAnim;

	float AnimCurrTime_Reverse;

	void SetTextToWidget(FString _text, double margin_Top, float _fontSize);

	void ReverseWidgetAnim();

	void ResetWidgetAnim();
private:
	void SetTextFont(float _fontSize);
};
