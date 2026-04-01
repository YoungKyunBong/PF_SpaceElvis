// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "AnswerTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AAnswerTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PositiveSoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NegativeSoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void PlayNarr(FString SoundID);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

private:
	FTimerHandle Handle;
	void SetTimer_PlayNarr();
};
