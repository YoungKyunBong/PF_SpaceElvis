// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "SubTextActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API ASubTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double margin_Top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fontSize;
protected:
	UFUNCTION(BlueprintCallable)
	void SetSubTextToWidget();

	UFUNCTION(BlueprintCallable)
	void CheckSkip();
};
 