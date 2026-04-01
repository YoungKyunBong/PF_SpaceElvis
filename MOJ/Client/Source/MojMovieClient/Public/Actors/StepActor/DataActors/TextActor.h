// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Actors/StepActor/StepActor.h"
#include "TextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ATextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int switchIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

protected:
	UFUNCTION(BlueprintCallable)
	void SetTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();
};
