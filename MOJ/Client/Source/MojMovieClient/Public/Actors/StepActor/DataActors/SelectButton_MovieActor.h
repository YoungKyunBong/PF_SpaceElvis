// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "SelectButton_MovieActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ASelectButton_MovieActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* BlurActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie(bool isCorrect) { PlayMovie(isCorrect); }

	UFUNCTION(BlueprintCallable)
	void Call_WidgetInterControl(bool isVisible) { SetWidgetInterControl(isVisible); }

	UFUNCTION(BlueprintCallable)
	void ChangeScene(MovieSceneType movieType);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetWrongMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie(bool isCorrect);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation(bool isCorrect) {}

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
	FTimerHandle WrongMovieDelay_Handle;
	FTimerHandle NextStep_Handle;
	//void SetTimer_PlayNarr();
	//void SetTimer_WrongNarr();

	void SetTimer_MovieDelay();
	void SetTimer_WrongMovieDelay();
	void SetTimer_NextStepDelay();
	void SetTimer_WrongStepDelay();
};
