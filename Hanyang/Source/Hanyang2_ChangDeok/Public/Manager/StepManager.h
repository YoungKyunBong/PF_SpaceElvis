// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "StepManager.generated.h"

//class UGameManager;
class ASqeStep;

UCLASS()
class HANYANG2_CHANGDEOK_API AStepManager : public ADefaultManager
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	FString StepName;

	UFUNCTION(BlueprintCallable)
	void SetNameCheck(AActor* checkActor, FString appendName);

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ASqeStep*> sqeSteps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepManagerNumber;

	//UPROPERTY()
	//	UGameManager* GameIns;

	//UFUNCTION(BlueprintCallable)
	//void SetGameIns(UGameManager* _GameIns) { GameIns = _GameIns; }

	void StepStart();

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void NextStep();

	UFUNCTION(BlueprintCallable)
	void SkipStep();

	UFUNCTION(BlueprintCallable)
	void RewindStep();

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void Reset_Skip();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void Reset_Skip_Implementation();

	UFUNCTION(BlueprintCallable)
	void CallResetSkip();

	UFUNCTION(BlueprintCallable)
	void SetIsGameEnd(bool IsCheck);

	UFUNCTION(BlueprintCallable)
	bool CheckStepCount();
private:
	bool IsGameEnd = false;
};
