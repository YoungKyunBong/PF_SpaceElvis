// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

//enum FontPercentSize : int
//{
//	Size_Two = 2,
//	Size_Three = 3,
//	Size_Four = 4,
//	Size_Five = 5,
//	Size_Six = 6,
//	Size_Seven = 7,
//	Size_Eight = 8,
//	Size_Nine = 9,
//	Size_Eleven = 11,
//};

class AWidgetManager;
class UInmateSelectButtonWidget;
class UInmateSelectMainWidget;
class UInmateIconSelectButtonWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

public:
	UFUNCTION(BlueprintCallable)
	void Init(AWidgetManager* _WidgetManager);

public:
	void SetWidgetSwitchIndex(int index);
	void SetNarrText(FString _HeaderText, FString _text, bool _IsVisibleNarrNextButton);
	void InmateSelectButton(FString _HeaderText, const TArray<FSelectButton>& buttonText, bool _IsVisibleNextButton);
	void InmateKeywordCardButton(const TArray<FSelectButton>& buttonText);
	void SetWidgetVisible(ESlateVisibility option);
	void SetIconType(CheckIconType _checkIconType);

	void CallSelectButton(FSelectButton text);
	void CallIconButton();
	void CallNextButton();

protected:
	UPROPERTY(BlueprintReadOnly)
	FString Text;

	UPROPERTY(BlueprintReadOnly)
	FString HeaderText;

	UPROPERTY(BlueprintReadWrite)
	class UCanvasPanelSlot* MainCanvasSlot;

	UPROPERTY(BlueprintReadWrite)
	class UCanvasPanel* NarrNextButtonCanvas;

	UPROPERTY(BlueprintReadWrite)
	class UKeywordCardWidget* KeywordCardWidget;

	UPROPERTY(BlueprintReadWrite)
	class UInmateSelectMainWidget* InmateSelectMainWidget;

	UPROPERTY(BlueprintReadWrite)
	class UInmateSelectEmotionMainWidget* InmateSelectEmotionMainWidget;

	UPROPERTY(BlueprintReadWrite)
	UInmateIconSelectButtonWidget* InmateIconSelectButtonWidget;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_InmateReadyButton_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_SelectYes_OnClick();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetFillHeaderText(bool isHeader);
	UFUNCTION(BlueprintCallable)
	virtual void SetFillHeaderText_Implementation(bool isHeader) {}

private:
	AWidgetManager* WidgetManager;
};
