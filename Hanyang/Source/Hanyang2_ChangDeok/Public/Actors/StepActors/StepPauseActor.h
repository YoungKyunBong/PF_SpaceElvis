// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "StepPauseActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API AStepPauseActor : public AStepActor
{
	GENERATED_BODY()
protected:
	void Init(AStepManager* Manager);

	UFUNCTION(BlueprintCallable)
	void PlacePawnDefaultSetting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* PlacePawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite)
	FString SkipText;

	UPROPERTY(BlueprintReadWrite)
	FString BackText;

	virtual void MyStep_Implementation(AStepManager* Manager) override;

	virtual void ResetSkip_Implementation() override;

private:
	int ReverseStepNumber;
};
