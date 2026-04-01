// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "SoundActor.generated.h"

/**
 * 
 */

UCLASS()
class HANYANG2_CHANGDEOK_API ASoundActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 2.0f;

	UFUNCTION(BlueprintCallable)
	void PlayNarr();

	UFUNCTION(BlueprintCallable)
	float CheckSkip();

	//virtual void MyStep_Implementation(AStepManager* Manager) override;

private:
	FTimerHandle Handle;

	void SetTimer_PlayNarr();
};
