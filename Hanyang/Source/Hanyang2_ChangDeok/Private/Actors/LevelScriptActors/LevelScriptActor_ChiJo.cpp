// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelScriptActors/LevelScriptActor_ChiJo.h"
#include "Actors/Widget/ChiJo/ChiJoMainWidget.h"

void ALevelScriptActor_ChiJo::CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass)
{
	if (_DefaultWidgetClass)
	{
		widgetBP = Cast<UChiJoMainWidget>(CreateWidget(GetWorld(), _DefaultWidgetClass));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}
