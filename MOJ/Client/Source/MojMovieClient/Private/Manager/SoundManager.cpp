// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/SoundManager.h"
#include "Manager/GameManager.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"

// Sets default values
ASoundManager::ASoundManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASoundManager::SetBGMVolume(float volume)
{
	Audio_BGM->VolumeMultiplier = volume;
}

void ASoundManager::SetBGM(USoundBase* sound)
{
	if (Audio_BGM->IsPlaying())
		Audio_BGM->Stop();

	Audio_BGM->SetSound(sound);
}

void ASoundManager::PlayBGM(bool bPlay)
{
	if (bPlay)
		Audio_BGM->Play();
	else
		Audio_BGM->Stop();
}

void ASoundManager::SetNarration(USoundBase* sound)
{
	if (Audio_Narr == nullptr)
		return;

	if (Audio_Narr->IsPlaying())
		Audio_Narr->Stop();

	Audio_Narr->SetSound(sound);
}

void ASoundManager::PlayNarration(bool bPlay)
{
	if (bPlay)
		Audio_Narr->Play();
	else
		Audio_Narr->Stop();
}

float ASoundManager::NarrationFadeOut(float FadeDuration, float FadeVolumeLevel)
{
	Audio_BGM->SetVolumeMultiplier(1.0f);
	Audio_Narr->FadeOut(FadeDuration, FadeVolumeLevel);

	return FadeDuration;
}

float ASoundManager::PlayNarrationByID(FString _SoundID, ENationType _type)
{
	Audio_BGM->SetVolumeMultiplier(0.1f);
	SetNarration(GetGameManager()->GetSound(_SoundID, _type));
	PlayNarration(true);
	return Audio_Narr->Sound->GetDuration();;
}

void ASoundManager::SetNarrationPaused(bool IsPlay)
{
	Audio_Narr->SetPaused(IsPlay);
}
