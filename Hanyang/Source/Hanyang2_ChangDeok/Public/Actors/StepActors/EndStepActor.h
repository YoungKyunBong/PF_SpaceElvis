// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "EndStepActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API AEndStepActor : public AStepActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetStepManagerDefault();

	UFUNCTION(BlueprintCallable)
	void SetInputModeDefault();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReverse;
};
