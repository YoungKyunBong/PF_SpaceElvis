// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "WidgetSwitchActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AWidgetSwitchActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	int index;

protected:
	UFUNCTION(BlueprintCallable)
	void SetWidgetSwitchIndex();
};
