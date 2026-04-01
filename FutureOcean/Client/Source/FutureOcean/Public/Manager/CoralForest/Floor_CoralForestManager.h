

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Floor_CoralForestManager.generated.h"

/**
 * 
 */

class USoundBase;
class AFlagCoralActor;

UCLASS()
class FUTUREOCEAN_API AFloor_CoralForestManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	AFloor_CoralForestManager();

	virtual	void C_Init() override;

	UFUNCTION()
	void SendOverlapToServer(CORAL_TYPE _Type);

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvCoralWhiteSwitch();

	UFUNCTION()
	void RecvCoralOverlap(CORAL_TYPE _Type);

	//virtual void RecvLevelEnd() override;
	virtual void RecvCoralLevelEnd() override;

	virtual void SetCmsIsStart(bool isStart) override;

	virtual void RecvPlayTimeOutEvent() override;

	virtual void RecvOceanCleanChange() override;

	//virtual void SetTimeLine_EnvFloatValue() override;
	virtual void SetTimeLine_EnvColorValue() override;

	void ChangeSkipBinding();
	//UFUNCTION()
	//void RecvLevelEnd();

	void TimeOutDelay();

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Dirty;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Clean;

	UPROPERTY(EditAnywhere)
	USoundBase* CoralOverlapSound;

	UPROPERTY(EditAnywhere)
	UCurveFloat* envFloatValue_Curve;

	UPROPERTY(EditAnywhere)
	UCurveLinearColor* envColorValue_Curve;

private:
	TArray<AFlagCoralActor*> FlagCoralActors;

	float Finishtime = 10.f; // æ¿¿¸»Ø
};
