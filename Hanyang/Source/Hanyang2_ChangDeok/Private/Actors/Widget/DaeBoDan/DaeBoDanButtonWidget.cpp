// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/DaeBoDan/DaeBoDanButtonWidget.h"
#include "Actors/Widget/DaeBoDan/DaeBoDanMainWidget.h"

void UDaeBoDanButtonWidget::MovePlace()
{
	MainWidget->OnPressed_MovePlaceButton(MyStepManagerNumber);
}
