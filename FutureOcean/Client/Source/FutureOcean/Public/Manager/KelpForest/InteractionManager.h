#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractionManager.generated.h"

class AInteractionActor;
/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API UInteractionManager : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem
	UFUNCTION()
	void RegisterInteractionActor(AInteractionActor* InteractionActor);
	
	UFUNCTION()
	void SendSceneTypeToServer();
	UFUNCTION()
	void SendOverlapToServer(CORAL_TYPE _Type);
	UFUNCTION()
	void DepthSwitch(bool bEnable = false);
	UFUNCTION()
	void VisibilitySwitch(bool bEnable = false);
	
	
	UFUNCTION()
	void CheckFloorLevel();

	UFUNCTION()
	bool GetFloorLevel() { return bFloorLevel; }
	const TArray<TObjectPtr<AInteractionActor>>& GetInteractionActors() const;
private:
	TArray<TObjectPtr<AInteractionActor>> InteractionActors;
	bool bFloorLevel = false;  // 특정 레벨 여부를 나타낼 변수
	
};
