// CategoryCircleWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CategoryCircleWidget.generated.h"

UCLASS(Blueprintable)
class MOJCMSCLIENT_API UCategoryCircleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// C++에서 부를 함수, BP에서 구현
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="CategoryCircle")
	void SetPercent(float InPercent);
};
