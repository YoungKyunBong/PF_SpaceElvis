// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ColumnNameTextWidget.generated.h"

class UValueTextWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UColumnNameTextWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetWidgetData(UUserWidget* widget);
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetData_Implementation(UUserWidget* widget) {}

public:
	UFUNCTION(BlueprintCallable)
	void Init(UProcessInmateWidget* _InmateWidget);

	void RecvSearchData(const TArray<FString> datas, const TArray<FVector2D> Vector2DSizes, const TArray<FSlateFontInfo> SlateFontInfos);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UValueTextWidget> TUValueTextWidget;

	UPROPERTY(BlueprintReadWrite)
	class UHorizontalBox* HorizontalBox;

private:
	UProcessInmateWidget* InmateWidget;
};
