#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CleaningOilManager.generated.h"

/**
 *
 */

class ACleaningOilActor;

UCLASS()
class FUTUREOCEAN_API UCleaningOilManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem
	UFUNCTION()
	void RegisterCleaningOilActor(ACleaningOilActor* CleaningOilActor);
	UFUNCTION()
	void SendActorCountToServer();
	UFUNCTION()
	void SendSceneTypeToServer();
	UFUNCTION()
	void SendOilOverlapToServer();
	UFUNCTION()
	void PollutedCoralChangeOpValue();
	UFUNCTION()
	void CheckFloorLevel();

	UFUNCTION()
	bool GetFloorLevel() { return bFloorLevel; }
	const TArray<TObjectPtr<ACleaningOilActor>>& GetCleaningOilActors() const;
private:
	TArray<TObjectPtr<ACleaningOilActor>> CleaningOilActors;
	bool bFloorLevel = false;  // 특정 레벨 여부를 나타낼 변수

	int32 CleaningOilCnt = 0;
	int32 Test2Cnt = 0;
};
