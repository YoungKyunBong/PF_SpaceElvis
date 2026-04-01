#include "Manager/KelpForest/Floor_KelpForestManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/KelpForest/CleaningOilActor.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "kismet/GameplayStatics.h"

AFloor_KelpForestManager::AFloor_KelpForestManager()
{
	PrimaryActorTick.bCanEverTick = false;
	envFloatValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvFloatValueTimeLine"));
	envColorValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvColorValueTimeLine"));
}

void AFloor_KelpForestManager::C_Init()
{
	Super::C_Init();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ACleaningOilActor::StaticClass(), OutActors);

	for (auto iter : OutActors)
	{
		auto tempActor = Cast<ACleaningOilActor>(iter);
		tempActor->Init(this);
		oilActors.Add(Cast<ACleaningOilActor>(tempActor));
	}
	OilCount = oilActors.Num();
	oilDisableCount = 0;

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvKelpLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvKelpLevelPlaySequence.AddUFunction(this, FName("RecvPlaySequence"));
	GetGameManager()->RecvPlayTimeOutEvent.AddUFunction(this, FName("RecvPlayTimeOutEvent"));
	GetGameManager()->Send_KelpLevelLoadingEnd();

	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Dirty);
}

void AFloor_KelpForestManager::SendOilOverlapToServer()
{	
	//GetGameManager()->Send_OilCount(OilCount);
	//GetGameManager()->Send_OilOverlap(OilCount);
}

void AFloor_KelpForestManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);

	//SetCmsIsStart(isStart);
	GetGameManager()->Send_OilCount(OilCount);
}

void AFloor_KelpForestManager::RecvPlaySequence()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvPlaySequence"));
	ChangeEnvironment();
	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::InteractionType);
	//PlaySequenceActor->PlaySequence(Lv_Sq_Type::InteractionType);
}

void AFloor_KelpForestManager::CheckDisableOilCount()
{
	oilDisableCount++;
	if (oilDisableCount == OilCount)
	{
		GetGameManager()->Send_KelpLevelPlaySequence();
		//바닥면 월드 설정 변경 코드인데 PlaySequence로 같이 연결하는 쪽이 깔끔할 듯 함
		//GetGameManager()->Send_OceanCleanChange();
	}
}

void AFloor_KelpForestManager::Call_Interaction_SQ_End()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Call_Interaction_SQ_End"));
	if (isSuccess)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroSucessType);
	else
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AFloor_KelpForestManager::RecvPlayTimeOutEvent()
{
	RecvPlaySequence();

	isSuccess = false;

	for (int i = 0; i < oilActors.Num(); i++)
	{
		oilActors[i]->SetOverlap(false);
	}
}

void AFloor_KelpForestManager::SetTimeLine_EnvFloatValue()
{
	float playrate = 1.f / envDefaultTimeRate;
	envFloatValue_TimeLine->SetLooping(false);

	envFloatValue_TimeLine->AddInterpFloat(envFloatValue_Curve, envFloatValue_TimelineCallback);
	envFloatValue_TimeLine->SetTimelineFinishedFunc(envFloatValue_TimelineFinishedCallback);
	envFloatValue_TimeLine->SetPlayRate(playrate);

	envFloatValue_TimeLine->PlayFromStart();
}

void AFloor_KelpForestManager::SetTimeLine_EnvColorValue()
{
}

void AFloor_KelpForestManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

//void AFloor_KelpForestManager::SetCmsIsStart(bool isStart)
//{
//	for (auto iter : oilActors)
//	{
//		iter->SetCollisionInteractionMesh(isStart ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
//	}
//}
