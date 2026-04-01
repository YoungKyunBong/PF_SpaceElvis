


#include "Manager/CoralForest/Floor_CoralForestManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/CoralForest/FlagCoralActor.h"

#include "Actors/StepActor/CoralForest/InteractionActor.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Kismet/GameplayStatics.h"

AFloor_CoralForestManager::AFloor_CoralForestManager()
{
	PrimaryActorTick.bCanEverTick = false;
	envFloatValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvFloatValueTimeLine"));
	envColorValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvColorValueTimeLine"));
}

void AFloor_CoralForestManager::C_Init()
{
	Super::C_Init();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFlagCoralActor::StaticClass(), OutActors);

	for (auto iter : OutActors)
	{
		auto tempActor = Cast<AFlagCoralActor>(iter);
		FlagCoralActors.Add(Cast<AFlagCoralActor>(tempActor));
	}

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvCoralLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvCoralOverlap.AddUFunction(this, FName("RecvCoralOverlap"));
	GetGameManager()->RecvCoralWhiteSwitch.AddUFunction(this, FName("RecvCoralWhiteSwitch"));
	//GetGameManager()->RecvCoralEnd.AddUFunction(this, FName("RecvLevelEnd"));

	GetGameManager()->Send_CoralLevelLoadingEnd();

	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Dirty);

	//Å×½ºÆ®
	//ChangeEnvironment();
}

void AFloor_CoralForestManager::SendOverlapToServer(CORAL_TYPE _Type)
{
	//GetGameManager()->Send_CoralOverlap(_Type);
}

void AFloor_CoralForestManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);

	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);

	//SetCmsIsStart(isStart);
}

void AFloor_CoralForestManager::RecvCoralWhiteSwitch()
{
	for (auto FlagCoralActor : FlagCoralActors)
	{
		FlagCoralActor->WhiteSwitch();
	}
}

void AFloor_CoralForestManager::RecvCoralOverlap(CORAL_TYPE _Type)
{
	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::Effect, CoralOverlapSound);
}

//void AFloor_CoralForestManager::RecvLevelEnd()
//{
//	//Super::RecvLevelEnd();
//
//	PlaySequenceActor->ClearSequence();
//	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
//	ChangeSkipBinding();
//}

void AFloor_CoralForestManager::RecvCoralLevelEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	GetGameMode()->Call_LevelEnd(0);
}

void AFloor_CoralForestManager::SetCmsIsStart(bool isStart)
{
	//for (auto iter : InteractionActors)
	//{
	//	iter->SetCollisionInteractionMesh(isStart ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	//}
	
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

void AFloor_CoralForestManager::RecvPlayTimeOutEvent()
{
	//Super::RecvPlayTimeOutEvent();

	ChangeEnvironment();

	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AFloor_CoralForestManager::TimeOutDelay, Finishtime, false);
}

void AFloor_CoralForestManager::RecvOceanCleanChange()
{
	Super::RecvOceanCleanChange();

	//GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);

	ChangeEnvironment();
	//ChangeSkipBinding();
}

//void AFloor_CoralForestManager::SetTimeLine_EnvFloatValue()
//{
//	float playrate = 1.f / envDefaultTimeRate;
//	envFloatValue_TimeLine->SetLooping(false);
//
//	envFloatValue_TimeLine->AddInterpFloat(envFloatValue_Curve, envFloatValue_TimelineCallback);
//	envFloatValue_TimeLine->SetTimelineFinishedFunc(envFloatValue_TimelineFinishedCallback);
//	envFloatValue_TimeLine->SetPlayRate(playrate);
//
//	envFloatValue_TimeLine->PlayFromStart();
//}

void AFloor_CoralForestManager::SetTimeLine_EnvColorValue()
{
}

void AFloor_CoralForestManager::ChangeSkipBinding()
{
	GetGameManager()->RecvCmsControllerSkip.Clear();
	GetGameManager()->RecvCmsControllerSkip.AddUFunction(this, FName("RecvCoralLevelEnd"));
}

void AFloor_CoralForestManager::TimeOutDelay()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TimeOutDelay"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

//void AFloor_CoralForestManager::RecvLevelEnd()
//{
//	GetGameMode()->Call_LevelEnd(0);
//}
