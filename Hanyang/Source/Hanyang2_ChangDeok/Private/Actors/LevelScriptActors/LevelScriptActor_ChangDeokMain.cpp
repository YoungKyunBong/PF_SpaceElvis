// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelScriptActors/LevelScriptActor_ChangDeokMain.h"
#include "Actors/Widget/ChangDeokMain/ChangDeokMainWIdget.h"

void ALevelScriptActor_ChangDeokMain::CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass)
{
	if (_DefaultWidgetClass)
	{
		widgetBP = Cast<UChangDeokMainWIdget>(CreateWidget(GetWorld(), _DefaultWidgetClass));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}
