// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SearchWidget.generated.h"

class UProcessInmateWidget;
class UValueTextWidget;
/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API USearchWidget : public UUserWidget
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

	void RecvUpdateData(int index, FString data);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UValueTextWidget> TUValueTextWidget;

	UPROPERTY(BlueprintReadWrite)
	class UHorizontalBox* HorizontalBox;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_InmateData_OnClick();

private:
	UProcessInmateWidget* InmateWidget;

	TArray<UValueTextWidget*> valueWidgets;
};
