// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelScriptActors/LevelScriptActor_YeonJo.h"
#include "Actors/Widget/YeonJo/YeonJoMainWidget.h"

void ALevelScriptActor_YeonJo::CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass)
{
	if (_DefaultWidgetClass)
	{
		widgetBP = Cast<UYeonJoMainWidget>(CreateWidget(GetWorld(), _DefaultWidgetClass));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}
