// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "DeviceSettingGuideWidget.generated.h"

enum ProcessDeviceGuide : int
{
	Guide_Start = 1,
	Guide_Strap = 2,
	Guide_View = 3,
	Guide_Sound = 4,
	Guide_Mirroring = 5,
};

class UInmateWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UDeviceSettingGuideWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UInmateWidget* _inmateWidget);

protected:
	UFUNCTION(BlueprintCallable)
	void Call_BackSpace_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_Next_OnClick();

protected:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox;

	UPROPERTY(BlueprintReadWrite)
	class UBackSpaceWidget* BackSpaceWidget;

private:
	UInmateWidget* InmateWidget;

	ProcessDeviceGuide currSwitcherWidget = ProcessDeviceGuide::Guide_Start;
};
