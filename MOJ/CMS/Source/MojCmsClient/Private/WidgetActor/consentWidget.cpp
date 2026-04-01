// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/consentWidget.h"

void UConsentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Check_Agree)
		Check_Agree->OnCheckStateChanged.AddDynamic(this, &UConsentWidget::OnAgreeChanged);

	if (Check_Disagree)
		Check_Disagree->OnCheckStateChanged.AddDynamic(this, &UConsentWidget::OnDisagreeChanged);

	// 초기 상태(둘 다 꺼짐 / 혹은 기본값 하나 켜고 싶으면 여기서 설정)
	SetRadioState(false, false);
}

void UConsentWidget::SetRadioState(bool bAgreeChecked, bool bDisagreeChecked)
{
	bSyncing = true;

	if (Check_Agree)
		Check_Agree->SetIsChecked(bAgreeChecked);

	if (Check_Disagree)
		Check_Disagree->SetIsChecked(bDisagreeChecked);

	// 상태 저장
	if (bAgreeChecked)       bAgreed = true;
	else if (bDisagreeChecked) bAgreed = false;
	// 둘 다 false면 bAgreed는 유지/초기값 그대로 (원하면 여기서 별도 처리)

	bSyncing = false;
}

void UConsentWidget::OnAgreeChanged(bool bIsChecked)
{
	if (bSyncing) return;

	if (bIsChecked)
	{
		// 동의 켜면 비동의는 반드시 끔
		SetRadioState(true, false);
	}
	else
	{
		// 동의를 끌 때 "둘 다 OFF 허용"이면 그대로 둠
		// "항상 하나는 선택" 강제하고 싶으면 아래로:
		// SetRadioState(false, true);
		SetRadioState(false, false);
	}
}

void UConsentWidget::OnDisagreeChanged(bool bIsChecked)
{
	if (bSyncing) return;

	if (bIsChecked)
	{
		// 비동의 켜면 동의는 반드시 끔
		SetRadioState(false, true);
	}
	else
	{
		// 둘 다 OFF 허용
		// 강제하려면: SetRadioState(true, false);
		SetRadioState(false, false);
	}
}
