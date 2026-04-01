#include "Manager/KelpForest/Wall_KelpForestManager.h"
#include "Actors/StepActor/KelpForest/PollutedCoralActor.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "kismet/GameplayStatics.h"


void AWall_KelpForestManager::C_Init()
{
	Super::C_Init();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, APollutedCoralActor::StaticClass(), OutActors);

	for (auto iter : OutActors)
	{
		auto tempActor = Cast<APollutedCoralActor>(iter);
		tempActor->Init(this);
		PollutedCoralActors.Add(Cast<APollutedCoralActor>(tempActor));
	}
	
	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvKelpLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvOilOverlap.AddUFunction(this, FName("ChangeOpValue"));
	GetGameManager()->RecvOilCount.AddUFunction(this, FName("CleaningOilCount"));
	GetGameManager()->RecvKelpLevelPlaySequence.AddUFunction(this, FName("RecvPlaySequence"));
	GetGameManager()->Send_KelpLevelLoadingEnd();
}

void AWall_KelpForestManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_KelpForestManager::TimeOutEvent, Playtime, false);
}

void AWall_KelpForestManager::CleaningOilCount(int32 _Count)
{
	OilCount = _Count;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OilCount OK"));
}

void AWall_KelpForestManager::RecvPlaySequence()
{
	//´ÙÀ½ ½ºÅÜ
	//GetGameMode()->Call_StepManager_SkipStep(0);
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvPlaySequence"));
	isPlaySequence = true;
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::InteractionType);
}

void AWall_KelpForestManager::ChangeOpValue(int32 cnt)
{
	//OilCount = cnt;
	for (APollutedCoralActor* PollutedCoralActor : PollutedCoralActors)
	{
		PollutedCoralActor->ChangeOpValue(OilCount);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap OK"));
	}
}

void AWall_KelpForestManager::CallOilLevelEnd()
{
	GetGameManager()->Send_OilEnd();
}

void AWall_KelpForestManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

void AWall_KelpForestManager::RecvPlayTimeOutEvent()
{
	RecvPlaySequence();

	isSuccess = false;
}

void AWall_KelpForestManager::Call_Intro_SQ_End()
{
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_KelpForestManager::TimeOutEvent, Playtime, false);
}

void AWall_KelpForestManager::Call_Interaction_SQ_End()
{
	if (isSuccess)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroSucessType);
	else
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void AWall_KelpForestManager::Call_DefaultLevelEnd()
{
	if (!checkTestGame)
		CallOilLevelEnd();
}
