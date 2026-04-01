// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/Oejo/OejoMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Actors/WidgetActor/OejoWidgetActor.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/Widget/Oejo/OejoSubDescriptWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Animation/WidgetAnimation.h"

void UOejoMainWidget::C_Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_SubDescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	OnPressed_TimeChangeButton();
	C_OeJoSubDescriptWidget->ResetWidgetAnim();
}

void UOejoMainWidget::SetWidgetVisibility(ESlateVisibility _SlateVisibility)
{
	C_WidgetSwitcher->SetVisibility(_SlateVisibility);
	C_SubDescriptButtonWidget->SetVisibility(_SlateVisibility);
}

void UOejoMainWidget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UOejoMainWidget::SetSkipButtonText(FString text)
{
	C_TextWidget->SetSkipButtonText(text);
}

void UOejoMainWidget::OnPressed_MovePlaceButton(int StepManagerNum)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = StepManagerNum;
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UOejoMainWidget::SetSubTextToWidget(FString subText, double margin_Top, float _fontSize)
{
	C_OeJoSubDescriptWidget->SetTextToWidget(subText, margin_Top, _fontSize);
	PlayAnimation(C_SubDescriptAnim);
}

void UOejoMainWidget::SetSubWidgetHidden()
{
	C_OeJoSubDescriptWidget->ReverseWidgetAnim();
	PlayAnimation(C_SubDescriptAnim, C_OeJoSubDescriptWidget->AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UOejoMainWidget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(CurrentStepManagerNum);
}

void UOejoMainWidget::OnPressed_Binding_DescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = C_SubDescriptButtonWidget->GetStepManagerNumber();
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UOejoMainWidget::OnPressed_Binding_TextHideButton()
{
	C_SubDescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UOejoMainWidget::OnPressed_Binding_TextShowButton()
{
	C_SubDescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UOejoMainWidget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UOejoMainWidget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UOejoMainWidget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
	WidgetActor->SetEmissiveActorValues(C_TextWidget->C_TimeEmissive);
}
