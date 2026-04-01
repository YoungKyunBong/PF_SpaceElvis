// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "SoundActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ASoundActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UFUNCTION(BlueprintCallable)
	void PlayNarr();

	UFUNCTION(BlueprintCallable)
	float CheckSkip();

	UFUNCTION(BlueprintCallable)
	void SetNarrationPaused(bool IsPlay);

	//virtual void MyStep_Implementation(AStepManager* Manager) override;

public:
	virtual void CmsSectionMovement() override;

protected:
	UPROPERTY(EditAnywhere)
	bool isDelay = true;

private:
	FTimerHandle Handle;

	void SetTimer_PlayNarr();
};
