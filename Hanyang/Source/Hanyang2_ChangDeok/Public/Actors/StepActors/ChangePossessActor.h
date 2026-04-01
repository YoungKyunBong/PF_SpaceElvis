// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
#include "ChangePossessActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API AChangePossessActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* PossessPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* MoveStartPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPossessDefaultPawnStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReverse;


protected:
	UFUNCTION(BlueprintCallable)
	void CustomPossess();

	UFUNCTION(BlueprintCallable)
	void SetMainWidgetDefault();

	void SetStartPos();

	UFUNCTION(BlueprintCallable)
	void CallCustomFadeIn();

	UFUNCTION(BlueprintCallable)
	void CallCustomFadeOut();
};
