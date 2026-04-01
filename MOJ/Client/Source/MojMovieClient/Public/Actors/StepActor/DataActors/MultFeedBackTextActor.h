// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "MultFeedBackTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMultFeedBackTextActor : public AStepActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int NextStepMaxCount = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

protected:
	UFUNCTION(BlueprintCallable)
	void SetTextToWidget(FString TextID);

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

private:
	int count = 0;
};
