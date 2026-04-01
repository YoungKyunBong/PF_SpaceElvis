// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "AfterRequestTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AAfterRequestTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSelectButton AskTextID;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie() { PlayMovie(); }

	UFUNCTION(BlueprintCallable)
	void SetTextToWidget();

	UFUNCTION(BlueprintCallable)
	void ChangeScene();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SetWidgetInterControl(bool isVisible);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SetWidgetInterControl_Implementation(bool isVisible) {}

	UFUNCTION(BlueprintNativeEvent)
	void TempClose();
	UFUNCTION(BlueprintCallable)
	virtual void TempClose_Implementation() {}

private:
	FTimerHandle MovieDelay_Handle;
	FTimerHandle NextStep_Handle;

	void SetTimer_MovieDelay();
	void SetTimer_NextStepDelay();
};
