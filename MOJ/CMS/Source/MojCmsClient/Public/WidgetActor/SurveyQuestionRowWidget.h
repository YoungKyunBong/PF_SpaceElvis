#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "SurveyQuestionRowWidget.generated.h"


UCLASS()
class MOJCMSCLIENT_API USurveyQuestionRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintPure)
	int32 GetSelectedIndex() const { return SelectedIndex; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Survey")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetReverseScore() const;
	

	UFUNCTION(BlueprintCallable, Category="Survey")
	void SetMaxChoice(int32 InMaxChoice); // 5 or 6

	
protected:
	UPROPERTY(meta=(BindWidget)) UCheckBox* Check_1;
	UPROPERTY(meta=(BindWidget)) UCheckBox* Check_2;
	UPROPERTY(meta=(BindWidget)) UCheckBox* Check_3;
	UPROPERTY(meta=(BindWidget)) UCheckBox* Check_4;
	UPROPERTY(meta=(BindWidget)) UCheckBox* Check_5;
	UPROPERTY(meta=(BindWidgetOptional)) UCheckBox* Check_6;
	
private:
	bool bSyncing = false;
	int32 SelectedIndex = 0; // 1~5, 0 = 미선택
	int32 MaxChoice = 5;
	
	UFUNCTION() void On1(bool b);
	UFUNCTION() void On2(bool b);
	UFUNCTION() void On3(bool b);
	UFUNCTION() void On4(bool b);
	UFUNCTION() void On5(bool b);
	UFUNCTION() void On6(bool b);

	void HandleCheck(bool bIsChecked, int32 Index);
	void SetOnly(int32 Index);
};
