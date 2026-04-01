// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "SubDescriptHitActor.generated.h"

/**
 * 
 */
UCLASS()
class HANYANG2_CHANGDEOK_API ASubDescriptHitActor : public ADefaultManager
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void BeginOverlapPawn();

	UFUNCTION(BlueprintCallable)
	void EndOverlapPawn();

	UFUNCTION(BlueprintCallable)
	void IsDefaultBox() { IsOverDefaultBox = true; }

	UFUNCTION(BlueprintCallable)
	void IsCheckBox() { IsOverCheckBox = true; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MyStepManagerNumber;

private:
	bool IsOverDefaultBox;
	bool IsOverCheckBox;
};
