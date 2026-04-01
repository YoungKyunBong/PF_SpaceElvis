// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChiJo/ChiJoSubDescriptWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/SizeBoxSlot.h"
#include "Components/TextBlock.h"

void UChiJoSubDescriptWidget::NativeTick(const FGeometry& MyGeometry, float deltaTime)
{
	Super::NativeTick(MyGeometry, deltaTime);
	if (IsPlayingAnimation())
		AnimCurrTime = GetAnimationCurrentTime(C_OpenAnim);
}

void UChiJoSubDescriptWidget::SetTextToWidget(FString _text, double margin_Top, float _fontSize)
{
	text = _text;
	SetTextFont(_fontSize);
	C_SizeBoxSlot->SetPadding(FMargin(0.0, margin_Top, 0.0, 0.0));
	PlayAnimation(C_OpenAnim);
}

void UChiJoSubDescriptWidget::ReverseWidgetAnim()
{
	AnimCurrTime_Reverse = AnimEndTime - AnimCurrTime;
	PlayAnimation(C_OpenAnim, AnimCurrTime_Reverse, 1, EUMGSequencePlayMode::Reverse);
}

void UChiJoSubDescriptWidget::ResetWidgetAnim()
{
	AnimCurrTime = 0;
}

void UChiJoSubDescriptWidget::SetTextFont(float _fontSize)
{
	C_FontInfo.Size = _fontSize;
	C_TextBlock->SetFont(C_FontInfo);
}
