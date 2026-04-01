// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

/**
 * 
 */
class ASoundManager;
class AStepManager;
class ADefaultLevelScriptActor;
class ADefaultManager;

UCLASS()
class HANYANG2_CHANGDEOK_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetStartStepManager(AStepManager* _StepManager);

	UFUNCTION(BlueprintCallable)
	void SetSoundManager(ASoundManager* _SoundMgr) { SoundMgr = _SoundMgr; }

	UFUNCTION(BlueprintCallable)
	void SetStepManagers(TArray<AStepManager*> _StepManagers);

	UFUNCTION(BlueprintCallable)
	void SetLevelBP(ADefaultLevelScriptActor* _LevelBP) { LevelBP = _LevelBP; }

	UFUNCTION(BlueprintCallable)
	void SetWidgetActor(ADefaultManager* _WidgetActor) { WidgetActor = _WidgetActor; }

	//UFUNCTION(BlueprintCallable)
	//void SetCurrentStepManager(AStepManager* _StepManager) { CurrStepManager = _StepManager; }

public:
	UFUNCTION(BlueprintCallable)
	ASoundManager* GetSoundMgr() { return SoundMgr; }

	UFUNCTION(BlueprintCallable)
	ADefaultLevelScriptActor* GetLevelBP() { return LevelBP; }

	UFUNCTION(BlueprintCallable)
	AStepManager* GetCurrentStepManager(int StepManagerNum);

	UFUNCTION(BlueprintCallable)
	ADefaultManager* GetWidgetActor() { return WidgetActor; }

	UFUNCTION(BlueprintCallable)
	void ProcessStartStepManager();

	UFUNCTION(BlueprintCallable)
	void PlayNotFirst();

private:
	ASoundManager* SoundMgr = nullptr;
	AStepManager* StartStepManager = nullptr;
	//TArray<AStepManager*> StepManagers;
	AStepManager* CurrStepManager = nullptr;
	ADefaultLevelScriptActor* LevelBP = nullptr;
	ADefaultManager* WidgetActor = nullptr;

	TMap<int, AStepManager*> InWorldAllManager;
};
