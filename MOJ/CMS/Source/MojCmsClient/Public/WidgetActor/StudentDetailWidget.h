#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"  // FStudentRowData 사용
#include "StudentDetailWidget.generated.h"

class UTextBlock;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrimeChanged, const FString&, CrimeType);
UCLASS()
class MOJCMSCLIENT_API UStudentDetailWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetDetailData(const FStudentRowData& InData);

	UPROPERTY(BlueprintAssignable)
	FOnCrimeChanged OnCrimeChanged;

	UFUNCTION(BlueprintImplementableEvent, Category="Student")
	void SetDetailImage(const FString& CrimeType);
	
protected:
	// 상단 정보 표시용
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Name;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_ID;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Birth;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_CrimeType;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_EduCourse;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_VrType;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Concentration;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Name_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_ID_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Birth_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_CrimeType_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_EduCourse_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_VrType_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Concentration_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre2;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre3;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre4;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post2;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post3;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post4;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Satisfaction;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre1_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre2_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre3_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre4_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post1_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post2_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post3_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post4_1;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Satisfaction_1;

	//마약용
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre5;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre6;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre7;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Pre8;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post5;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post6;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post7;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TxtD_Post8;

	

	// 나중에 집중도 5행 테이블 붙이고 싶으면 여기부터 확장
	
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session1Score;
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session1Note;

	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session2Score;
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session2Note;

	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session3Score;
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session3Note;

	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session4Score;
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session4Note;

	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session5Score;
	UPROPERTY(meta=(BindWidget)) UTextBlock* Txt_Session5Note;
};
