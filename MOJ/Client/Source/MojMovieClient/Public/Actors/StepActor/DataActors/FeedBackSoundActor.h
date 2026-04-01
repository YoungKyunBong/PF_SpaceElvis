// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "FeedBackSoundActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AFeedBackSoundActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void CmsSectionMovement() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float deleyTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

protected:
	UFUNCTION(BlueprintCallable)
	void PlayNarr();

	UFUNCTION(BlueprintCallable)
	void SetTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetNarrationPaused(bool IsPlay);

protected:
	UPROPERTY(EditAnywhere);
	TArray<FString> headerTextIDs;

	UPROPERTY(EditAnywhere);
	TArray<FString> textIDs;

	UPROPERTY(EditAnywhere);
	TArray<FString> soundIDs;

private:
	FTimerHandle Handle;

	void SetTimer_PlayNarr();
};
