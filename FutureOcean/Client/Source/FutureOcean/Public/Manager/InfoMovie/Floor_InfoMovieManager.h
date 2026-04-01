

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Floor_InfoMovieManager.generated.h"


class UAudioComponent;
/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AFloor_InfoMovieManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* Audio_BGM = nullptr;

protected:
	UPROPERTY(EditAnywhere)
	class AMoviePlayerActor* MoviePlayerActor;

	UPROPERTY(EditAnywhere)
	float EndDelayTime = 2.0f;

public:
	virtual	void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	virtual void SetCmsIsStart(bool isStart) override;

	virtual void RecvLevelEnd() override;

	virtual void RecvInfoMovieLevelEnd() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CustomPlaySound(bool isPlay);
	UFUNCTION(BlueprintCallable)
	void CustomPlaySound_Implementation(bool isPlay) {}

private:
	FTimerHandle MainHandle;
	FTimerHandle MiddleTimeHandle;
	FTimerHandle EndTimeHandle;
};
