// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/Huwon/HuwonMainWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Actors/WidgetActor/HuwonWidgetActor.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/Widget/Huwon/HuwonSubDescriptWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Animation/WidgetAnimation.h"

void UHuwonMainWidget::C_Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_SubDescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	OnPressed_TimeChangeButton();
	C_HuwonSubDescriptWidget->ResetWidgetAnim();
}

void UHuwonMainWidget::SetWidgetVisibility(ESlateVisibility _SlateVisibility)
{
	C_WidgetSwitcher->SetVisibility(_SlateVisibility);
	C_SubDescriptButtonWidget->SetVisibility(_SlateVisibility);
}

void UHuwonMainWidget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UHuwonMainWidget::SetSkipButtonText(FString text)
{
	C_TextWidget->SetSkipButtonText(text);
}

void UHuwonMainWidget::OnPressed_MovePlaceButton(int StepManagerNum)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = StepManagerNum;
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UHuwonMainWidget::SetSubTextToWidget(FString subText, double margin_Top, float _fontSize)
{
	C_HuwonSubDescriptWidget->SetTextToWidget(subText, margin_Top, _fontSize);
	PlayAnimation(C_SubDescriptAnim);
}

void UHuwonMainWidget::SetSubWidgetHidden()
{
	C_HuwonSubDescriptWidget->ReverseWidgetAnim();
	PlayAnimation(C_SubDescriptAnim, C_HuwonSubDescriptWidget->AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UHuwonMainWidget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(CurrentStepManagerNum);
}

void UHuwonMainWidget::OnPressed_Binding_DescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
	//C_WidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	C_SubDescriptButtonWidget->OnClickDescriptButton();
	CurrentStepManagerNum = C_SubDescriptButtonWidget->GetStepManagerNumber();
	WidgetActor->OnPressed_CallNextStep(CurrentStepManagerNum);
}

void UHuwonMainWidget::OnPressed_Binding_TextHideButton()
{
	C_SubDescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UHuwonMainWidget::OnPressed_Binding_TextShowButton()
{
	C_SubDescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UHuwonMainWidget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UHuwonMainWidget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UHuwonMainWidget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
	WidgetActor->SetEmissiveActorValues(C_TextWidget->C_TimeEmissive);
}
