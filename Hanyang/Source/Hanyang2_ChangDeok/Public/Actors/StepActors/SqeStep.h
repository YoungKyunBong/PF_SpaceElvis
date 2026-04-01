// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SqeStep.generated.h"

class AStepManager;
class AStepActor;

UCLASS()
class HANYANG2_CHANGDEOK_API ASqeStep : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASqeStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AStepActor* StepActor;

	UFUNCTION(BlueprintCallable)
	void Init(AStepManager* Manager);

	void CheckStep(AStepManager* Manager);

	void SkipStep();

	void RewindStep();

	UFUNCTION(BlueprintCallable)
	void ResetSkip();
};
