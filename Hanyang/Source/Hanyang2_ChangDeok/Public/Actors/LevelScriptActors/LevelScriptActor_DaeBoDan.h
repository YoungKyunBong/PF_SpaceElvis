// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_DaeBoDan.generated.h"

/**
 * 
 */

class UUserWidget;
class UDaeBoDanMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_DaeBoDan : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UDaeBoDanMainWidget* GetWidgetBP() { return widgetBP; }

private:
	UDaeBoDanMainWidget* widgetBP;
};
