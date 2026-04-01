// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InmateWidget.generated.h"

enum ProcessInmateLogin : int
{
	INMATE_LOGIN_DEFAULT = 0,
	INMATE_INFO_CHECK = 1,
	DEVICE_CHECK = 2,
	MOVIE_CONTROLL = 3,
	SAVE = 4,
};

class UMainWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UInmateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitcher;

public:
	UFUNCTION(BlueprintNativeEvent)
	void PrintLoginSuccess();
	UFUNCTION(BlueprintCallable)
	virtual void PrintLoginSuccess_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void PrintLoginFail();
	UFUNCTION(BlueprintCallable)
	virtual void PrintLoginFail_Implementation() {}

	UFUNCTION(BlueprintCallable)
	void Init(UMainWidget* _mainWidget);

	void PrintLoginCheck(bool isSuccess);

	void CallInmateCheckInfo();

	void ChangeWidgetIndex(ProcessInmateLogin _type);

	void UseDataLoadWidget();

	void SetBackSpaceText_InmateWidget(FString _text);

public:
#pragma region SENDINFO
	void CmsControllerStart();
	void CmsControllerPlay();
	void CmsControllerStop();
#pragma endregion
	void RecvTrackingNum(int num);
	void RecvCmsNextRound();
	void RecvHeartRate(FString rate);

protected:
	UPROPERTY(BlueprintReadWrite)
	FString inmateNumText;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* StatusText;

	UPROPERTY(BlueprintReadWrite)
	class UInmateInfoCheckWidget* InmateInfoCheckWidget;

	UPROPERTY(BlueprintReadWrite)
	class UDataLoadTextWidget* DataLoadTextWidget;

	UPROPERTY(BlueprintReadWrite)
	class UDeviceSettingGuideWidget* DeviceSettingGuideWidget;

	UPROPERTY(BlueprintReadWrite)
	class UMovieControlWidget* MovieControlWidget;

	UPROPERTY(BlueprintReadWrite)
	class UBackSpaceWidget* BackSpaceWidget;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_BackSpace_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_Login_OnClick();

	UFUNCTION(BlueprintCallable)
	void SuccessInmateLogin();

private:
	UMainWidget* mainWidget;

	ProcessInmateLogin currSwitcherWidget = ProcessInmateLogin::INMATE_LOGIN_DEFAULT;
};
