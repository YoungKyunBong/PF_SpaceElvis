// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "InmateSelectMainWidget.generated.h"

class UHorizontalBox;
class UMainWidget;
class UInmateSelectButtonWidget;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API UInmateSelectMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UMainWidget* _mainWidget);

public:
	void InmateSelectButton(FString _HeaderText, const TArray<FSelectButton>& buttonText, bool _IsVisibleNextButton);

	void CallSelectButton(FSelectButton text);

protected:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly)
	FString HeaderText;

	UPROPERTY(BlueprintReadWrite)
	TArray<UHorizontalBox*> HorizonBoxs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UInmateSelectButtonWidget> TUInmateSelectButtonWidget;

	UPROPERTY(BlueprintReadWrite)
	class UCanvasPanel* NextButtonCanvas;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_NextButton_OnClick();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetChildFill(bool isHeader, int num);
	UFUNCTION(BlueprintCallable)
	virtual void SetChildFill_Implementation(bool isHeader, int num) {}

	UFUNCTION(BlueprintNativeEvent)
	void SetNextButtonVisible(bool IsVisible);
	UFUNCTION(BlueprintCallable)
	virtual void SetNextButtonVisible_Implementation(bool IsVisible) {}

private:
	bool isVisibleNextButton;

	UMainWidget* MainWidget;
};
