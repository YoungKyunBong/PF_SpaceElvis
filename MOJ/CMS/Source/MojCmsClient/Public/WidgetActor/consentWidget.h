#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "ConsentWidget.generated.h"

UCLASS()
class MOJCMSCLIENT_API UConsentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// 현재 선택값 가져오기용(원하면 사용)
	UFUNCTION(BlueprintCallable)
	bool IsAgreed() const { return bAgreed; }

protected:
	UPROPERTY(meta=(BindWidget))
	UCheckBox* Check_Agree;

	UPROPERTY(meta=(BindWidget))
	UCheckBox* Check_Disagree;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Save;

private:
	// 이벤트 재진입 방지용
	bool bSyncing = false;

	// 선택 상태 저장(선택이 없으면 false로 남음)
	bool bAgreed = false;

	UFUNCTION()
	void OnAgreeChanged(bool bIsChecked);

	UFUNCTION()
	void OnDisagreeChanged(bool bIsChecked);

	void SetRadioState(bool bAgreeChecked, bool bDisagreeChecked);
};
