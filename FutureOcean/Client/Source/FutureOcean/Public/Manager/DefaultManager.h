
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DefaultManager.generated.h"

class UGameManager;
class ADefaultGameMode;

UCLASS()
class FUTUREOCEAN_API ADefaultManager : public AActor
{
	GENERATED_BODY()
	
private:
	UGameManager* GameIns;
	ADefaultGameMode* GameMode;

protected:

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void SetGameManager(UGameManager* _GameIns) { GameIns = _GameIns; }

	UFUNCTION(BlueprintCallable)
	void SetGameMode(ADefaultGameMode* _GameMode) { GameMode = _GameMode; }

	FTimerHandle FinishHandle;

	UPROPERTY(EditAnywhere)
	float Playtime = 600.f; // 플레이어타임

	bool IsCmsState = false;

	bool checkTestGame = false;

public:
	UFUNCTION(BlueprintCallable)
	virtual void C_Init();

	UFUNCTION()
	virtual void RecvLevelEnd();

	UFUNCTION()
	virtual void RecvInfoMovieLevelEnd() {}

	UFUNCTION()
	virtual void RecvCoralLevelEnd() {}

	UFUNCTION()
	void RecvCmsStart();

	UFUNCTION()
	void RecvCmsStop();

	UFUNCTION()
	virtual void RecvCmsReset(RESET_TYPE _type);

	UFUNCTION()
	virtual void RecvCmsNewPlayerReset(FString _levelName);

	virtual void SetCmsIsStart(bool isStart){}

	UFUNCTION()
	virtual void RecvOceanCleanChange();

	virtual void SendOceanCleanChange();

	UFUNCTION()
	virtual void RecvPlayTimeOutEvent();

	UFUNCTION(BlueprintCallable)
	UGameManager* GetGameManager() { return GameIns; }

	UFUNCTION(BlueprintCallable)
	ADefaultGameMode* GetGameMode() { return GameMode; }

	UFUNCTION(BlueprintNativeEvent)
	void CustomInit();
	UFUNCTION(BlueprintCallable)
	virtual void CustomInit_Implementation() {}

	UFUNCTION(BlueprintCallable)
	inline void TestCall_ChangeEnv() { ChangeEnvironment(); }

	UFUNCTION(BlueprintNativeEvent)
	void ChangeEnvironment();
	UFUNCTION(BlueprintCallable)
	virtual void ChangeEnvironment_Implementation();

	virtual void Call_AnimFadeWidget(bool IsFadeIn) {}
	virtual void Call_FadeImageOp(float _op) {}
	virtual void Call_WidgetSwitcherIndex(int _index) {}

	virtual void SetGamePlay(bool _IsGameStop) {}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsCmsState() { return IsCmsState; }

	virtual void TimeOutEvent();

	virtual void Call_Intro_SQ_End() {}
	virtual void Call_Interaction_SQ_End() {}
	virtual void Call_DefaultLevelEnd() {}

	UPROPERTY(EditAnywhere)
	class APlaySequenceActor* PlaySequenceActor;

	//>>------------------------------------------------------ CMS 테스트 부분

	UFUNCTION(BlueprintCallable)
	void SendCmsPlay();

	UFUNCTION(BlueprintCallable)
	void SendCmsStop();

	UFUNCTION(BlueprintCallable)
	void SendCmsSkip();

	UFUNCTION(BlueprintCallable)
	void SendCmsReset(RESET_TYPE _type);

	UFUNCTION(BlueprintCallable)
	void SendTempBgWall();

	UFUNCTION(BlueprintCallable)
	void SendTempBgFloor();

	//<<------------------------------------------------------

protected:

	virtual void SetTimeLine_EnvFloatValue() {}
	virtual void SetTimeLine_EnvColorValue() {}

	UFUNCTION()
	void Binding_EnvFloatUpdate(float Value);

	UFUNCTION()
	void Binding_EnvFloatFinished();

	UFUNCTION()
	void Binding_EnvColorUpdate(FLinearColor Value);

	UFUNCTION()
	void Binding_EnvColorFinished();

	UPROPERTY(EditAnywhere)
	class APostProcessVolume* C_PostProcessVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AExponentialHeightFog* C_ExponentialHeightFog;

	UPROPERTY(EditAnywhere)
	float envDefaultTimeRate = 10.f;

	UTimelineComponent* envFloatValue_TimeLine;
	FOnTimelineFloat envFloatValue_TimelineCallback;
	FOnTimelineEvent envFloatValue_TimelineFinishedCallback;

	UTimelineComponent* envColorValue_TimeLine;
	FOnTimelineLinearColor envColorValue_TimelineCallback;
	FOnTimelineEvent envColorValue_TimelineFinishedCallback;

	FVector4 PostProcessValue_ColorGamma_Before = FVector4(0.968317f, 0.957163f, 1.0f, 1.0f);
	FVector4 PostProcessValue_ColorGamma_After = FVector4(1.161981f, 1.148595f, 1.2f, 1.0f);

	float PostProcessValue_BloomIntensity_Before = 0.0f;
	float PostProcessValue_BloomIntensity_After = 4.0f;

	float PostProcessValue_AutoExposureBias_Before = 10.92;
	float PostProcessValue_AutoExposureBias_After = 11.5;

	float PostProcessValue_LocalExposureHighlightContrastScale_Before = 0.8f;
	float PostProcessValue_LocalExposureHighlightContrastScale_After = 0.5f;

	float PostProcessValue_LocalExposureDetailStrength_Before = 0.5f;
	float PostProcessValue_LocalExposureDetailStrength_After = 1.5f;

	FVector4 PostProcessValue_ColorSaturation_Before = FVector4(0.85f, 0.85f, 0.85f, 1.0f);
	FVector4 PostProcessValue_ColorSaturation_After = FVector4(1.2f, 1.2f, 1.2f, 1.0f);

	float PostProcessValue_Sharpen_Before = 1;
	float PostProcessValue_Sharpen_After = 5;

	FLinearColor ExponentialHeightFog_FogInscatteringColor_Before = FLinearColor::FromSRGBColor(FColor::FromHex(TEXT("001531FF")));
	FLinearColor ExponentialHeightFog_FogInscatteringColor_After = FLinearColor::FromSRGBColor(FColor::FromHex(TEXT("000556FF")));
};
