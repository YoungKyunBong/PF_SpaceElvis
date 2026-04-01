// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_Oejo.generated.h"

/**
 * 
 */

class UOejoMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_Oejo : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UOejoMainWidget* GetWidgetBP() { return widgetBP; }

private:
	UOejoMainWidget* widgetBP;
};
