// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "ChangDeokMainWIdget.generated.h"

/**
 * 
 */

class UPopupButtonWidget;
class UWidgetSwitcher;
class UPopupWidget;
class UDescriptButtonWidget;
class UTextWidget;
class UFadeWidget;
class UDownLoadWidget;
class AChangDeokMainWidgetActor;

UCLASS()
class HANYANG2_CHANGDEOK_API UChangDeokMainWIdget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintNativeEvent)
	void CheckInit();
	UFUNCTION(BlueprintCallable)
	virtual void CheckInit_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetPopupInfo(UPopupButtonWidget* _Button);
	UFUNCTION(BlueprintCallable)
	virtual void SetPopupInfo_Implementation(UPopupButtonWidget* _Button);

	void SetWidgetActor(AChangDeokMainWidgetActor* _WidgetActor);
	void SetChangeText(FString text);

	UFadeWidget* GetFadeWidget() { return C_FadeWidget; }
protected:
	FString ChangeText;

	UFUNCTION(BlueprintCallable)
	void BeginInit();

	UFUNCTION(BlueprintCallable)
	void SetPopupButtons(UPopupButtonWidget* BackGround, UPopupButtonWidget* Chijo, UPopupButtonWidget* Oejo, UPopupButtonWidget* Yeonjo, UPopupButtonWidget* DaeBoDan);

	UFUNCTION(BlueprintCallable)
	void OnPressed_SkipButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_DescriptButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_TextHideButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_Binding_TextShowButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_ChangeLevel();

	UFUNCTION(BlueprintNativeEvent)
	void CustomOpenLevelFadeIn();
	UFUNCTION(BlueprintCallable)
	virtual void CustomOpenLevelFadeIn_Implementation(){}

	UFUNCTION(BlueprintCallable)
	void OpenLevelFadeIn();

	UFUNCTION(BlueprintCallable)
	void OnPressed_PlayChangeButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_TimeChangeButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_DownLoadButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_DownLoadCheckButton();

	UFUNCTION(BlueprintCallable)
	void OnPressed_CancelDownLoadButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* C_WidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPopupWidget* C_PopupWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDescriptButtonWidget* C_DescriptButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextWidget* C_TextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFadeWidget* C_FadeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDownLoadWidget* C_DownLoadWidget;

	UPROPERTY(BlueprintReadOnly)
	FString LauncherPath;

private:
	UFUNCTION()
	void CheckDownLoadState(float _Percent);

	UFUNCTION()
	void EndDownLoadState(bool IsDownLoadCancel);

	UFUNCTION()
	void UnZipEndState();

	AChangDeokMainWidgetActor* WidgetActor;

	bool IsDownLoadProcessing = false;
};
