// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_ChiJo.generated.h"

/**
 * 
 */

class UChiJoMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_ChiJo : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UChiJoMainWidget* GetWidgetBP() { return widgetBP; }

private:
	UChiJoMainWidget* widgetBP;
};
