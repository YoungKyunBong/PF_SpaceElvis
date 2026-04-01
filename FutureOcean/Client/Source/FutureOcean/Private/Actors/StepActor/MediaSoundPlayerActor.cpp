
#include "Actors/StepActor/MediaSoundPlayerActor.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "Manager/StepManager.h"
#include "Kismet/KismetSystemLibrary.h"

void AMediaSoundPlayerActor::CustomInit()
{
	MediaPlayer->OpenSource(MediaSource);

	C_MediaSound->SetMediaPlayer(MediaPlayer);
}

void AMediaSoundPlayerActor::MediaSoundPlay()
{
	//stepManager->Call_WidgetSwitcherIndex(2);

	//C_MediaSound->Activate(true);

	MediaPlayer->Rewind();

	MediaPlayer->Play();

	GetWorldTimerManager().SetTimer(Handle, this, &AMediaSoundPlayerActor::MediaSoundPlayCheck, MediaPlayer->GetDuration().GetTotalSeconds() + EndDelayTime, false);
}

void AMediaSoundPlayerActor::CheckSkip()
{
	GetWorldTimerManager().ClearTimer(Handle);
	MediaPlayer->Pause();
	stepManager->NextStep();
}

void AMediaSoundPlayerActor::CMS_Start()
{
	MediaPlayer->Play();
}

void AMediaSoundPlayerActor::CMS_Stop()
{
	MediaPlayer->Pause();
}

void AMediaSoundPlayerActor::MediaSoundPlayCheck()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->NextStep();
}
