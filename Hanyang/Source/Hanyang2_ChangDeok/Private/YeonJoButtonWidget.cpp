// Fill out your copyright notice in the Description page of Project Settings.


#include "YeonJoButtonWidget.h"
#include "Actors/Widget/YeonJo/YeonJoMainWidget.h"

void UYeonJoButtonWidget::MovePlace()
{
	MainWidget->OnPressed_MovePlaceButton(MyStepManagerNumber);
}
