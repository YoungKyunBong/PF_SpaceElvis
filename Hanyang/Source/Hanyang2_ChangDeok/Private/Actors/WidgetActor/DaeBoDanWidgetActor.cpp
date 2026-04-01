// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/DaeBoDanWidgetActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_DaeBoDan.h"
#include "Actors/Widget/DaeBoDan/DaeBoDanMainWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Actors/StepActors/SetRenderDepthActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void ADaeBoDanWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_DaeBoDan>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	SetEmissiveActorInsDyn();
}

void ADaeBoDanWidgetActor::SetEmissiveActorValues(float _TimeEmissive)
{
	for (int i = 0; i < EmissiveActorInsDyn.Num(); i++)
		EmissiveActorInsDyn[i]->SetScalarParameterValue("Light_On_Off", _TimeEmissive);
}

void ADaeBoDanWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void ADaeBoDanWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	if (AStepManager* tempManager = GetGameMode()->GetCurrentStepManager(StepManagerNum))
		tempManager->NextStep();
}

void ADaeBoDanWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void ADaeBoDanWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void ADaeBoDanWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void ADaeBoDanWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->C_Init();
}

void ADaeBoDanWidgetActor::SetWidgetVisibility(bool IsVisible)
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

void ADaeBoDanWidgetActor::SetSkipButtonText(FString Text)
{
	LevelBP->GetWidgetBP()->SetSkipButtonText(Text);
}

void ADaeBoDanWidgetActor::SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize)
{
	LevelBP->GetWidgetBP()->SetSubTextToWidget(GetGameManager()->GetNaText(TextID), margin_Top, _fontSize);
}

void ADaeBoDanWidgetActor::SetSubWidgetHidden()
{
	LevelBP->GetWidgetBP()->SetSubWidgetHidden();
}

void ADaeBoDanWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

void ADaeBoDanWidgetActor::SetEmissiveActorInsDyn()
{
	for (int i = 0; i < EmissiveActors.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0));

	for (int i = 0; i < RenderDepthActors.Num(); i++)
		EmissiveActorInsDyn.Add(RenderDepthActors[i]->GetChangeMeshDynIns());
}
