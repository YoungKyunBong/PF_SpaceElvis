

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Wall_LuminaryManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AWall_LuminaryManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	virtual	void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	UFUNCTION()
	void RecvLumiFishEnd();

	UFUNCTION(BlueprintCallable)
	void SendLumiFishHit();

	UFUNCTION(BlueprintCallable)
	void SendLumiFishFind();

	virtual void SetCmsIsStart(bool isStart) override;
	virtual void Call_Intro_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

protected:
	UFUNCTION(BlueprintCallable)
	inline void SetFishCount(int _count) { fishCount = _count; }

	UFUNCTION(BlueprintCallable)
	void TempLevelEnd();

private:
	int fishCount;
	int findFishCount = 0;
};
