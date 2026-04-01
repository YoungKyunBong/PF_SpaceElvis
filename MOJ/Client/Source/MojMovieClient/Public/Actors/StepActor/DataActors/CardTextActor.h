// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "CardTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ACardTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

	UPROPERTY(BlueprintReadOnly)
	FString FeedBackText;

	UPROPERTY(BlueprintReadOnly)
	FString FeedBackTextSub;

public:
	virtual void ReplayStep_Implementation(FSelectButton selectButton) override;

	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie() { PlayMovie(); }

	UFUNCTION(BlueprintCallable)
	void Call_WidgetInterControl(bool isVisible) { SetWidgetInterControl(isVisible); }

	UFUNCTION(BlueprintCallable)
	void ChangeScene(MovieSceneType movieType);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

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
	int processIndex = 0;

	FTimerHandle MovieDelay_Handle;
	FTimerHandle NextStep_Handle;

	void SetTimer_MovieDelay();
	void SetTimer_NextStepDelay();
	void SetTimer_AnotherStepDelay();
};
