

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Wall_CleaningOceanManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AWall_CleaningOceanManager : public ADefaultManager
{
	GENERATED_BODY()
protected:
	AWall_CleaningOceanManager();

	UPROPERTY(EditAnywhere)
	bool IsTest;

	UPROPERTY(EditAnywhere)
	SIDE_TYPE noneServerSideType;

	UFUNCTION(BlueprintImplementableEvent)
	void WorldSetting(WHALE_SOUND_DISTANCE_TYPE _type);
	UFUNCTION(BlueprintCallable)
	void WorldSetting_Implementation(WHALE_SOUND_DISTANCE_TYPE _type) {}

public:
	virtual void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvWallSpawnWhale(SIDE_TYPE _type);

	UFUNCTION()
	void RecvChangeWhaleDirection();

	UFUNCTION()
	inline void RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE _type);

	UFUNCTION()
	void RecvFloorSpawnWhale(SIDE_TYPE _type, bool _isSuccess);

	//UFUNCTION()
	//void RecvLevelEnd();

	UFUNCTION(BlueprintCallable)
	void TestCallPlayWhaleSound();

	void SendChangeWhaleDirection();
	void SendWallSpawnWhaleEnd();

	virtual void SetCmsIsStart(bool isStart) override;

	virtual void TimeOutEvent() override;

	virtual void Call_Intro_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

	virtual void SetTimeLine_EnvFloatValue() override;
	virtual void SetTimeLine_EnvColorValue() override;

	UPROPERTY(EditAnywhere)
	class AWhaleCharacter* whaleActor;

	UPROPERTY(EditAnywhere)
	UCurveFloat* envFloatValue_Curve;

	UPROPERTY(EditAnywhere)
	UCurveLinearColor* envColorValue_Curve;

private:
	bool IsWhaleMoveEnd = false;
	bool IsPlaySequenceEnd = false;

};
