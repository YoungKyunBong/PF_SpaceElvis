// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_ChangDeokMain.generated.h"

/**
 * 
 */

class UUserWidget;
class UChangDeokMainWIdget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_ChangDeokMain : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
	
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UChangDeokMainWIdget* GetWidgetBP() { return widgetBP; }

private:
	UChangDeokMainWIdget* widgetBP;
};
