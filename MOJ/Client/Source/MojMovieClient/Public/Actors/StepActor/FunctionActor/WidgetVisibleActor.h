// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "WidgetVisibleActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AWidgetVisibleActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	ESlateVisibility Option;

protected:
	UFUNCTION(BlueprintCallable)
	void SetWidgetVisible();
};
