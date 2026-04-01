

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "StepManager.generated.h"

UCLASS()
class FUTUREOCEAN_API AStepManager : public ADefaultManager
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	FString StepName;

	UFUNCTION(BlueprintCallable)
	void SetNameCheck(AActor* checkActor, FString appendName);

	bool IsGameStop = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StepManagerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AStepActor*> stepActors;

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
	bool CheckStepCount();

	virtual void Call_AnimFadeWidget(bool IsFadeIn) override;
	//virtual void Call_WidgetSwitcherIndex(int _index) override;
	
	void Call_CmsIsStart(bool _IsStart);

	void Call_LastStep();

	UFUNCTION(BlueprintCallable)
	void SetGamePlay(bool _IsGameStop) override;
private:
	bool IsGameEnd = false;
};
