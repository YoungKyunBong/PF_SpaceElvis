// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelScriptActors/LevelScriptActor_DaeBoDan.h"
#include "Actors/Widget/DaeBoDan/DaeBoDanMainWidget.h"

void ALevelScriptActor_DaeBoDan::CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass)
{
	if (_DefaultWidgetClass)
	{
		widgetBP = Cast<UDaeBoDanMainWidget>(CreateWidget(GetWorld(), _DefaultWidgetClass));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}
