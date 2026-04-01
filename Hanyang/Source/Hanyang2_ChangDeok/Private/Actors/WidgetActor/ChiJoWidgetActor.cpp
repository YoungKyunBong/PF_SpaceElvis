// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/ChiJoWidgetActor.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_ChiJo.h"
#include "Actors/Widget/ChiJo/ChiJoMainWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Actors/StepActors/SetRenderDepthActor.h"
#include "LampActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void AChiJoWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_ChiJo>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	SetEmissiveActorInsDyn();
}

void AChiJoWidgetActor::SetEmissiveActorValues(float _TimeEmissive)
{
	for (int i = 0; i < EmissiveActorInsDyn.Num(); i++)
		EmissiveActorInsDyn[i]->SetScalarParameterValue("Light_On_Off", _TimeEmissive);
}

void AChiJoWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void AChiJoWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	if (AStepManager* tempManager = GetGameMode()->GetCurrentStepManager(StepManagerNum))
		tempManager->NextStep();
}

void AChiJoWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void AChiJoWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void AChiJoWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void AChiJoWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->C_Init();
}

void AChiJoWidgetActor::SetWidgetVisibility(bool IsVisible)
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

void AChiJoWidgetActor::SetSkipButtonText(FString Text)
{
	LevelBP->GetWidgetBP()->SetSkipButtonText(Text);
}

void AChiJoWidgetActor::SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize)
{
	LevelBP->GetWidgetBP()->SetSubTextToWidget(GetGameManager()->GetNaText(TextID), margin_Top, _fontSize);
}

void AChiJoWidgetActor::SetSubWidgetHidden()
{
	LevelBP->GetWidgetBP()->SetSubWidgetHidden();
}

void AChiJoWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

void AChiJoWidgetActor::SetEmissiveActorInsDyn()
{
	for (int i = 0; i < EmissiveActors.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0));

	for (int i = 0; i < RenderDepthActors.Num(); i++)
		EmissiveActorInsDyn.Add(RenderDepthActors[i]->GetChangeMeshDynIns());

	for (int i = 0; i < LampActor_M2.Num(); i++)
		EmissiveActorInsDyn.Add(LampActor_M2[i]->GetChangeMeshDynIns_M2());
}
