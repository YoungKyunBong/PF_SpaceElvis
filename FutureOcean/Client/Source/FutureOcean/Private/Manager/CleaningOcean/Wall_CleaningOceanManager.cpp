
#include "Manager/CleaningOcean/Wall_CleaningOceanManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/CleaningOcean/WhaleCharacter.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"

AWall_CleaningOceanManager::AWall_CleaningOceanManager()
{
	PrimaryActorTick.bCanEverTick = false;
	envFloatValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvFloatValueTimeLine"));
	envColorValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvColorValueTimeLine"));
}

void AWall_CleaningOceanManager::C_Init()
{
	Super::C_Init();

	whaleActor->Init(this);

	GetGameManager()->RecvCleaningLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvWallSpawnWhale.AddUFunction(this, FName("RecvWallSpawnWhale"));
	GetGameManager()->RecvChangeWhaleDirection.AddUFunction(this, FName("RecvChangeWhaleDirection"));
	GetGameManager()->RecvPlayWhaleSound.AddUFunction(this, FName("RecvPlayWhaleSound"));
	GetGameManager()->RecvFloorSpawnWhale.AddUFunction(this, FName("RecvFloorSpawnWhale"));
	//GetGameManager()->RecvCleaningOceanEnd.AddUFunction(this, FName("RecvLevelEnd"));

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->Send_CleaningLevelLoadingEnd();

	/* Test Debug Code */
	//if (!IsTest)
	//	return;

	//whaleActor->SetSideType(SIDE_TYPE::LeftSide);
	//whaleActor->IsWhaleMove(true);	
	/* Test Debug Code End */
}

void AWall_CleaningOceanManager::RecvLevelLoadingEnd(bool isStart)
{
	//whaleActor->IsWhaleMove(isStart);

	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);

	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);

	whaleActor->IsWhaleMove(false);

	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CleaningOceanManager::TimeOutEvent, Playtime, false);

	//서버 없을 때에 좌우 직접 선택
	if(GetGameManager()->GetIsLocalGame())
		RecvWallSpawnWhale(noneServerSideType);
}

void AWall_CleaningOceanManager::RecvWallSpawnWhale(SIDE_TYPE _type)
{
	whaleActor->SetSideType(_type);
}


//
//void AWall_CleaningOceanManager::RecvLevelEnd()
//{
//	GetGameMode()->Call_LevelEnd(0);
//}

// <<--------------------------------------------------------------------- 요 함수는 고래가 좌, 우 이동시에 콜하면 됨
void AWall_CleaningOceanManager::RecvChangeWhaleDirection()
{
	// 고래 함수 콜
}
inline void AWall_CleaningOceanManager::RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE _type) { WorldSetting(_type); }

void AWall_CleaningOceanManager::RecvFloorSpawnWhale(SIDE_TYPE _type, bool _isSuccess)
{
	ChangeEnvironment();

	if(_isSuccess)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroSucessType);
	else
		GetGameManager()->Send_PlayTimeOutEvent();
}
void AWall_CleaningOceanManager::TestCallPlayWhaleSound()
{
	GetGameManager()->Send_PlayWhaleSound();
}
// >>---------------------------------------------------------------------x수는 정면으로 이동 완료 후 콜하면 됨 (도착과 동시에 양 화면에서 자동 실행해도 되지만 혹시 모르는 동기화를 위해서 서버로 전달)
void AWall_CleaningOceanManager::SendChangeWhaleDirection()
{
	if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
		GetGameManager()->Send_ChangeWhaleDirection();
}
// >>---------------------------------------------------------------------

// <<--------------------------------------------------------------------- 요 함수는 좌, 우 이동 완료 후 콜하면 됨
void AWall_CleaningOceanManager::SendWallSpawnWhaleEnd()
{
	GetGameManager()->Send_WallSpawnWhaleEnd();
	whaleActor->IsWhaleMove(false);
	IsWhaleMoveEnd = true;
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CleaningOceanManager::TimeOutEvent, Playtime, false);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
}
// >>---------------------------------------------------------------------

void AWall_CleaningOceanManager::SetCmsIsStart(bool isStart)
{
	if(!IsWhaleMoveEnd && IsPlaySequenceEnd)
		whaleActor->IsWhaleMove(isStart);

	//if (isStart && !IsWhaleMoveEnd)
	//	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType0);

	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
	//if (isStart)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	//	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType0);
	//}
}

void AWall_CleaningOceanManager::TimeOutEvent()
{
	//Super::TimeOutEvent();

	GetGameManager()->Send_FloorSpawnWhale();
}

void AWall_CleaningOceanManager::Call_Intro_SQ_End()
{
	whaleActor->IsWhaleMove(true);
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType0);
	IsPlaySequenceEnd = true;
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CleaningOceanManager::TimeOutEvent, Playtime, false);
}

void AWall_CleaningOceanManager::Call_DefaultLevelEnd()
{
	if(!checkTestGame)
		GetGameManager()->Send_CleaningOceanEnd();
}

void AWall_CleaningOceanManager::SetTimeLine_EnvFloatValue()
{
	float playrate = 1.f / envDefaultTimeRate;
	envFloatValue_TimeLine->SetLooping(false);

	envFloatValue_TimeLine->AddInterpFloat(envFloatValue_Curve, envFloatValue_TimelineCallback);
	envFloatValue_TimeLine->SetTimelineFinishedFunc(envFloatValue_TimelineFinishedCallback);
	envFloatValue_TimeLine->SetPlayRate(playrate);

	envFloatValue_TimeLine->PlayFromStart();
}

void AWall_CleaningOceanManager::SetTimeLine_EnvColorValue()
{
	//float playrate = 1.f / envDefaultTimeRate;
	//envColorValue_TimeLine->SetLooping(false);

	//envColorValue_TimeLine->AddInterpLinearColor(envColorValue_Curve, envColorValue_TimelineCallback);
	//envColorValue_TimeLine->SetTimelineFinishedFunc(envColorValue_TimelineFinishedCallback);
	//envColorValue_TimeLine->SetPlayRate(playrate);

	//envColorValue_TimeLine->PlayFromStart();
}
