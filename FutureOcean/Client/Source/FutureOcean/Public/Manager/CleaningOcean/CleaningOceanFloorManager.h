#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CleaningOceanFloorManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API UCleaningOceanFloorManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION()
	void SendSceneTypeToServer();
	UFUNCTION()
	void CheckFloorLevel();
	UFUNCTION()
	void SendLeftSideToServer();
	UFUNCTION()
	void SendRightSideToServer();
	UFUNCTION()
	void SendPlayWhaleSound();
	UFUNCTION()
	void RecvPlayWhaleSound();
	UFUNCTION()
	void SetWhaleSoundType(WHALE_SOUND_DISTANCE_TYPE Type);
	UFUNCTION()
	WHALE_SOUND_DISTANCE_TYPE GetSoundType() { return SoundType; }

private:
	bool bFloorLevel = false;  // 특정 레벨 여부를 나타낼 변수
	WHALE_SOUND_DISTANCE_TYPE SoundType;
};
