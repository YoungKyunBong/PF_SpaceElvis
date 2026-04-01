// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "CamMoveBlendActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API ACamMoveBlendActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetCam;

protected:
	UFUNCTION(BlueprintCallable)
	void CustomViewBlend();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReverse;
};
