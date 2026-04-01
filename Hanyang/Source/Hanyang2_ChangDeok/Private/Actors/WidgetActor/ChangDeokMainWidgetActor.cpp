// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/ChangDeokMainWidgetActor.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_ChangDeokMain.h"
#include "Actors/Widget/ChangDeokMain/ChangDeokMainWIdget.h"
#include "Actors/Widget/FadeWidget.h"

void AChangDeokMainWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_ChangDeokMain>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	//CustomFadeOut();
}

void AChangDeokMainWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void AChangDeokMainWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->NextStep();
}

void AChangDeokMainWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void AChangDeokMainWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void AChangDeokMainWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void AChangDeokMainWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->CheckInit();
}

void AChangDeokMainWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

float AChangDeokMainWidgetActor::Call_DownLoadPercent()
{
	return GetGameManager()->Percent;
}

void AChangDeokMainWidgetActor::Call_SetHttpData(FString _Path, FString _Name)
{
	GetGameManager()->SetHttpData(_Path, _Name);
}