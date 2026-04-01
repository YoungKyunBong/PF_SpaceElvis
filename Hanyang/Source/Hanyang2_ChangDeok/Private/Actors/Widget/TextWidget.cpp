// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/TextWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"

void UTextWidget::Init(FString PlayButtonText)
{
	PlayChangeButtonText = PlayButtonText;
}

void UTextWidget::OnPressed_PlayButton(FString PlayButtonText)
{
	PlayChangeButtonText = PlayButtonText;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	IsPaused = true;
}

void UTextWidget::OnPressed_StopButton(FString PlayButtonText)
{
	PlayChangeButtonText = PlayButtonText;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	IsPaused = false;
}

void UTextWidget::OnPressed_TimeChangeButton(int Index, float _TimeOfDay, float _TimeEmissive)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(Index);
	C_TimeOfDay = _TimeOfDay;
	C_TimeEmissive = _TimeEmissive;
}

void UTextWidget::SetDefault_Implementation()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UTextWidget::SetIsEnabled(bool isEnabled)
{
	C_WidgetSwitcher->SetIsEnabled(isEnabled);
}
