// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "StepManager.generated.h"

UCLASS()
class MOJMOVIECLIENT_API AStepManager : public ADefaultManager
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	FString StepName;

	UFUNCTION(BlueprintCallable)
	void SetNameCheck(AActor* checkActor, FString appendName);

	bool IsGameStop = false;

public:
	int BeforeSelectIndex = 0;

	TArray<int> MultSelectMovieIndex;
	TArray<int> MultNoneSelectMovieIndex;

	TArray<int> InterMovieIndex;

	TArray<FString> TotalFeedBackText;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> SectionMovementStepCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepManagerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AStepActor*> stepActors;

	void StepStart();

	virtual void Init() override;
	virtual void NextStep() override;
	virtual void SkipStep() override;
	virtual void RewindStep() override;
	virtual void ReplayStep(FSelectButton selectButton) override;

	UFUNCTION(BlueprintCallable)
	void ReturnStep();

	virtual void Reset_Skip_Implementation() override;

	void Call_TempNextRound();

	UFUNCTION()
	void MyStepPlay();

	UFUNCTION()
	void MyStepPause();

	UFUNCTION()
	void MyStepSectionMovement(int num);

	UFUNCTION(BlueprintCallable)
	bool CheckStepCount();

	void Call_LastStep();

	void SetReturnStepIndex();

	void ReStartStep();

	FString GetNarrText(FString _textID);
private:
	bool IsGameEnd = false;
	int ReturnStepIndex = -1;
};
