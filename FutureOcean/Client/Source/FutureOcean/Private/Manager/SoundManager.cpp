
#include "Manager/SoundManager.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"

float ASoundManager::NarrationFadeOut(float FadeDuration, float FadeVolumeLevel)
{
	return 0.0f;
}

float ASoundManager::PlayNarrationByID(FString _SoundID)
{
	return 0.0f;
}

void ASoundManager::SetNarrationPaused(bool IsPlay)
{
}

void ASoundManager::SetCustomSound(SOUND_TYPE _type, USoundBase* sound)
{
	switch (_type)
	{
	case SOUND_TYPE::Narr:
		break;
	case SOUND_TYPE::BGM:
		Audio_BGM->SetSound(sound);
		PlayBGM(true);
		break;
	case SOUND_TYPE::Effect:
		//Audio_Effect->Stop();
		Audio_Effect->SetSound(sound);
		PlayEffect(WHALE_SOUND_DISTANCE_TYPE::Default);
		break;
	default:
		break;
	}
}

void ASoundManager::PlayEffect(WHALE_SOUND_DISTANCE_TYPE _type)
{
	float tempVolume = 0.0f;
	switch (_type)
	{
	case WHALE_SOUND_DISTANCE_TYPE::LOW:
		tempVolume = 0.33f;
		break;
	case WHALE_SOUND_DISTANCE_TYPE::MIDDLE:
		tempVolume = 0.66f;
		break;
	case WHALE_SOUND_DISTANCE_TYPE::HIGH:
		tempVolume = 1.0f;
		break;
	case WHALE_SOUND_DISTANCE_TYPE::Default:
		tempVolume = 1.0f;
		break;
	default:
		break;
	}
	Audio_Effect->SetVolumeMultiplier(tempVolume);
	Audio_Effect->Play();
}

void ASoundManager::PlayBGM(bool bPlay)
{
	Audio_BGM->Play();
}

void ASoundManager::PlayNarration(bool bPlay)
{
}

void ASoundManager::SetBGMVolume(float volume)
{
}

void ASoundManager::SetNarration(USoundBase* sound)
{
}
