// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChiJo/ChiJoButtonWidget.h"
#include "Actors/Widget/ChiJo/ChiJoMainWidget.h"

void UChiJoButtonWidget::MovePlace()
{
	MainWidget->OnPressed_MovePlaceButton(MyStepManagerNumber);
}
