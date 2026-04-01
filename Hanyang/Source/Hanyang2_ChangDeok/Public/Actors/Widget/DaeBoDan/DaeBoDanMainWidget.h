// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DaeBoDanMainWidget.generated.h"

/**
 * 
 */

class UWidgetSwitcher;
class UTextWidget;
class ADaeBoDanWidgetActor;
class USubLevelDescriptButtonWidget;
class UFadeWidget;
class UDaeBoDanSubDescriptWidget;
class UWidgetAnimation;

UCLASS()
class HANYANG2_CHANGDEOK_API UDaeBoDanMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void C_Init();

	void SetWidgetVisibility(ESlateVisibility _SlateVisibility);
	void SetWidgetActor(ADaeBoDanWidgetActor* _WidgetActor) { WidgetActor = _WidgetActor; }
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
	UDaeBoDanSubDescriptWidget* C_DaeBoDanSubDescriptWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* C_SubDescriptAnim;
private:
	ADaeBoDanWidgetActor* WidgetActor;
	int CurrentStepManagerNum = -1;
};
