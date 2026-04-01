// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupButtonWidget.generated.h"

/**
 * 
 */

class UChangDeokMainWIdget;

USTRUCT(BlueprintType)
struct FPopupInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name_Horizon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* PlaceSampleImage;
};

USTRUCT(BlueprintType)
struct FDownLoadData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString Path;

	UPROPERTY(EditAnywhere)
	FString FileName;
};

UCLASS()
class HANYANG2_CHANGDEOK_API UPopupButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FPopupInfo _PopupInfo;

	UPROPERTY(EditAnywhere)
	FDownLoadData _DownLoadData;

	UFUNCTION(BlueprintCallable)
	void SetMainWidget(UChangDeokMainWIdget* _MainWidget) { MainWidget = _MainWidget; }

protected:
	UFUNCTION(BlueprintCallable)
	void OnPressed_Button();

	UChangDeokMainWIdget* MainWidget;
};
