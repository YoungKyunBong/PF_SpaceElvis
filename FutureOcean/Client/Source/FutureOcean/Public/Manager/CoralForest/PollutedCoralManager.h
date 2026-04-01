

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PollutedCoralManager.generated.h"

/**
 * 
 */

class APollutedCoralActor;

UCLASS()
class FUTUREOCEAN_API UPollutedCoralManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	virtual void Deinitialize() override;
	UFUNCTION()
	void RegisterPollutedCoraltActor(APollutedCoralActor* PollutedCoralActor);
	UFUNCTION()
	void ChangeOpValue();
	UFUNCTION()
	void CleaningOilCount(int32 _Count);
	UFUNCTION()
	void SendSceneTypeToServer();
	UFUNCTION()
	void RecvOilCountFromServer();
	/*UFUNCTION()
	void RecvOilOverlapFromServer();*/
	UFUNCTION()
	const TArray<APollutedCoralActor*>& GetPollutedCoralActors() const;

	UFUNCTION()
	bool GetWallLevel() { return bWallLevel; }

private:
	UPROPERTY()
	TArray<APollutedCoralActor*> PollutedCoralActors;
	UPROPERTY()
	int32 OilCount = 0;
	bool bWallLevel = false;  // 특정 레벨 여부를 나타낼 변수

	void CheckWallLevel();
};