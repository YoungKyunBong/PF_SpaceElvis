// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Manager/GameManager.h"
#include "LogRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API ULogRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetData(const FLogItem& Data);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Type;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TimeActor;
};

