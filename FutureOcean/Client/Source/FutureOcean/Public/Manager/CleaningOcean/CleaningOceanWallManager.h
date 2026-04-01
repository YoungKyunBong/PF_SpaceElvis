

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CleaningOceanWallManager.generated.h"

/**
 *
 */
UCLASS()
class FUTUREOCEAN_API UCleaningOceanWallManager : public UWorldSubsystem
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
	void SendFloorSpawnTypeToServer();
	UFUNCTION()
	void RecvSideTypeFromServer();
	
	UFUNCTION()
	SIDE_TYPE Get_SideType();
	UFUNCTION()
	void SetSideType(SIDE_TYPE Type);
	UFUNCTION()
	void CheckWallLevel();
	bool bWallLevel = false;  // 특정 레벨 여부를 나타낼 변수
	TArray<SIDE_TYPE> CurType;



};
