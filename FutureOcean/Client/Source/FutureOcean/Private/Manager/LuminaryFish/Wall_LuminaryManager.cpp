


#include "Manager/LuminaryFish/Wall_LuminaryManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

void AWall_LuminaryManager::C_Init()
{
	Super::C_Init();

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvLuminaryFishLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvLumiFishEnd.AddUFunction(this, FName("RecvLumiFishEnd"));

	GetGameManager()->Send_LuminaryFishLevelLoadingEnd();
}

void AWall_LuminaryManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
	//GetGameManager()->Send_LuminaryFishCount(fishCount);
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_LuminaryManager::TimeOutEvent, Playtime, false);
}

void AWall_LuminaryManager::RecvLumiFishEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvLumiFishEnd"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AWall_LuminaryManager::SendLumiFishHit()
{
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType0);
}

void AWall_LuminaryManager::SendLumiFishFind()
{
	findFishCount++;
	if (findFishCount == fishCount)
		GetGameManager()->Send_LumiFishFind();

	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType1);
}

void AWall_LuminaryManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

void AWall_LuminaryManager::Call_Intro_SQ_End()
{
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_LuminaryManager::TimeOutEvent, Playtime, false);
}

void AWall_LuminaryManager::Call_DefaultLevelEnd()
{
	if (!checkTestGame && GetGameManager()->GetNodeType() == ClientNodeType::Node0)
		GetGameManager()->Send_CmsControllerSkip();
}

void AWall_LuminaryManager::TempLevelEnd()
{
	GetGameManager()->Send_LumiFishFind();
}
