// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "SoundManager.generated.h"

class USoundBase;
class UAudioComponent;
class UGameManager;

UCLASS()
class HANYANG2_CHANGDEOK_API ASoundManager : public ADefaultManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_Narr = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_BGM = nullptr;

	float NarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f);
	float PlayNarrationByID(FString _SoundID);
	void SetNarrationPaused(bool IsPlay);

private:
	void PlayBGM(bool bPlay);
	void PlayNarration(bool bPlay);
	void SetBGMVolume(float volume);
	void SetBGM(USoundBase* sound);
	void SetNarration(USoundBase* sound);
};
  