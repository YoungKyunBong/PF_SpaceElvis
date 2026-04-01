// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "MovieDelayActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMovieDelayActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void TempClose();
	UFUNCTION(BlueprintCallable)
	virtual void TempClose_Implementation() {}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReturn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsNextStep = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PauseTime = 0.0f;

public:
	virtual void ReturnStep_Implementation() override;

	virtual void CmsSectionMovement() override;

private:
	FTimerHandle MovieDelay_Handle;
	FTimerHandle NextSetting_Handle;
	FTimerHandle NextStep_Handle;

	void SetTimer_NextSetting();
	void SetTimer_MovieDelay();
	void SetTimer_NextStepDelay();

	bool isReturn = false;
};
