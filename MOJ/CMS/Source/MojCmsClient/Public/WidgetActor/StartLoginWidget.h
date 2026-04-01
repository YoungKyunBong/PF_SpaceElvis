// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StartLoginWidget.generated.h"

class UMainWidget;
/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UStartLoginWidget : public UUserWidget
{
	GENERATED_BODY()
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

	UFUNCTION()
	void PrintLoginCheck(bool isSuccess);

protected:
	UPROPERTY(BlueprintReadWrite)
	FString pinText;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* StatusText;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_Login_OnClick();

	UFUNCTION(BlueprintCallable)
	void ChangeWidgetIndex();

private:
	UMainWidget* mainWidget;
};
