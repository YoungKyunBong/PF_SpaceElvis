// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/DaeBoDan/DaeBoDanMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Actors/WidgetActor/DaeBoDanWidgetActor.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/Widget/DaeBoDan/DaeBoDanSubDescriptWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Animation/WidgetAnimation.h"

void UDaeBoDanMainWidget::C_Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_SubDescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	OnPressed_TimeChangeButton();
	C_DaeBoDanSubDescriptWidget->ResetWidgetAnim();
}

void UDaeBoDanMainWidget::SetWidgetVisibility(ESlateVisibility _SlateVisibility)
{
	C_WidgetSwitcher->SetVisibility(_SlateVisibility);
	C_SubDescriptButtonWidget->SetVisibility(_SlateVisibility);
}

void UDaeBoDanMainWidget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UDaeBoDanMainWidget::SetSkipButtonText(FString text)
{
	C_TextWidget->SetSkipButtonText(text);
}

void UDaeBoDanMainWidget::OnPressed_MovePlaceButton(int StepManagerNum)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = StepManagerNum;
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}
void UDaeBoDanMainWidget::SetSubTextToWidget(FString subText, double margin_Top, float _fontSize)
{
	C_DaeBoDanSubDescriptWidget->SetTextToWidget(subText, margin_Top, _fontSize);
	PlayAnimation(C_SubDescriptAnim);
}

void UDaeBoDanMainWidget::SetSubWidgetHidden()
{
	C_DaeBoDanSubDescriptWidget->ReverseWidgetAnim();
	PlayAnimation(C_SubDescriptAnim, C_DaeBoDanSubDescriptWidget->AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UDaeBoDanMainWidget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(CurrentStepManagerNum);
}

void UDaeBoDanMainWidget::OnPressed_Binding_DescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = C_SubDescriptButtonWidget->GetStepManagerNumber();
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UDaeBoDanMainWidget::OnPressed_Binding_TextHideButton()
{
	C_SubDescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UDaeBoDanMainWidget::OnPressed_Binding_TextShowButton()
{
	C_SubDescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UDaeBoDanMainWidget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UDaeBoDanMainWidget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UDaeBoDanMainWidget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
	WidgetActor->SetEmissiveActorValues(C_TextWidget->C_TimeEmissive);
}
