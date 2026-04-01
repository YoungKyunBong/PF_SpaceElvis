// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/Huwon/HuwonButtonWidget.h"
#include "Actors/Widget/Huwon/HuwonMainWidget.h"

void UHuwonButtonWidget::MovePlace()
{
	MainWidget->OnPressed_MovePlaceButton(MyStepManagerNumber);
}
