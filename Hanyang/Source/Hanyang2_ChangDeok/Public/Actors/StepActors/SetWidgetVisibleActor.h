// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "SetWidgetVisibleActor.generated.h"

/**
 * 
 */



UCLASS()
class HANYANG2_CHANGDEOK_API ASetWidgetVisibleActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ADefaultManager* WidgetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReverse;
};
