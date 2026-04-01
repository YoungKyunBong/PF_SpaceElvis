#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"              // FStudentRowData 재사용
#include "StudentResultRowWidget.generated.h"

class UTextBlock;

UCLASS()
class MOJCMSCLIENT_API UStudentResultRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetRowData(const FStudentRowData& InData);

protected:
	// ── 기본 정보 ───────────────────────────────
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Name;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_ID;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Birth;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CrimeType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_EduCourse;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_VRType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_AVConcentration;

	// ── 사전검사 ───────────────────────────────
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Pre_Attack;      // 공격성

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Pre_Violence;    // 폭력성

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Pre_Relationship; // 대인관계

	// ── 사후검사 ───────────────────────────────
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Post_Attack;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Post_Violence;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Post_Relationship;

	// ── 만족도 / 진행상태 ──────────────────────
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Satisfaction;    // 만족도 (예: "진행", "완료" 대신 숫자면 "4점" 등)

	UPROPERTY(meta=(BindWidget, BlueprintReadWrite))
	UTextBlock* Txt_Status;          // "진행", "완료" 등 (원하면 사용)
};
