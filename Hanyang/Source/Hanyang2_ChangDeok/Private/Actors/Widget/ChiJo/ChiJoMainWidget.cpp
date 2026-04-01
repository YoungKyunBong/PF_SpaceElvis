// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChiJo/ChiJoMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Actors/WidgetActor/ChiJoWidgetActor.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/Widget/ChiJo/ChiJoSubDescriptWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Animation/WidgetAnimation.h"

void UChiJoMainWidget::C_Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_SubDescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	OnPressed_TimeChangeButton();
	C_ChiJoSubDescriptWidget->ResetWidgetAnim();
}

void UChiJoMainWidget::SetWidgetVisibility(ESlateVisibility _SlateVisibility)
{
	C_WidgetSwitcher->SetVisibility(_SlateVisibility);
	C_SubDescriptButtonWidget->SetVisibility(_SlateVisibility);
}

void UChiJoMainWidget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UChiJoMainWidget::SetSkipButtonText(FString text)
{
	C_TextWidget->SetSkipButtonText(text);
}

void UChiJoMainWidget::OnPressed_MovePlaceButton(int StepManagerNum)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = StepManagerNum;
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UChiJoMainWidget::SetSubTextToWidget(FString subText, double margin_Top, float _fontSize)
{
	C_ChiJoSubDescriptWidget->SetTextToWidget(subText, margin_Top, _fontSize);
	PlayAnimation(C_SubDescriptAnim);
}

void UChiJoMainWidget::SetSubWidgetHidden()
{
	C_ChiJoSubDescriptWidget->ReverseWidgetAnim();
	PlayAnimation(C_SubDescriptAnim, C_ChiJoSubDescriptWidget->AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UChiJoMainWidget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(CurrentStepManagerNum);
}

void UChiJoMainWidget::OnPressed_Binding_DescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	//C_WidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = C_SubDescriptButtonWidget->GetStepManagerNumber();
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UChiJoMainWidget::OnPressed_Binding_TextHideButton()
{
	C_SubDescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UChiJoMainWidget::OnPressed_Binding_TextShowButton()
{
	C_SubDescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UChiJoMainWidget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UChiJoMainWidget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UChiJoMainWidget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
	WidgetActor->SetEmissiveActorValues(C_TextWidget->C_TimeEmissive);
}