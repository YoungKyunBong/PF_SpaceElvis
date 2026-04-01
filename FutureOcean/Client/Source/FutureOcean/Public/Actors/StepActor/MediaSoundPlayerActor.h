

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "MediaSoundPlayerActor.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AMediaSoundPlayerActor : public AStepActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CustomInit();

	UFUNCTION(BlueprintCallable)
	void MediaSoundPlay();

	UFUNCTION(BlueprintCallable)
	void CheckSkip();

	UPROPERTY(BlueprintReadWrite)
	UMediaSoundComponent* C_MediaSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMediaSource* MediaSource;

	UPROPERTY(EditAnywhere)
	float EndDelayTime = 0.5f;

	virtual void CMS_Start() override;
	virtual void CMS_Stop() override;
private:
	FTimerHandle Handle;

	void MediaSoundPlayCheck();
};
