#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Protocols.h"
#include "Components/TimelineComponent.h"
#include "NiagaraComponent.h"
#include "FlagCoralActor.generated.h"

class AWall_CoralForestManager;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UStaticMesh;
class UTimelineComponent;
class UCurveFloat;

UCLASS()
class FUTUREOCEAN_API AFlagCoralActor : public AActor
{
	GENERATED_BODY()


public:
	AFlagCoralActor();
	virtual void BeginPlay() override;

	void Init(AWall_CoralForestManager* _manager);	
	UFUNCTION(BlueprintCallable)
	void FadeSwitch();
	UFUNCTION(BlueprintCallable)
	void WhiteSwitch();
	UFUNCTION(BlueprintCallable)
	void PlaySpringEffect();
	UFUNCTION(BlueprintCallable)
	void PlayNiagaraEffect();

	UFUNCTION(BlueprintNativeEvent)
	void SpawnAnimSequence();
	UFUNCTION(BlueprintCallable)
	virtual void SpawnAnimSequence_Implementation() {}
	
	CORAL_TYPE Get_CoralType() { return CoralType; }
	bool Get_CoralFade() { return bFade; }	

protected:
	UFUNCTION(BlueprintCallable)
	void TempSetMesh();
	/*타임라인 업데이트 콜백*/
	UFUNCTION()
	void HandleFadeUpdate(float Value);
	UFUNCTION()
	void HandleWhiteUpdate(float Value);	
	UFUNCTION()
	void HandleSpringScaleZ(float Value);

	UFUNCTION()
	void HandleSpringScaleY(float Value);

	UFUNCTION()
	void HandleSpringRotation(float Value);

	/*타임라인 종료 콜백*/
	UFUNCTION()
	void HandleFadeFinished();
	UFUNCTION()
	void HandleWhiteFinished();
	UFUNCTION()
	void HandleSpringFinished();

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> FlagMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstanceDynamic> MInsDyn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> TempMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> DefaultWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Timeline")
	TObjectPtr<UTimelineComponent> FadeTimeline;
	UPROPERTY(VisibleAnywhere, Category = "Timeline")
	TObjectPtr<UTimelineComponent> WhiteTimeline;
	UPROPERTY(VisibleAnywhere, Category = "Timeline")
	TObjectPtr<UTimelineComponent> SpringTimeline;

	/*타임라인 커브*/
	UPROPERTY(EditAnywhere, Category = "Timeline")
	TObjectPtr<UCurveFloat> FadeCurve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	TObjectPtr<UCurveFloat> WhiteCurve;
	/* 스프링 효과를 위한 커브*/
	UPROPERTY(EditAnywhere, Category = "Animation")
	UCurveFloat* SpringScaleXCurve;  // X축 스케일용 커브
	UPROPERTY(EditAnywhere, Category = "Animation")
	UCurveFloat* SpringScaleYCurve;  // Y축 스케일용 커브
	UPROPERTY(EditAnywhere, Category = "Animation")
	UCurveFloat* SpringRotationCurve;  // 회전용 커브
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    TObjectPtr<UNiagaraComponent> NiagaraEffectComponent_Barrier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UNiagaraComponent> NiagaraEffectComponent_Bomb;

	FOnTimelineFloat FadeTimelineCallback;
	FOnTimelineFloat WhiteTimelineCallback;
	FOnTimelineFloat SpringScaleXCallback;
	FOnTimelineFloat SpringScaleYCallback;
	FOnTimelineFloat SpringRotationCallback;
	FOnTimelineEvent FadeTimelineFinishedCallback;
	FOnTimelineEvent WhiteTimelineFinishedCallback;
	FOnTimelineEvent SpringTimelineFinishedCallback;

	/*초기 트랜스폼 저장용*/
	FVector OriginalScale;
	FRotator OriginalRotation;
	FString CurLevelName;
	FString	FloorLevelName = "CoralForest_Floor_Dev";

	UPROPERTY(EditAnywhere)
	CORAL_TYPE CoralType;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	float TimetoFade = 1.f;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	float TimetoWhite = 5.f;
	/*스프링 효과 지속 시간*/
	UPROPERTY(EditAnywhere, Category = "Animation")
	float SpringEffectDuration = 3.f;
	UPROPERTY()
	bool bFade = false;
	
private:
	UPROPERTY()
	TObjectPtr<AWall_CoralForestManager> coralManager;
};
