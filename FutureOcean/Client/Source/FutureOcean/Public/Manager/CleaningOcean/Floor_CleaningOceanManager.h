

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Floor_CleaningOceanManager.generated.h"

/**
 * 
 */

class USoundBase;

UCLASS()
class FUTUREOCEAN_API AFloor_CleaningOceanManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	AFloor_CleaningOceanManager();

	virtual void C_Init() override;

	UFUNCTION(BlueprintCallable)
	int CountOverlap(bool isAdd);

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvWallSpawnWhaleEnd();

	UFUNCTION()
	void RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE _type);

	UFUNCTION()
	void RecvFloorSpawnWhale(SIDE_TYPE _type, bool _isSuccess);

	UFUNCTION()
	void RecvPlayEffectSound(EFFECT_SOUND_TYPE _type);

	void SendPlayWhaleSound();

	void SendCleaningOceanLevelEnd();

	UPROPERTY(EditAnywhere)
	class AWhaleCharacter* whaleActor;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Dirty;

	UPROPERTY(EditAnywhere)
	USoundBase* BGSound_Clean;

	UPROPERTY(EditAnywhere)
	USoundBase* WallWhaleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* FloorWhaleSound;

	UPROPERTY(EditAnywhere)
	UCurveFloat* envFloatValue_Curve;

	UPROPERTY(EditAnywhere)
	UCurveLinearColor* envColorValue_Curve;

	virtual void SetCmsIsStart(bool isStart) override;

	virtual void SetTimeLine_EnvFloatValue() override;
	virtual void SetTimeLine_EnvColorValue() override;

	virtual void Call_Intro_SQ_End() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetCushionActors(bool isStart);
	UFUNCTION(BlueprintCallable)
	void SetCushionActors_Implementation(bool isStart){}

	UFUNCTION(BlueprintImplementableEvent)
	void WorldSetting(WHALE_SOUND_DISTANCE_TYPE _type);
	UFUNCTION(BlueprintCallable)
	void WorldSetting_Implementation(WHALE_SOUND_DISTANCE_TYPE _type) {}

	UPROPERTY(BlueprintReadWrite)
	float trashActorCount = 0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float ChangeRange = 0.5f;

	UPROPERTY(BlueprintReadOnly)
	float AddRange = 0.f;

private:
	TArray<class AFloorTrashActor*> floorTrashActors;
	bool isWallSpawnWhaleEnd = false;

	int trashActorOverlapCount = 1;

	EFFECT_SOUND_TYPE currSoundType;
	//int trashCount;
};
