// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupWidget.generated.h"

/**
 * 
 */
class UWidgetSwitcher;

UCLASS()
class HANYANG2_CHANGDEOK_API UPopupWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	FPopupInfo PopupInfo;

	UPROPERTY(BlueprintReadOnly)
	FString DownLoadText;

	UPROPERTY(BlueprintReadOnly)
	bool IsDownLoadButtonCanvasPanel = true;

	UPROPERTY(BlueprintReadOnly)
	bool IsMovePlaceButtonCanvasPanel = true;

	UPROPERTY(BlueprintReadWrite)
	FString DownLoadNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* C_MainSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetSwitcher* C_ButtonSwitcher;

	//UFUNCTION(BlueprintCallable)
	//void OnPressed_OpenLevel();

public:
	//UFUNCTION(BlueprintCallable)
	//void Init();

	void SetInfo(FPopupInfo _PopupInfo, FDownLoadData _DownLoadData, FString& _LauncherPath);

	UFUNCTION(BlueprintCallable)
	void SetMainSwitcherIndex(int index);

	FDownLoadData DownLoadData;

	void SetPanelEnable(bool IsEnable) { IsDownLoadButtonCanvasPanel = IsEnable; }

	void SetMovePlaceButtonPanelEnable(bool IsEnable) { IsMovePlaceButtonCanvasPanel = IsEnable; }

private:
	//TMap<FName, FName> LevelNames;
};
