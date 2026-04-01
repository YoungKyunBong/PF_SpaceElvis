

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Wall_CoralForestManager.generated.h"


class AFlagCoralActor;
UCLASS()
class FUTUREOCEAN_API AWall_CoralForestManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	AWall_CoralForestManager();

	virtual	void C_Init() override;
	UFUNCTION(BlueprintNativeEvent)
	void PlayFishSwim();
	UFUNCTION(BlueprintCallable)
	virtual void PlayFishSwim_Implementation() {}
	
	UFUNCTION()
	void OverlapInteraction(CORAL_TYPE _Type);


	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	void PlayfishSwimming();
	void EndInteractionChangeOpValue();
	void SendLevelEnd();
	//virtual void TimeOutEvent() override;

	//virtual void RecvLevelEnd() override;
	virtual void RecvCoralLevelEnd() override;

	virtual void SetCmsIsStart(bool isStart) override;

	virtual void RecvPlayTimeOutEvent() override;

	virtual void RecvOceanCleanChange() override;

	virtual void Call_Intro_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

	//virtual void SetTimeLine_EnvFloatValue() override;
	virtual void SetTimeLine_EnvColorValue() override;

	void TimeOutDelay();
	UFUNCTION()
	PROTOCOLSUB_TYPE Get_Type();
	UPROPERTY(EditAnywhere)
	UCurveFloat* envFloatValue_Curve;

	UPROPERTY(EditAnywhere)
	UCurveLinearColor* envColorValue_Curve;

	//>>------------------------------------------------------ 서버 없이 & 산호초 센서 없는 상태로 서버 테스트를 위한 구조

	UFUNCTION(BlueprintCallable)
	void Send_CoralOverlap(CORAL_TYPE _Type);

	//<<------------------------------------------------------

private:
	//void ChangeSkipBinding();

	UPROPERTY()
	TArray<TObjectPtr<AFlagCoralActor>> FlagCoralActors;
	int32 InteractionCnt = 0;
	int32 sendCount = 0;
	int32 FlagCount = 0;
	int32 FlagFinishCount = 0;
	int32 alphaTotalCount = 0;
	
	bool isOneTime = true;
	int32 currOverlapType;
	int32 maxCount = 3;

	bool IsPlayTime = true;

	UPROPERTY(EditAnywhere)
	float Finishtime = 30.f; // 씬전환

	bool IsFail = false;
};
