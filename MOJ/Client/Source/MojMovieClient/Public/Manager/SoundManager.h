// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "SoundManager.generated.h"

class USoundBase;
class UAudioComponent;
class UGameManager;

UCLASS()
class MOJMOVIECLIENT_API ASoundManager : public ADefaultManager
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASoundManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_Narr = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_BGM = nullptr;

	virtual float NarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f) override;
	virtual float PlayNarrationByID(FString _SoundID, ENationType _type) override;
	virtual void SetNarrationPaused(bool IsPlay) override;

private:
	void PlayBGM(bool bPlay);
	void PlayNarration(bool bPlay);
	void SetBGMVolume(float volume);
	void SetBGM(USoundBase* sound);
	void SetNarration(USoundBase* sound);
};
