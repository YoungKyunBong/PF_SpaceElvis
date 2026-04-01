// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fonts/SlateFontInfo.h"
#include "Blueprint/UserWidget.h"
#include "SwitchButtonWidget.generated.h"


class UCanvasPanelSlot;
class UTextBlock;
class UTexture2D;
class UButton;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API USwitchButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString text;

	UPROPERTY(EditAnywhere)
	FVector2D canvasSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateFontInfo textFontInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SwitchButton_NormalImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SwitchButton_HoverImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SwitchButton_PressImage;

	UFUNCTION(BlueprintCallable)
	void SetText(UTextBlock* _textBlock);

	UFUNCTION(BlueprintCallable)
	void SetCanvasSize(UCanvasPanelSlot* _canvasSlot);

	UFUNCTION(BlueprintCallable)
	void SetTextFont(UTextBlock* _textBlock);

	UFUNCTION(BlueprintCallable)
	void SetButtonImage(UButton* SwitchButton);
};
