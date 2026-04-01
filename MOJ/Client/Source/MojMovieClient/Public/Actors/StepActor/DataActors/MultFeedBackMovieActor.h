// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "MultFeedBackMovieActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMultFeedBackMovieActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void CmsSectionMovement() override;

protected:
	UPROPERTY(EditAnywhere);
	TArray<MovieSceneType> sceneTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;
protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie() { PlayMovie(); }

	UFUNCTION(BlueprintCallable)
	void ChangeScene();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation() {}

private:
	int processIndex = 0;

	FTimerHandle Handle;
	FTimerHandle NextStep_Handle;

	void SetTimer_MovieDelay();
	void SetTimer_NextStepDelay();
};
