// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelScriptActors/LevelScriptActor_Huwon.h"
#include "Actors/Widget/Huwon/HuwonMainWidget.h"

void ALevelScriptActor_Huwon::CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass)
{
	if (_DefaultWidgetClass)
	{
		widgetBP = Cast<UHuwonMainWidget>(CreateWidget(GetWorld(), _DefaultWidgetClass));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}
