// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "ProcessSubStepManager.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API AProcessSubStepManager : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AStepManager* SubStepManager;

	UFUNCTION(BlueprintCallable)
	void SubStepInit();

	UFUNCTION(BlueprintCallable)
	void SubStepSkip();
};
