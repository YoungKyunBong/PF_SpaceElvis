// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DownLoadWidget.generated.h"

/**
 * 
 */

class UCanvasPanel;
class UImage;

UCLASS()
class HANYANG2_CHANGDEOK_API UDownLoadWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FString PercentText;

	UPROPERTY(BlueprintReadOnly)
	float Percent;

	UPROPERTY(BlueprintReadWrite)
	FString DefaultText;

	UPROPERTY(BlueprintReadWrite)
	bool IsFirstPlay = true;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DownLoadHandle;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle UnZipHandle;

	UPROPERTY(BlueprintReadWrite)
	UCanvasPanel* C_DownLoadCheckCanvasPanel;

	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> prograssbars;

	UFUNCTION(BlueprintCallable)
	void C_Init();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeTextDownLoading();
	UFUNCTION(BlueprintCallable)
	virtual void ChangeTextDownLoading_Implementation(){}

	UFUNCTION(BlueprintNativeEvent)
	void ChangeTextUnZip();
	UFUNCTION(BlueprintCallable)
	virtual void ChangeTextUnZip_Implementation() {}

public:
	void SetDefault();

	void SetPercent(float _percent);

	UFUNCTION(BlueprintNativeEvent)
	void DownLoadEnd(bool IsDownLoadCancel);
	UFUNCTION(BlueprintCallable)
	virtual void DownLoadEnd_Implementation(bool IsDownLoadCancel);

	UFUNCTION(BlueprintNativeEvent)
	void UnZipEnd();
	UFUNCTION(BlueprintCallable)
	virtual void UnZipEnd_Implementation();


	void SetCanvasPanelVisible(ESlateVisibility _visible);

	void SetText_CompleteDownLoad();
	void SetText_CancelDownLoad();

	UPROPERTY(BlueprintReadOnly)
	FString DownLoadLevelName;

private:
	FString downLoadStateText;

	//bool IsVisibleCheckButton;
};
