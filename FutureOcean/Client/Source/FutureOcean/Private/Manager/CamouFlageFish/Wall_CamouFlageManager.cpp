


#include "Manager/CamouFlageFish/Wall_CamouFlageManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

void AWall_CamouFlageManager::C_Init()
{
	Super::C_Init();

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvCamouFlageFishLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvCamouFishEnd.AddUFunction(this, FName("RecvCamouFishEnd"));

	GetGameManager()->Send_CamouFlageFishLevelLoadingEnd();
}

void AWall_CamouFlageManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
	//GetGameManager()->Send_CamouFlageFishCount(fishCount);
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CamouFlageManager::TimeOutEvent, Playtime, false);
}

void AWall_CamouFlageManager::RecvCamouFishEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvCamouFishEnd"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AWall_CamouFlageManager::SendCamouFishHit()
{
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType0);
}

void AWall_CamouFlageManager::SendCamouFishFind()
{
	findFishCount++;
	if(findFishCount == fishCount)
		GetGameManager()->Send_CamouFishFind();
	
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType1);
}

void AWall_CamouFlageManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

void AWall_CamouFlageManager::Call_Intro_SQ_End()
{
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CamouFlageManager::TimeOutEvent, Playtime, false);
}

void AWall_CamouFlageManager::Call_DefaultLevelEnd()
{
	if (!checkTestGame && GetGameManager()->GetNodeType() == ClientNodeType::Node0)
		GetGameManager()->Send_CmsControllerSkip();
}
