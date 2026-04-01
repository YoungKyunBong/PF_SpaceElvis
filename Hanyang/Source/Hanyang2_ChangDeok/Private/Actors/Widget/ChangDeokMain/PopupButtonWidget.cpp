// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChangDeokMain/PopupButtonWidget.h"
#include "Actors/Widget/ChangDeokMain/ChangDeokMainWIdget.h"

void UPopupButtonWidget::OnPressed_Button()
{
	MainWidget->SetPopupInfo(this);
}
