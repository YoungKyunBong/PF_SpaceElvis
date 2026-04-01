

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "InteractionWidgetActor.generated.h"

/**
 * 
 */

class UInteractionWidget;

UCLASS()
class FUTUREOCEAN_API AInteractionWidgetActor : public ADefaultManager
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UUserWidget> C_UserWidget;

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	virtual void Call_AnimFadeWidget(bool IsFadeIn) override;

	virtual void Call_FadeImageOp(float _op) override;

	virtual void Call_WidgetSwitcherIndex(int _index) override;

private:
	UInteractionWidget* widgetBP;

	void CustomCreateWidget();
};
