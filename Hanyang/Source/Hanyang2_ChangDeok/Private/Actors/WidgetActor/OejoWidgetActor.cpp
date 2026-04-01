// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/OejoWidgetActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_Oejo.h"
#include "Actors/Widget/Oejo/OejoMainWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Actors/StepActors/SetRenderDepthActor.h"
#include "LampActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void AOejoWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_Oejo>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	SetEmissiveActorInsDyn();
}

void AOejoWidgetActor::SetEmissiveActorValues(float _TimeEmissive)
{
	for (int i = 0; i < EmissiveActorInsDyn.Num(); i++)
		EmissiveActorInsDyn[i]->SetScalarParameterValue("Light_On_Off", _TimeEmissive);
}

void AOejoWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void AOejoWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	if (AStepManager* tempManager = GetGameMode()->GetCurrentStepManager(StepManagerNum))
		tempManager->NextStep();
}

void AOejoWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void AOejoWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void AOejoWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void AOejoWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->C_Init();
}

void AOejoWidgetActor::SetWidgetVisibility(bool IsVisible)
{
	if (IsVisible)
		LevelBP->GetWidgetBP()->SetWidgetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else
	{
		LevelBP->GetWidgetBP()->SetWidgetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	}
}

void AOejoWidgetActor::SetSkipButtonText(FString Text)
{
	LevelBP->GetWidgetBP()->SetSkipButtonText(Text);
}

void AOejoWidgetActor::SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize)
{
	LevelBP->GetWidgetBP()->SetSubTextToWidget(GetGameManager()->GetNaText(TextID), margin_Top, _fontSize);
}

void AOejoWidgetActor::SetSubWidgetHidden()
{
	LevelBP->GetWidgetBP()->SetSubWidgetHidden();
}

void AOejoWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

void AOejoWidgetActor::SetEmissiveActorInsDyn()
{
	for (int i = 0; i < EmissiveActors.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0));

	for (int i = 0; i < RenderDepthActors.Num(); i++)
		EmissiveActorInsDyn.Add(RenderDepthActors[i]->GetChangeMeshDynIns());

	for (int i = 0; i < LampActor_M2.Num(); i++)
		EmissiveActorInsDyn.Add(LampActor_M2[i]->GetChangeMeshDynIns_M2());
}
