// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/YeonJoWidgetActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_YeonJo.h"
#include "Actors/Widget/YeonJo/YeonJoMainWidget.h"
#include "Actors/GetBPAllComp.h"
#include "Actors/Widget/FadeWidget.h"
#include "Actors/StepActors/SetRenderDepthActor.h"
#include "LampActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void AYeonJoWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_YeonJo>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	for (int i = 0; i < OthersBP.Num(); i++)
		OthersBP[i]->Init();
	SetEmissiveActorInsDyn();
}

void AYeonJoWidgetActor::SetEmissiveActorValues(float _TimeEmissive)
{
	for (int i = 0; i < EmissiveActorInsDyn.Num(); i++)
		EmissiveActorInsDyn[i]->SetScalarParameterValue("Light_On_Off", _TimeEmissive);
}

void AYeonJoWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void AYeonJoWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	if (AStepManager* tempManager = GetGameMode()->GetCurrentStepManager(StepManagerNum))
		tempManager->NextStep();
}

void AYeonJoWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void AYeonJoWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void AYeonJoWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void AYeonJoWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->C_Init();
}

void AYeonJoWidgetActor::SetWidgetVisibility(bool IsVisible)
{
	if(IsVisible)
		LevelBP->GetWidgetBP()->SetWidgetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else
	{
		LevelBP->GetWidgetBP()->SetWidgetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	}
}

void AYeonJoWidgetActor::SetSkipButtonText(FString Text)
{
	LevelBP->GetWidgetBP()->SetSkipButtonText(Text);
}

void AYeonJoWidgetActor::SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize)
{
	LevelBP->GetWidgetBP()->SetSubTextToWidget(GetGameManager()->GetNaText(TextID), margin_Top, _fontSize);
}

void AYeonJoWidgetActor::SetSubWidgetHidden()
{
	LevelBP->GetWidgetBP()->SetSubWidgetHidden();
}

void AYeonJoWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

void AYeonJoWidgetActor::SetEmissiveActorInsDyn()
{
	for (int i = 0; i < EmissiveActors.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0));

	for (int i = 0; i < EmissiveActors_M2.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors_M2[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(1));

	for (int i = 0; i < LampActor_M2.Num(); i++)
		EmissiveActorInsDyn.Add(LampActor_M2[i]->GetChangeMeshDynIns_M2());

	for (int i = 0; i < RenderDepthActors.Num(); i++)
		EmissiveActorInsDyn.Add(RenderDepthActors[i]->GetChangeMeshDynIns());

	for (int i = 0; i < RenderDepthActors_M2.Num(); i++)
		EmissiveActorInsDyn.Add(RenderDepthActors_M2[i]->GetChangeMeshDynIns_M2());

	for (int i = 0; i < OthersBP.Num(); i++)
	{
		TArray<UStaticMeshComponent*> tempComp = OthersBP[i]->GetCompCount();
		for (int j = 0; j < tempComp.Num(); j++)
			EmissiveActorInsDyn.Add(tempComp[j]->CreateDynamicMaterialInstance(0));

		tempComp.Empty();
	}
}
