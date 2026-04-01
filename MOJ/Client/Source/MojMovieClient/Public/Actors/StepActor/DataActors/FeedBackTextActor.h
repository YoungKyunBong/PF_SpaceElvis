// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "FeedBackTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AFeedBackTextActor : public AStepActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVisibleNextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsVisibleNarrNextButton = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void PlayNarr(FString SoundID);

	UFUNCTION(BlueprintCallable)
	void WrongNarr(FString SoundID);

	UFUNCTION(BlueprintCallable)
	void SetTextToWidget(FString TextID);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

private:
	FTimerHandle Handle;
	void SetTimer_PlayNarr();
	void SetTimer_WrongNarr();
};
