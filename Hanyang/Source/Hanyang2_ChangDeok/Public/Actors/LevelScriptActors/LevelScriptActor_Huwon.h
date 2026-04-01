// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelScriptActors/DefaultLevelScriptActor.h"
#include "LevelScriptActor_Huwon.generated.h"

/**
 * 
 */

class UHuwonMainWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ALevelScriptActor_Huwon : public ADefaultLevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass) override;

	UHuwonMainWidget* GetWidgetBP() { return widgetBP; }

private:
	UHuwonMainWidget* widgetBP;
};
