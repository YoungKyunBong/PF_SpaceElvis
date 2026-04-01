// StudentDashboardWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"          // FStudentRowData
#include "WidgetActor/CategoryCircleWidget.h"
#include "StudentDashboardWidget.generated.h"

class UTextBlock;
class UGameManager;
class UCategoryCircleWidget; 
/**
 * 대시보드(메인) 위젯
 * - 오늘 날짜
 * - 누적 교육생 수
 * - 전체 교육생 수
 * - 교육 완료율
 * - 주요 범죄유형별 교육 현황 (성폭력 / 가정폭력 / 아동학대 / 스토킹 / 마약)
 */
UCLASS()
class MOJCMSCLIENT_API UStudentDashboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	/** 상단 카드 4개 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TodayDate;          // "2025년 11월 28일 (금)"

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TotalAccumulated;   // 누적 교육생 수 (예: "300명")

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TotalStudents;      // 전체 교육생 수 (예: "100명")

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CompletionRate;     // 교육 완료율 (예: "74.3%")

	/** 범죄 유형별 도넛 밑의 숫자 "5/100" 같은 표시용 텍스트 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_SexCrimeCount;      // 성폭력

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_DomesticCount;      // 가정폭력

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_ChildAbuseCount;    // 아동학대

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_StalkingCount;      // 스토킹

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_DrugCount;          // 마약


protected:
	UPROPERTY(meta=(BindWidget))
	UCategoryCircleWidget* Circle_SexCrime;

	UPROPERTY(meta=(BindWidget))
	UCategoryCircleWidget* Circle_Domestic;

	UPROPERTY(meta=(BindWidget))
	UCategoryCircleWidget* Circle_ChildAbuse;

	UPROPERTY(meta=(BindWidget))
	UCategoryCircleWidget* Circle_Stalking;

	UPROPERTY(meta=(BindWidget))
	UCategoryCircleWidget* Circle_Drug;
	

private:
	/** GameManager 캐시 */
	UPROPERTY()
	UGameManager* GM = nullptr;

	/** GameManager 의 OnStudentRowsUpdated 델리게이트 콜백 */
	void OnStudentRowsUpdated();

	/** 전체 UI 갱신 */
	void RefreshDashboard();

	/** 상단 날짜 카드 갱신 */
	void RefreshDate();

	/** 내부 통계 계산 (StudentRows 기반) */
	void CalcStats(
		int32& OutTotalStudents,
		int32& OutCompletedStudents,
		TMap<FString,int32>& OutCrimeTypeCounts
		) const;
};
