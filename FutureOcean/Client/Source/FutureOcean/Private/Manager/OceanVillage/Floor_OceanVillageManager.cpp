


#include "Manager/OceanVillage/Floor_OceanVillageManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

void AFloor_OceanVillageManager::C_Init()
{
	Super::C_Init();

	GetGameManager()->RecvOceanVillageLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvPlayEffectSound.AddUFunction(this, FName("RecvPlayEffectSound"));

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->Send_OceanVillageLevelLoadingEnd();

	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);
}

void AFloor_OceanVillageManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
}

void AFloor_OceanVillageManager::RecvPlayEffectSound(EFFECT_SOUND_TYPE _type)
{
	GetGameMode()->Call_WorldPlayEffectSounds(_type);
}

void AFloor_OceanVillageManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}
