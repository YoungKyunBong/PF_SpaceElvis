// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "NextRoundActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ANextRoundActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void CallTempNextRound();
};
