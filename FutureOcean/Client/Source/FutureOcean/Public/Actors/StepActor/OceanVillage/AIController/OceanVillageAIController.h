#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OceanVillageAIController.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AOceanVillageAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
