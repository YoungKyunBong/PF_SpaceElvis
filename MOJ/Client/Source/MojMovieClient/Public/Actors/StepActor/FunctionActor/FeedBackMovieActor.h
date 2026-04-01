// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "FeedBackMovieActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AFeedBackMovieActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void ChangeScene();

protected:
	UPROPERTY(EditAnywhere);
	TArray<MovieSceneType> sceneTypes;
};
