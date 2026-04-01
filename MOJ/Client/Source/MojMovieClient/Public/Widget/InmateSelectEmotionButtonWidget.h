// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "InmateSelectEmotionButtonWidget.generated.h"

class UInmateSelectEmotionMainWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UInmateSelectEmotionButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DataInit(UInmateSelectEmotionMainWidget* _inmateSelectEmotionMainWidget, FSelectButton buttonType);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSlateBrush> Emotion_2D;

private:
	UInmateSelectEmotionMainWidget* MainWidget;
};
