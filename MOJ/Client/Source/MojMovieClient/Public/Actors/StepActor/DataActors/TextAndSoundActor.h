// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Actors/StepActor/StepActor.h"
#include "TextAndSoundActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ATextAndSoundActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

protected:
	UFUNCTION(BlueprintCallable)
	void PlayNarr();

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();
};
