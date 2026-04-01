// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/YeonJo/YeonJoMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Actors/WidgetActor/YeonJoWidgetActor.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/Widget/YeonJo/YeonJoSubDescriptWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Animation/WidgetAnimation.h"

void UYeonJoMainWidget::C_Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_SubDescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	OnPressed_TimeChangeButton();
	C_YeonJoSubDescriptWidget->ResetWidgetAnim();
}

void UYeonJoMainWidget::SetWidgetVisibility(ESlateVisibility _SlateVisibility)
{
	C_WidgetSwitcher->SetVisibility(_SlateVisibility);
	C_SubDescriptButtonWidget->SetVisibility(_SlateVisibility);
}

void UYeonJoMainWidget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UYeonJoMainWidget::SetSkipButtonText(FString text)
{
	C_TextWidget->SetSkipButtonText(text);
}

void UYeonJoMainWidget::OnPressed_MovePlaceButton(int StepManagerNum)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = StepManagerNum;
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UYeonJoMainWidget::SetSubTextToWidget(FString subText, double margin_Top, float _fontSize)
{
	C_YeonJoSubDescriptWidget->SetTextToWidget(subText, margin_Top, _fontSize);
	PlayAnimation(C_SubDescriptAnim);
}

void UYeonJoMainWidget::SetSubWidgetHidden()
{
	C_YeonJoSubDescriptWidget->ReverseWidgetAnim();
	PlayAnimation(C_SubDescriptAnim, C_YeonJoSubDescriptWidget->AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UYeonJoMainWidget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(CurrentStepManagerNum);
}

void UYeonJoMainWidget::OnPressed_Binding_DescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	//C_WidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = C_SubDescriptButtonWidget->GetStepManagerNumber();
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UYeonJoMainWidget::OnPressed_Binding_TextHideButton()
{
	C_SubDescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UYeonJoMainWidget::OnPressed_Binding_TextShowButton()
{
	C_SubDescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UYeonJoMainWidget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UYeonJoMainWidget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UYeonJoMainWidget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
	WidgetActor->SetEmissiveActorValues(C_TextWidget->C_TimeEmissive);
}
