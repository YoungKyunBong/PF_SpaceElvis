// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StepActor.generated.h"

class AStepManager;

UCLASS()
class HANYANG2_CHANGDEOK_API AStepActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStepActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	AStepManager* stepManager;

	UFUNCTION(BlueprintCallable)
	virtual void Init(AStepManager* Manager) { stepManager = Manager; }

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void MyStep(AStepManager* Manager);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void MyStep_Implementation(AStepManager* Manager) {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SkipStep();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SkipStep_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void RewindStep();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void RewindStep_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void ResetSkip();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void ResetSkip_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SkipWidget")
	void ClickCheck();
	UFUNCTION(BlueprintCallable, Category = "SkipWidget")
	virtual void ClickCheck_Implementation() {}
};
