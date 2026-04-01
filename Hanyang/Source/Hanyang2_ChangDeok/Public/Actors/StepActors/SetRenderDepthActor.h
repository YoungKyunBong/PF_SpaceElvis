// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "SetRenderDepthActor.generated.h"

/**
 * 
 */

class UStaticMeshComponent;

UCLASS()
class HANYANG2_CHANGDEOK_API ASetRenderDepthActor : public AStepActor
{
	GENERATED_BODY()
public:
	UMaterialInstanceDynamic* GetChangeMeshDynIns() { return changeMesh->CreateDynamicMaterialInstance(0); }

	UMaterialInstanceDynamic* GetChangeMeshDynIns_M2() { return changeMesh->CreateDynamicMaterialInstance(1); }

protected:
	UFUNCTION(BlueprintCallable)
	void SetRenderDepth();

	UFUNCTION(BlueprintCallable)
	void CheckSkip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* changeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float deleyTime = 5.0f;

private:
	FTimerHandle Handle;

	void SetTimer_DepthRenderOff();
};
