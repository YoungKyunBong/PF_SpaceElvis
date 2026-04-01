// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_YeonJo.generated.h"

/**
 * 
 */

class UUserWidget;
class UYeonJoMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_YeonJo : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UYeonJoMainWidget* GetWidgetBP() { return widgetBP; }

private:
	UYeonJoMainWidget* widgetBP;
};
