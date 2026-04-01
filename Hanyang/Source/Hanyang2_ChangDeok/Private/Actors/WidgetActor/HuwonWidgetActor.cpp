// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WidgetActor/HuwonWidgetActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Hanyang2_ChangDeok/GameManager.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Actors/LevelScriptActors/LevelScriptActor_Huwon.h"
#include "Actors/Widget/Huwon/HuwonMainWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "LampActor.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void AHuwonWidgetActor::Init()
{
	LevelBP = Cast<ALevelScriptActor_Huwon>(GetGameMode()->GetLevelBP());
	LevelBP->GetWidgetBP()->SetWidgetActor(this);
	SetEmissiveActorInsDyn();
}

void AHuwonWidgetActor::SetEmissiveActorValues(float _TimeEmissive)
{
	for (int i = 0; i < EmissiveActorInsDyn.Num(); i++)
		EmissiveActorInsDyn[i]->SetScalarParameterValue("Light_On_Off", _TimeEmissive);
}

void AHuwonWidgetActor::SetTextToWidget(FString TextID)
{
	LevelBP->GetWidgetBP()->SetChangeText(GetGameManager()->GetNaText(TextID));
}

void AHuwonWidgetActor::OnPressed_CallNextStep(int StepManagerNum)
{
	if (AStepManager* tempManager = GetGameMode()->GetCurrentStepManager(StepManagerNum))
		tempManager->NextStep();
}

void AHuwonWidgetActor::OnPressed_CallResetSkip(int StepManagerNum)
{
	GetGameMode()->GetCurrentStepManager(StepManagerNum)->Reset_Skip();
}

void AHuwonWidgetActor::CustomFadeIn()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeIn();
}

void AHuwonWidgetActor::CustomFadeOut()
{
	LevelBP->GetWidgetBP()->GetFadeWidget()->CustomFadeOut();
}

void AHuwonWidgetActor::SetMainWidgetDefault()
{
	LevelBP->GetWidgetBP()->C_Init();
}

void AHuwonWidgetActor::SetWidgetVisibility(bool IsVisible)
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

void AHuwonWidgetActor::SetSkipButtonText(FString Text)
{
	LevelBP->GetWidgetBP()->SetSkipButtonText(Text);
}

void AHuwonWidgetActor::SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize)
{
	LevelBP->GetWidgetBP()->SetSubTextToWidget(GetGameManager()->GetNaText(TextID), margin_Top, _fontSize);
}

void AHuwonWidgetActor::SetSubWidgetHidden()
{
	LevelBP->GetWidgetBP()->SetSubWidgetHidden();
}

void AHuwonWidgetActor::SetSoundPlay(bool IsPaused)
{
	GetGameMode()->GetSoundMgr()->SetNarrationPaused(IsPaused);
}

void AHuwonWidgetActor::SetEmissiveActorInsDyn()
{
	for(int i = 0; i < EmissiveActors.Num(); i++)
		EmissiveActorInsDyn.Add(EmissiveActors[i]->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0));

	for (int i = 0; i < LampActor_M2.Num(); i++)
		EmissiveActorInsDyn.Add(LampActor_M2[i]->GetChangeMeshDynIns_M2());
}
