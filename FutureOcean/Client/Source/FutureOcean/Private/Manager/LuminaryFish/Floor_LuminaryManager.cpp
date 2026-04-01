
#include "Manager/LuminaryFish/Floor_LuminaryManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

void AFloor_LuminaryManager::C_Init()
{
	Super::C_Init();

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvLuminaryFishLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvPlayEffectSound.AddUFunction(this, FName("RecvPlayEffectSound"));
	GetGameManager()->RecvLumiFishEnd.AddUFunction(this, FName("RecvLumiFishEnd"));

	GetGameManager()->Send_LuminaryFishLevelLoadingEnd();

	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);
}

void AFloor_LuminaryManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
}

void AFloor_LuminaryManager::RecvPlayEffectSound(EFFECT_SOUND_TYPE _type)
{
	GetGameMode()->Call_WorldPlayEffectSounds(_type);
}

void AFloor_LuminaryManager::RecvLumiFishEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvLumiFishEnd"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AFloor_LuminaryManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}
