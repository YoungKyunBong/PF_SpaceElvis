// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "TextActor.generated.h"

/**
 * 
 */

UCLASS()
class HANYANG2_CHANGDEOK_API ATextActor : public AStepActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

protected:
	UFUNCTION(BlueprintCallable)
	void SetTextToWidget();
};
