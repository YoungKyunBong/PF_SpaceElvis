#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Wall_KelpForestManager.generated.h"

/**
 * 
 */

UCLASS()
class FUTUREOCEAN_API AWall_KelpForestManager : public ADefaultManager
{
	GENERATED_BODY()

public:
	virtual void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void CleaningOilCount(int32 _Count);

	UFUNCTION()
	void RecvPlaySequence();

	UFUNCTION()
	void ChangeOpValue(int32 cnt);

	void CallOilLevelEnd();

	//UFUNCTION()
	//void RecvLevelEnd();

	//void SendWallSpawnWhaleEnd();

	//virtual void SetCmsIsStart(bool isStart) override;

	virtual void SetCmsIsStart(bool isStart) override;

public:
	UPROPERTY()
	int32 OilCount = 0;
	UPROPERTY()
	TArray<TObjectPtr<class APollutedCoralActor>> PollutedCoralActors;

	UPROPERTY(EditAnywhere)
	bool isPlaySequence = false;
	//UPROPERTY(EditAnywhere)
	//ULevelSequencePlayer* test2;

	virtual void RecvPlayTimeOutEvent() override;

	virtual void Call_Intro_SQ_End() override;
	virtual void Call_Interaction_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

	bool isSuccess = true;
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              