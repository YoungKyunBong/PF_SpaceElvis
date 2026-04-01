// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Actors/StepActor/StepActor.h"
#include "StartIconType.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AStartIconType : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	CheckIconType checkIconType;

protected:
	UFUNCTION(BlueprintCallable)
	void SetIconType();
};
