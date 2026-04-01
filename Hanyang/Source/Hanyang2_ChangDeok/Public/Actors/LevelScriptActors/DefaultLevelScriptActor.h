// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DefaultLevelScriptActor.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class HANYANG2_CHANGDEOK_API ADefaultLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void CustomCreateWidget(TSubclassOf<UUserWidget> _DefaultWidgetClass){}
};
