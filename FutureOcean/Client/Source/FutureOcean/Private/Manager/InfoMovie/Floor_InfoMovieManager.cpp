
#include "Manager/InfoMovie/Floor_InfoMovieManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Components/AudioComponent.h"
#include "actors/StepActor/MoviePlayerActor.h"

void AFloor_InfoMovieManager::C_Init()
{
	Super::C_Init();

	MoviePlayerActor->CustomInit(this);

	//GetGameMode()->Call_FadeImageOp(1.0f);

	GetGameManager()->RecvMovieLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));

	GetGameManager()->Send_MovieLevelLoadingEnd();

	//Audio_BGM->Play();
	//GetWorldTimerManager().SetTimer(MiddleTimeHandle, this, &AMoviePlayerActor::ChangeScriptMiddle, Middle_ChangeScriptTime, false);
	//GetWorldTimerManager().SetTimer(EndTimeHandle, this, &AMoviePlayerActor::ChangeScriptEnd, End_ChangeScriptTime, false);
}

void AFloor_InfoMovieManager::RecvLevelLoadingEnd(bool isStart)
{
	SetCmsIsStart(isStart);

	//if (GetGameManager()->GetNodeType() == ClientNodeType::Node1)
	//{
	//	Audio_BGM->BeginPlay();
	//	GetWorldTimerManager().SetTimer(MainHandle, this, &AFloor_InfoMovieManager::RecvInfoMovieLevelEnd, Audio_BGM->Sound->GetDuration() + EndDelayTime, false);
	//}
}

void AFloor_InfoMovieManager::SetCmsIsStart(bool isStart)
{
	//isStart ? MoviePlayerActor->CMS_Start() : MoviePlayerActor->CMS_Stop();
	CustomPlaySound(isStart);
	//if (GetGameManager()->GetNodeType() == ClientNodeType::Node1)
	//	isStart ? Audio_BGM->Play() : Audio_BGM->Stop();
}

void AFloor_InfoMovieManager::RecvLevelEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep1"));
	Audio_BGM->Stop();
	GetGameMode()->Call_StepManager_SkipStep(0);
	//MoviePlayerActor->CheckSkip();
}

void AFloor_InfoMovieManager::RecvInfoMovieLevelEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep2"));
	Audio_BGM->Stop();
	GetGameMode()->Call_StepManager_SkipStep(0);
}
