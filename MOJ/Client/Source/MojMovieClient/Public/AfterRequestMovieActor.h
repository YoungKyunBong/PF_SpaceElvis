// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "AfterRequestMovieActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AAfterRequestMovieActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie() { PlayMovie(); }

	UFUNCTION(BlueprintCallable)
	void SetTextToWidget(FString TextID);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

	UFUNCTION(BlueprintCallable)
	void ChangeScene();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SelectMovieDelay();

	UFUNCTION(BlueprintCallable)
	void NoneSelectMovieDelay();
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SetWidgetInterControl(bool isVisible);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SetWidgetInterControl_Implementation(bool isVisible) {}

	UFUNCTION(BlueprintNativeEvent)
	void TempClose();
	UFUNCTION(BlueprintCallable)
	virtual void TempClose_Implementation() {}

private:
	bool isStart = true;

	FSelectButton SelectButtonID;
	FSelectButton NoneSelectButtonID;

	FTimerHandle MovieDelay_Handle;
	FTimerHandle NextStep_Handle;

	void SetTimer_SelectMovieDelay();
	void SetTimer_NoneSelectMovieDelay();
	void SetTimer_SelectStepDelay();
	void SetTimer_NextStepDelay();
};
