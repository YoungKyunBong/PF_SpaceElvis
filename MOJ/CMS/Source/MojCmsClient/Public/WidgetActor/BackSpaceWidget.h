// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BackSpaceWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UBackSpaceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString text;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* TextBlock;

public:
	UFUNCTION(BlueprintCallable)
	void SetText(FString _text);
};
