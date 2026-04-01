// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YeonJoMainWidget.generated.h"

/**
 * 
 */

class UWidgetSwitcher;
class UTextWidget;
class AYeonJoWidgetActor;
class USubLevelDescriptButtonWidget;
class UFadeWidget;
class UYeonJoSubDescriptWidget;
class UWidgetAnimation;

UCLASS()
class HANYANG2_CHANGDEOK_API UYeonJoMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void C_Init();

	void SetWidgetVisibility(ESlateVisibility _SlateVisibility);
	void SetWidgetActor(AYeonJoWidgetActor* _WidgetActor) { WidgetActor = _WidgetActor; }
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
	UYeonJoSubDescriptWidget* C_YeonJoSubDescriptWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* C_SubDescriptAnim;
private:
	AYeonJoWidgetActor* WidgetActor;
	int CurrentStepManagerNum = -1;
};
