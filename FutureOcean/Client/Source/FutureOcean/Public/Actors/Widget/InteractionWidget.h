

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
class UWidgetSwitcher;
class AInteractionWidgetActor;
class UFadeWidget;

UCLASS()
class FUTUREOCEAN_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetWidgetActor(AInteractionWidgetActor* _WidgetActor) { WidgetActor = _WidgetActor; }

	void SetFadeAnim(bool IsFadeIn);

	void SetFadeImageOp(float _op);

	void SetWidgetSwitcherIndex(int _index);

protected:
	UPROPERTY(BlueprintReadWrite)
	UFadeWidget* C_FadeWidget;

	UPROPERTY(BlueprintReadWrite)
	UWidgetSwitcher* C_WidgetSwitcher;

private:
	AInteractionWidgetActor* WidgetActor;
};
