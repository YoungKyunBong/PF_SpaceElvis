
#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Manager/InteractionWidgetActor.h"

void ADefaultGameMode::SetStepManagers(TArray<AStepManager*> _StepManagers)
{
	for (int i = 0; i < _StepManagers.Num(); i++)
		InWorldAllManager.Add(_StepManagers[i]->StepManagerNumber, _StepManagers[i]);
}

void ADefaultGameMode::SetSoundManager(ASoundManager* _soundManager)
{
	SoundManager = _soundManager;
}

AStepManager* ADefaultGameMode::GetCurrentStepManager(int StepManagerNum)
{
	if (InWorldAllManager.Contains(StepManagerNum))
		return InWorldAllManager[StepManagerNum];

	return nullptr;
}

void ADefaultGameMode::Call_AnimFadeWidget(bool IsFadeIn)
{
	WidgetActor->Call_AnimFadeWidget(IsFadeIn);
}

//void ADefaultGameMode::Call_FadeImageOp(float _op)
//{
//	WidgetActor->Call_FadeImageOp(_op);
//}
//
void ADefaultGameMode::Call_WidgetSwitcherIndex(int _index)
{
	WidgetActor->Call_WidgetSwitcherIndex(_index);
}

void ADefaultGameMode::Call_LevelEnd(int StepManagerNum)
{
	GetCurrentStepManager(StepManagerNum)->SetGamePlay(false);
}

void ADefaultGameMode::Call_StepManager_SkipStep(int StepManagerNum)
{
	GetCurrentStepManager(StepManagerNum)->SkipStep();
}

void ADefaultGameMode::Call_StepManager_CmsIsStart(int StepManagerNum, bool _IsStart)
{
	GetCurrentStepManager(StepManagerNum)->Call_CmsIsStart(_IsStart);
}

void ADefaultGameMode::Call_SetCustomSound(uint8 _type, USoundBase* _sound)
{
	SoundManager->SetCustomSound((SOUND_TYPE)_type, _sound);
}

void ADefaultGameMode::Call_PlayCustomSound(uint8 _soundType, uint8 _volumeType)
{
	switch (_soundType)
	{
	case (uint8)SOUND_TYPE::Narr:
		break;
	case (uint8)SOUND_TYPE::BGM:
		break;
	case (uint8)SOUND_TYPE::Effect:
		SoundManager->PlayEffect((WHALE_SOUND_DISTANCE_TYPE)_volumeType);
		break;
	default:
		break;
	}
}

void ADefaultGameMode::Call_WorldPlayEffectSounds(EFFECT_SOUND_TYPE _type)
{
	SoundManager->WorldPlayEffectSounds(_type);
}
