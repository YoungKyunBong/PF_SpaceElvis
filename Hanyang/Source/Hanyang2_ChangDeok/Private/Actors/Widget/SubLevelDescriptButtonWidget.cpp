// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/SubLevelDescriptButtonWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void USubLevelDescriptButtonWidget::Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
}

void USubLevelDescriptButtonWidget::OnClickDescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
}

void USubLevelDescriptButtonWidget::OnClickTextHideButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(2);
}

void USubLevelDescriptButtonWidget::OnClickTextShowButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
}
