

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "Runtime/MediaAssets/Public/MediaSoundComponent.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "MoviePlayerActor.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AMoviePlayerActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void Init(AStepManager* Manager) override;
	
	void CustomInit(class ADefaultManager* _manager);

	UFUNCTION(BlueprintCallable)
	void PlayMovie();

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

	UPROPERTY(EditAnywhere)
	float First_ChangeScriptTime;	
	
	UPROPERTY(EditAnywhere)
	float Middle_ChangeScriptTime;

	UPROPERTY(EditAnywhere)
	float End_ChangeScriptTime;

	UPROPERTY(EditAnywhere)
	bool IsWall;

	virtual void CMS_Start() override;
	virtual void CMS_Stop() override;

private:
	FTimerHandle MainHandle;
	FTimerHandle StartTimeHandle;
	FTimerHandle MiddleTimeHandle;
	FTimerHandle EndTimeHandle;

	void MoviePlayCheck();
	void ChangeScriptFirst();
	void ChangeScriptMiddle();
	void ChangeScriptEnd();

	bool isFirstPlay;

	class AWall_InfoMovieManager* wallManager;
};
