// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "TotalFeedbackPrintActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ATotalFeedbackPrintActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextDelay = 5.0f;

public:
	virtual void CmsSectionMovement() override;

protected:
	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SetWidgetInterControl(bool isVisible);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SetWidgetInterControl_Implementation(bool isVisible) {}

private:
	FTimerHandle Handle;

	int index = 0;

	FString TotalText;

	void SetPrintText();

	void SetTimer_PrintText();
};
