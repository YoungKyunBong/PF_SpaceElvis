

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StepActor.generated.h"

UCLASS()
class FUTUREOCEAN_API AStepActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	AStepManager* stepManager;

	UFUNCTION(BlueprintCallable)
	virtual void Init(AStepManager* Manager) { stepManager = Manager; }

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void MyStep(AStepManager* Manager);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void MyStep_Implementation(AStepManager* Manager) {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SkipStep();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SkipStep_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void RewindStep();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void RewindStep_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void ResetSkip();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void ResetSkip_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SkipWidget")
	void ClickCheck();
	UFUNCTION(BlueprintCallable, Category = "SkipWidget")
	virtual void ClickCheck_Implementation() {}

	virtual void CMS_Start();
	virtual void CMS_Stop(){}
};
