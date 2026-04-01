// StudentDashboardWidget.cpp

#include "WidgetActor/StudentDashboardWidget.h"
#include "Components/TextBlock.h"
#include "Manager/GameManager.h"

void UStudentDashboardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// GameManager 캐시
	if (UWorld* World = GetWorld())
	{
		GM = World->GetGameInstance<UGameManager>();
	}

	// 날짜 카드 먼저 채우기
	RefreshDate();

	// GameManager 통계 연동
	if (GM)
	{
		// 데이터 변경 델리게이트 구독
		GM->OnStudentRowsUpdated.AddUObject(
			this, &UStudentDashboardWidget::OnStudentRowsUpdated);

		// 이미 StudentRows 가 있으면 바로 한 번 갱신
		RefreshDashboard();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StudentDashboardWidget: GameManager not found"));
	}
}

void UStudentDashboardWidget::OnStudentRowsUpdated()
{
	RefreshDashboard();
}

void UStudentDashboardWidget::RefreshDate()
{
	const FDateTime Now = FDateTime::Now();

	// 요일 한글
	static const TCHAR* DayNames[7] =
	{
		TEXT("일"), TEXT("월"), TEXT("화"),
		TEXT("수"), TEXT("목"), TEXT("금"), TEXT("토")
	};

	int32 DayOfWeekIndex = static_cast<int32>(Now.GetDayOfWeek());
	if (DayOfWeekIndex < 0 || DayOfWeekIndex > 6)
	{
		DayOfWeekIndex = 0;
	}

	const FString DateStr = FString::Printf(
		TEXT("%d년 %02d월 %02d일 (%s)"),
		Now.GetYear(),
		Now.GetMonth(),
		Now.GetDay(),
		DayNames[DayOfWeekIndex]
	);

	if (Txt_TodayDate)
	{
		Txt_TodayDate->SetText(FText::FromString(DateStr));
	}
}

void UStudentDashboardWidget::RefreshDashboard()
{
    if (!GM)
    {
        return;
    }

    int32 TotalStudents     = 0;
    int32 CompletedStudents = 0;
    TMap<FString,int32> CrimeCounts;

    CalcStats(TotalStudents, CompletedStudents, CrimeCounts);

    // --- 상단 카드 ---

    if (Txt_TotalAccumulated)
    {
        const FString AccStr = FString::Printf(TEXT("%d명"), TotalStudents);
        Txt_TotalAccumulated->SetText(FText::FromString(AccStr));
    }

    if (Txt_TotalStudents)
    {
        const FString TotalStr = FString::Printf(TEXT("%d명"), TotalStudents);
        Txt_TotalStudents->SetText(FText::FromString(TotalStr));
    }

    float CompletionRate = 0.f;
    if (TotalStudents > 0)
    {
        CompletionRate = (float)CompletedStudents * 100.f / (float)TotalStudents;
    }

    if (Txt_CompletionRate)
    {
        const FString RateStr = FString::Printf(TEXT("%.1f%%"), CompletionRate);
        Txt_CompletionRate->SetText(FText::FromString(RateStr));
    }

    // --- 범죄유형별 카운트 ---

    auto FormatCrimeText = [TotalStudents](int32 Count) -> FString
    {
        return FString::Printf(TEXT("%d/%d"), Count, TotalStudents);
    };

    const int32 SexCnt      = CrimeCounts.FindRef(TEXT("성폭력"));
    const int32 DomesticCnt = CrimeCounts.FindRef(TEXT("가정폭력"));
    const int32 ChildCnt    = CrimeCounts.FindRef(TEXT("아동학대"));
    const int32 StalkingCnt = CrimeCounts.FindRef(TEXT("스토킹"));
    const int32 DrugCnt     = CrimeCounts.FindRef(TEXT("마약"));

    if (Txt_SexCrimeCount)
        Txt_SexCrimeCount->SetText(FText::FromString(FormatCrimeText(SexCnt)));

    if (Txt_DomesticCount)
        Txt_DomesticCount->SetText(FText::FromString(FormatCrimeText(DomesticCnt)));

    if (Txt_ChildAbuseCount)
        Txt_ChildAbuseCount->SetText(FText::FromString(FormatCrimeText(ChildCnt)));

    if (Txt_StalkingCount)
        Txt_StalkingCount->SetText(FText::FromString(FormatCrimeText(StalkingCnt)));

    if (Txt_DrugCount)
        Txt_DrugCount->SetText(FText::FromString(FormatCrimeText(DrugCnt)));

    // --- 도넛 퍼센트 (0~1 범위) 계산 ---

    auto ToRate = [TotalStudents](int32 Count) -> float
    {
        return (TotalStudents > 0)
            ? (float)Count / (float)TotalStudents   // 예: 0.2 = 20%
            : 0.f;
    };

    const float SexRate      = ToRate(SexCnt);
    const float DomesticRate = ToRate(DomesticCnt);
    const float ChildRate    = ToRate(ChildCnt);
    const float StalkingRate = ToRate(StalkingCnt);
    const float DrugRate     = ToRate(DrugCnt);

    // --- WBP_CategoryCircle 에 값 전달 ---

    if (Circle_SexCrime)
        Circle_SexCrime->SetPercent(SexRate);      // 머티리얼 Percent = 0~1 기준

    if (Circle_Domestic)
        Circle_Domestic->SetPercent(DomesticRate);

    if (Circle_ChildAbuse)
        Circle_ChildAbuse->SetPercent(ChildRate);

    if (Circle_Stalking)
        Circle_Stalking->SetPercent(StalkingRate);

    if (Circle_Drug)
        Circle_Drug->SetPercent(DrugRate);
}


void UStudentDashboardWidget::CalcStats(
	int32& OutTotalStudents,
	int32& OutCompletedStudents,
	TMap<FString,int32>& OutCrimeTypeCounts
	) const
{
	OutTotalStudents    = 0;
	OutCompletedStudents = 0;
	OutCrimeTypeCounts.Empty();

	if (!GM) return;

	const TArray<FStudentRowData>& Rows = GM->GetStudentRows();

	for (const FStudentRowData& Row : Rows)
	{
		OutTotalStudents++;

		// 수료여부
		if (Row.Fin == TEXT("수료"))
		{
			OutCompletedStudents++;
		}

		// 범죄 유형 카운트
		int32& CountRef = OutCrimeTypeCounts.FindOrAdd(Row.CrimeType);
		CountRef++;
	}
}
