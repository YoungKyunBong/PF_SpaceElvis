

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Floor_KelpForestManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AFloor_KelpForestManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	AFloor_KelpForestManager();
	virtual	void C_Init() override;
	UFUNCTION()
	void SendOilOverlapToServer();
	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);
	UFUNCTION()
	void RecvPlaySequence();



	void CheckDisableOilCount();
	//virtual void SetCmsIsStart(bool isStart) override;
	virtual void Call_Interaction_SQ_End() override;
	virtual void RecvPlayTimeOutEvent() override;

	virtual void SetTimeLine_EnvFloatValue() override;
	virtual void SetTimeLine_EnvColorValue() override;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Dirty;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Clean;

	UPROPERTY(EditAnywhere)
	UCurveFloat* envFloatValue_Curve;

	UPROPERTY(EditAnywhere)
	UCurveLinearColor* envColorValue_Curve;
public:
	UPROPERTY()
	int OilCount = 0;

	UPROPERTY()
	TArray<TObjectPtr<class ACleaningOilActor>> oilActors;

	virtual void SetCmsIsStart(bool isStart) override;

protected:
	int oilDisableCount = 0;

	bool isSuccess = true;
};
