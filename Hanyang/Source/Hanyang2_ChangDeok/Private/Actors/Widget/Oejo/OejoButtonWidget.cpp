// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/Oejo/OejoButtonWidget.h"
#include "Actors/Widget/Oejo/OejoMainWidget.h"

void UOejoButtonWidget::MovePlace()
{
	MainWidget->OnPressed_MovePlaceButton(MyStepManagerNumber);
}
