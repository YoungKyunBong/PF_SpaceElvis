#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentSessionMonitorWidget.h"        // FHeartRateLog 쓰려고 (또는 struct만 따로 헤더로 분리)
#include "HeartRateGraphWidget.generated.h"

UCLASS()
class MOJCMSCLIENT_API UHeartRateGraphWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 로그 세팅 (외부에서 호출)
	UFUNCTION(BlueprintCallable)
	void SetLogs(const TArray<FHeartRateLog>& InLogs);

protected:
	// 실제 그리기
	virtual int32 NativePaint(const FPaintArgs& Args,
							  const FGeometry& AllottedGeometry,
							  const FSlateRect& MyCullingRect,
							  FSlateWindowElementList& OutDrawElements,
							  int32 LayerId,
							  const FWidgetStyle& InWidgetStyle,
							  bool bParentEnabled) const override;

	// 내부용 로그 복사본
	UPROPERTY()
	TArray<FHeartRateLog> Logs;

	// 그래프 스타일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graph", meta=(ClampMin="1.0"))
	float LineThickness = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graph")
	FLinearColor LineColor = FLinearColor(0.12f, 0.16f, 0.26f, 1.f); // 짙은 파란색 느낌

	// BPM 스케일 범위 (자동 스케일 대신 고정 범위 쓰고 싶으면 값 조정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graph")
	float MinBpm = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graph")
	float MaxBpm = 150.f;
};
