#include "WidgetActor/HeartRateGraphWidget.h"
#include "Rendering/DrawElements.h"

void UHeartRateGraphWidget::SetLogs(const TArray<FHeartRateLog>& InLogs)
{
	Logs = InLogs;
	// 다시 그리기 요청
	Invalidate(EInvalidateWidgetReason::Paint);
}

int32 UHeartRateGraphWidget::NativePaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect,
	                   OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (Logs.Num() < 2)
	{
		// 점이 2개 이하면 그릴 선이 없음
		return LayerId;
	}

	const FVector2D Size = AllottedGeometry.GetLocalSize();
	if (Size.X <= 0.f || Size.Y <= 0.f)
	{
		return LayerId;
	}

	// === 시간 범위 계산 (왼쪽 ~ 오른쪽) ===
	int64 FirstTs = Logs[0].TimestampMs;
	int64 LastTs  = Logs.Last().TimestampMs;
	double TotalMs = static_cast<double>(LastTs - FirstTs);
	if (TotalMs <= 0.0)
	{
		TotalMs = 1.0; // 0 나누기 방지
	}

	// === BPM 범위 계산 (자동 / 고정 혼합) ===
	float LocalMinBpm = MinBpm;
	float LocalMaxBpm = MaxBpm;

	for (const FHeartRateLog& L : Logs)
	{
		LocalMinBpm = FMath::Min(LocalMinBpm, static_cast<float>(L.Bpm));
		LocalMaxBpm = FMath::Max(LocalMaxBpm, static_cast<float>(L.Bpm));
	}
	if (FMath::IsNearlyEqual(LocalMinBpm, LocalMaxBpm))
	{
		LocalMaxBpm = LocalMinBpm + 1.f;
	}

	TArray<FVector2D> Points;
	Points.Reserve(Logs.Num());

	for (const FHeartRateLog& L : Logs)
	{
		// 0~1 시간 비율
		const double TimeAlpha = (static_cast<double>(L.TimestampMs - FirstTs)) / TotalMs;
		const float  X = static_cast<float>(TimeAlpha) * Size.X;

		// 0~1 BPM 비율
		const float BpmAlpha = (static_cast<float>(L.Bpm) - LocalMinBpm) / (LocalMaxBpm - LocalMinBpm);
		// 위가 높게 보이도록 Y 뒤집기
		const float Y = Size.Y * (1.f - BpmAlpha);

		Points.Add(FVector2D(X, Y));
	}

	// 선 그리기
	FSlateDrawElement::MakeLines(
		OutDrawElements,
		++LayerId,
		AllottedGeometry.ToPaintGeometry(),
		Points,
		ESlateDrawEffect::None,
		LineColor,
		true,             // bAntialias
		LineThickness
	);

	return LayerId;
}
