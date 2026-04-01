// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChangDeokMain/DescriptButtonWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UDescriptButtonWidget::Init()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UDescriptButtonWidget::OnClickDescriptButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UDescriptButtonWidget::OnClickTextHideButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UDescriptButtonWidget::OnClickTextShowButton()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(1);
}
 