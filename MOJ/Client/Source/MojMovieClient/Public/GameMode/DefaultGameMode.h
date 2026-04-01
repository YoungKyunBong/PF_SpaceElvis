// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "../InsideDataStruct.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

class ASoundManager;
class AStepManager;
class AWidgetManager;
class AMovieManager;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SetSoundManager(ASoundManager* _SoundMgr) { SoundMgr = _SoundMgr; }

	UFUNCTION(BlueprintCallable)
	void SetStepManagers(TArray<AStepManager*> _StepManagers);

	UFUNCTION(BlueprintCallable)
	void SetMovieManager(AMovieManager* _MovieMgr) { MovieManager = _MovieMgr; }

	UFUNCTION(BlueprintCallable)
	void SetWidgetManager(AWidgetManager* _WidgetMgr) { WidgetManager = _WidgetMgr; }

protected:
	UPROPERTY(EditAnywhere)
	ENationType NationType;

public:
	UFUNCTION(BlueprintCallable)
	ASoundManager* GetSoundMgr() { return SoundMgr; }

	UFUNCTION(BlueprintCallable)
	AStepManager* GetCurrentStepManager(int StepManagerNum);

	UFUNCTION(BlueprintCallable)
	AWidgetManager* GetWidgetManager() { return WidgetManager; }

public:
	ENationType GetNationType() { return NationType; }

#pragma region StepManager

	UFUNCTION(BlueprintCallable)
	void Call_ReStartStep();

	void Call_NextStep();
	void Call_RewindStep();
	void Call_ReplayStep(FSelectButton selectButton);

#pragma endregion

#pragma region SoundManager

	float Call_NarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f);
	float Call_PlayNarrationByID(FString _SoundID);
	void Call_SetNarrationPaused(bool IsPlay);

#pragma endregion

#pragma region MovieManager

	void Call_MoviePlay();
	void Call_MoviePause();
	void Call_ChangeMovieScene(MovieSceneType _type);
	float Call_MediaPlayTime();

#pragma endregion

#pragma region WidgetManager

	void Call_SetWidgetSwitchIndex(int index);
	void Call_SetNarrText(FString HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton);
	void Call_InmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton);
	void Call_InmateKeywordCardButton(TArray<FSelectButton> buttonText);
	void Call_WidgetVisible(ESlateVisibility option);
	void Call_SetIconType(CheckIconType _checkIconType);

#pragma endregion

private:
	ASoundManager* SoundMgr = nullptr;
	AStepManager* StartStepManager = nullptr;
	AWidgetManager* WidgetManager = nullptr;
	AMovieManager* MovieManager = nullptr;

	TMap<int, AStepManager*> InWorldAllManager;
};
