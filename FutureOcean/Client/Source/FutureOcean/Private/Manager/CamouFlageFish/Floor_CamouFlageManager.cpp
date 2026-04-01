
#include "Manager/CamouFlageFish/Floor_CamouFlageManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

void AFloor_CamouFlageManager::C_Init()
{
	Super::C_Init();

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvCamouFlageFishLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvPlayEffectSound.AddUFunction(this, FName("RecvPlayEffectSound"));
	GetGameManager()->RecvCamouFishEnd.AddUFunction(this, FName("RecvCamouFishEnd"));

	GetGameManager()->Send_CamouFlageFishLevelLoadingEnd();

	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);
}

void AFloor_CamouFlageManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
}

void AFloor_CamouFlageManager::RecvPlayEffectSound(EFFECT_SOUND_TYPE _type)
{
	GetGameMode()->Call_WorldPlayEffectSounds(_type);
}

void AFloor_CamouFlageManager::RecvCamouFishEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvCamouFishEnd"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AFloor_CamouFlageManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}
