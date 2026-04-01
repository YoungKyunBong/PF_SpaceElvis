#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoralForestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API ACoralForestGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void init();
	
};
