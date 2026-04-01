// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "../InsideDataStruct.h"
#include "GameFramework/Actor.h"
#include "StepActor.generated.h"

UCLASS()
class MOJMOVIECLIENT_API AStepActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	AStepManager* stepManager;

	UFUNCTION(BlueprintCallable)
	virtual void Init(AStepManager* Manager) { stepManager = Manager; }

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void MyStep(AStepManager* Manager);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void MyStep_Implementation(AStepManager* Manager) {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void ReplayStep(FSelectButton selectButton);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void ReplayStep_Implementation(FSelectButton selectButton) {}
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

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void ReturnStep();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void ReturnStep_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void MyStepPause(bool IsPause);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void MyStepPause_Implementation(bool IsPause) {}

	virtual void CMS_Start() {}
	virtual void CMS_Stop() {}

	virtual void CmsSectionMovement() {}
};
