

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "../Protocols.h"
#include "SoundManager.generated.h"

class USoundBase;
class UAudioComponent;
class UGameManager;

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API ASoundManager : public ADefaultManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_Narr = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_BGM = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio_Effect = nullptr;

	UFUNCTION(BlueprintNativeEvent)
	void WorldPlayEffectSounds(EFFECT_SOUND_TYPE _type);
	UFUNCTION(BlueprintCallable)
	virtual void WorldPlayEffectSounds_Implementation(EFFECT_SOUND_TYPE _type) {}

	float NarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f);
	float PlayNarrationByID(FString _SoundID);
	void SetNarrationPaused(bool IsPlay);

	void SetCustomSound(SOUND_TYPE _type, USoundBase* sound);
	void PlayEffect(WHALE_SOUND_DISTANCE_TYPE _type);
private:
	void PlayBGM(bool bPlay);
	void PlayNarration(bool bPlay);
	void SetBGMVolume(float volume);
	void SetNarration(USoundBase* sound);
};
