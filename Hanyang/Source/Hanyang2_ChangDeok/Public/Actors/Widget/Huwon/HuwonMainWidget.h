// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HuwonMainWidget.generated.h"

/**
 * 
 */

class UWidgetSwitcher;
class UTextWidget;
class AHuwonWidgetActor;
class USubLevelDescriptButtonWidget;
class UFadeWidget;
class UHuwonSubDescriptWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API UHuwonMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void C_Init();

	void SetWidgetVisibility(ESlateVisibility _SlateVisibility);
	void SetWidgetActor(AHuwonWidgetActor* _WidgetActor) { WidgetActor = _WidgetActor; }
	void SetChangeText(FString text);
	void SetSkipButtonText(FString text);

	void OnPressed_MovePlaceButton(int StepManagerNum);

	UFadeWidget* GetFadeWidget() { return C_FadeWidget; }

	void SetSubTextToWidget(FString subText, double margin_Top, float _fontSize);
	void SetSubWidgetHidden();

protected:
	UFUNCTION(BlueprintCallable)
	void OnPressed_SkipButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_DescriptButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_TextHideButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_TextShowButton();

	UFUNCTION(BlueprintCallable)
	void OpenLevelFadeIn();

	UFUNCTION(BlueprintCallable)
	void OnPressed_PlayChangeButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_TimeChangeButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* C_WidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextWidget* C_TextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USubLevelDescriptButtonWidget* C_SubDescriptButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFadeWidget* C_FadeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHuwonSubDescriptWidget* C_HuwonSubDescriptWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* C_SubDescriptAnim;

private:
	AHuwonWidgetActor* WidgetActor;
	int CurrentStepManagerNum = -1;
};
