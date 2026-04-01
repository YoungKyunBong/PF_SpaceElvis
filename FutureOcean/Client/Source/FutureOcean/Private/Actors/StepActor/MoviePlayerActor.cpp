
#include "Actors/StepActor/MoviePlayerActor.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "Manager/StepManager.h"
#include "Manager/InfoMovie/Wall_InfoMovieManager.h"
#include "Kismet/KismetSystemLibrary.h"

void AMoviePlayerActor::Init(AStepManager* Manager)
{
	CustomInit(Manager);
}

void AMoviePlayerActor::CustomInit(class ADefaultManager* _manager)
{
	if (IsWall)
		wallManager = Cast<AWall_InfoMovieManager>(_manager);

	MediaPlayer->OpenSource(MediaSource);

	isFirstPlay = true;

	if (!IsWall)
	{
		C_MediaSound->SetMediaPlayer(MediaPlayer);
		C_MediaSound->Activate(true);
	}
}

void AMoviePlayerActor::PlayMovie()
{
	//stepManager->Call_WidgetSwitcherIndex(2);

	isFirstPlay = false;

	//MediaPlayer->Rewind();

	//MediaPlayer->Play();

	if (IsWall)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SetTimer"));
		//GetWorldTimerManager().SetTimer(MainHandle, this, &AMoviePlayerActor::MoviePlayCheck, MediaPlayer->GetDuration().GetTotalSeconds() + EndDelayTime, false);
		//GetWorldTimerManager().SetTimer(StartTimeHandle, this, &AMoviePlayerActor::ChangeScriptFirst, First_ChangeScriptTime, false);
		GetWorldTimerManager().SetTimer(MiddleTimeHandle, this, &AMoviePlayerActor::ChangeScriptMiddle, Middle_ChangeScriptTime, false);
		GetWorldTimerManager().SetTimer(EndTimeHandle, this, &AMoviePlayerActor::ChangeScriptEnd, End_ChangeScriptTime, false);
	}
}

void AMoviePlayerActor::CheckSkip()
{
	CMS_Stop();

	if (IsWall)
		wallManager->SendInfoMovieLevelEnd();

}

void AMoviePlayerActor::CMS_Start()
{
	if(isFirstPlay)
		PlayMovie();
	else
	{
		//MediaPlayer->Play();
		//GetWorldTimerManager().UnPauseTimer(MainHandle);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Start"));
		GetWorldTimerManager().UnPauseTimer(StartTimeHandle);
		GetWorldTimerManager().UnPauseTimer(MiddleTimeHandle);
		GetWorldTimerManager().UnPauseTimer(EndTimeHandle);
	}
}

void AMoviePlayerActor::CMS_Stop()
{
	//MediaPlayer->Pause();
	//GetWorldTimerManager().PauseTimer(MainHandle);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Stop"));
	GetWorldTimerManager().PauseTimer(StartTimeHandle);
	GetWorldTimerManager().PauseTimer(MiddleTimeHandle);
	GetWorldTimerManager().PauseTimer(EndTimeHandle);
}

void AMoviePlayerActor::MoviePlayCheck()
{
	//GetWorldTimerManager().PauseTimer(MainHandle);
	//GetWorldTimerManager().PauseTimer(MiddleTimeHandle);
	//GetWorldTimerManager().PauseTimer(EndTimeHandle);
	//if (IsWall)
	//	wallManager->SendInfoMovieLevelEnd();
}

void AMoviePlayerActor::ChangeScriptFirst()
{
	wallManager->SendChangeScript(PROTOCOLSUB_CMS::GuideScript_InfoMovie_Start);
}

void AMoviePlayerActor::ChangeScriptMiddle()
{
	wallManager->SendChangeScript(PROTOCOLSUB_CMS::GuideScript_InfoMovie_Middle);
}

void AMoviePlayerActor::ChangeScriptEnd()
{
	wallManager->SendChangeScript(PROTOCOLSUB_CMS::GuideScript_InfoMovie_End);
}
