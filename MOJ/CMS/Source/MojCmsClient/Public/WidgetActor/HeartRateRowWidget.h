#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartRateRowWidget.generated.h"

class UTextBlock;

UCLASS()
class MOJCMSCLIENT_API UHeartRateRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UMG에서 바인딩할 텍스트 블록들
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* Txt_Time;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock* Txt_Bpm;

	// C++ 또는 BP 양쪽에서 호출 가능한 셋업 함수
	UFUNCTION(BlueprintCallable)
	void Setup(const FString& InTimeText, const FString& InBpmText);
};
