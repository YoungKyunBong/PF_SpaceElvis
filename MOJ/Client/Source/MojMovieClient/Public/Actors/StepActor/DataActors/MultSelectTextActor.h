// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "MultSelectTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMultSelectTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void CmsSectionMovement() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayTextTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

	UPROPERTY(EditAnywhere);
	TArray<MovieSceneType> sceneTypes;

protected:
	UFUNCTION(BlueprintCallable)
	void SetTextToWidget(FString TextID);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

protected:
	UFUNCTION(BlueprintCallable)
	void ChangeScene();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetNarrationPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void PlaySelectText();

	UFUNCTION(BlueprintCallable)
	void PlayNoneSelectText();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation() {}

private:
	int processIndex = 0;

	TArray<FSelectButton> MultSelectText;
	TArray<FSelectButton> MultNoneSelectText;

	FTimerHandle Handle;

	bool isStart = true;
	bool isOnce = false;
private:

	void CheckNextStep_Select();
	void CheckNextStep_NoneSelect();
};
