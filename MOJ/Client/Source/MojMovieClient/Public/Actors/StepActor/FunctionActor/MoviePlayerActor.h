// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "MoviePlayerActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMoviePlayerActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void Init(AStepManager* Manager) override;

public:
	UFUNCTION(BlueprintCallable)
	void PlayMovie();

	UFUNCTION(BlueprintCallable)
	void PauseMovie();
};
