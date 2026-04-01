

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "FadeActor.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AFadeActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsFadeIn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsNext;

	UFUNCTION(BlueprintCallable)
	void CallCustomFade();

	UFUNCTION(BlueprintCallable)
	void Call_LastStep();
};
