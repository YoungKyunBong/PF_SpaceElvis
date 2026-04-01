

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void CustomFadeIn();
	UFUNCTION(BlueprintCallable)
	virtual void CustomFadeIn_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void CustomFadeOut();
	UFUNCTION(BlueprintCallable)
	virtual void CustomFadeOut_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void SetFadeImageOp(float _op);
	UFUNCTION(BlueprintCallable)
	virtual void SetFadeImageOp_Implementation(float _op) {}
};
