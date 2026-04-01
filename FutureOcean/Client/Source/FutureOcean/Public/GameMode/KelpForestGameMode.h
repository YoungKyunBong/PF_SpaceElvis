

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KelpForestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AKelpForestGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	void init();
};
