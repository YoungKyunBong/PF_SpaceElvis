

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Wall_CamouFlageManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AWall_CamouFlageManager : public ADefaultManager
{
	GENERATED_BODY()
	
public:
	virtual	void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvCamouFishEnd();

	UFUNCTION(BlueprintCallable)
	void SendCamouFishHit();

	UFUNCTION(BlueprintCallable)
	void SendCamouFishFind();

	virtual void SetCmsIsStart(bool isStart) override;
	virtual void Call_Intro_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

protected:
	UFUNCTION(BlueprintCallable)
	inline void SetFishCount(int _count) { fishCount = _count; }

private:
	int fishCount;
	int findFishCount = 0;
};
