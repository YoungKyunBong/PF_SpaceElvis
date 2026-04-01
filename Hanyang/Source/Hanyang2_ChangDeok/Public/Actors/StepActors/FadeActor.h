// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "FadeActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API AFadeActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFadeIn;

	UFUNCTION(BlueprintCallable)
	void CallCustomFade();
};
