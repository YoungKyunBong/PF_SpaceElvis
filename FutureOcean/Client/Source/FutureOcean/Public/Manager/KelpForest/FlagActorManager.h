#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FlagActorManager.generated.h"

class AFlagCoralActor;
/**
 *
 */
UCLASS()
class FUTUREOCEAN_API UFlagActorManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	virtual void Deinitialize() override;
	UFUNCTION()
	void RegisterFlagCoraltActor(AFlagCoralActor* FlagCoralActor);
	UFUNCTION()
	void SendSceneTypeToServer();
	UFUNCTION()
	void RecvOverlapFromServer();
	UFUNCTION()
	const TArray<AFlagCoralActor*>& GetPollutedCoralActors() const;
	UFUNCTION()
	void RecvCoralType(CORAL_TYPE _Type);
	UFUNCTION()
	void OverlapInteraction(CORAL_TYPE _Type);
	UFUNCTION()
	void ChangeOpValue();
	UFUNCTION()
	bool GetWallLevel() { return bWallLevel; }

	UFUNCTION()
	int32 GetInteractionCnt() { return InteractionCnt; }

private:
	UPROPERTY()
	TArray<AFlagCoralActor*> FlagCoralActors;
	UPROPERTY()
	CORAL_TYPE CoralType;
	bool bWallLevel = false;  // 특정 레벨 여부를 나타낼 변수

	void CheckWallLevel();

	int32 InteractionCnt = 0;
};
