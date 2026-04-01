

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Floor_LuminaryManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AFloor_LuminaryManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	virtual	void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvPlayEffectSound(EFFECT_SOUND_TYPE _type);

	UFUNCTION()
	void RecvLumiFishEnd();

	virtual void SetCmsIsStart(bool isStart) override;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Clean;
};
