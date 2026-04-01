// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "TotalFeedBackTextActor.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ATotalFeedBackTextActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TextDelay = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HeaderTextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WordFirstID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WordEndID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ButtonTextID;

public:
	virtual void ReplayStep_Implementation(FSelectButton selectButton) override;

protected:
	UFUNCTION(BlueprintCallable)
	void Call_WidgetInterControl(bool isVisible) { SetWidgetInterControl(isVisible); }

	UFUNCTION(BlueprintCallable)
	void SetButtonTextToWidget();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void SetWidgetInterControl(bool isVisible);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void SetWidgetInterControl_Implementation(bool isVisible) {}
};
