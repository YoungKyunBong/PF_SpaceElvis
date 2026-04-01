

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuideTargetActor.generated.h"

class AWall_OceanVillageManager;

UCLASS()
class FUTUREOCEAN_API AGuideTargetActor : public AActor
{
	GENERATED_BODY()
public:
	inline void SetMyNum(int _myNum) { myNum = _myNum; }
	inline int GetMyNum() { return myNum; }

	void CustomInit(AWall_OceanVillageManager* _manager);

private:
	int myNum;
	AWall_OceanVillageManager* wallManager;
};
