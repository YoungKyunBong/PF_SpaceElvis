// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "../InsideDataStruct.h"
#include "GameFramework/Actor.h"
#include "DefaultManager.generated.h"

class UGameManager;
class ADefaultGameMode;

UCLASS()
class MOJMOVIECLIENT_API ADefaultManager : public AActor
{
	GENERATED_BODY()
	
private:
	UGameManager* GameIns;
	ADefaultGameMode* GameMode;

protected:
	UFUNCTION(BlueprintCallable)
	void SetGameManager(UGameManager* _GameIns);

	UFUNCTION(BlueprintCallable)
	void SetGameMode(ADefaultGameMode* _GameMode) { GameMode = _GameMode; }
public:
	UFUNCTION(BlueprintCallable)
	UGameManager* GetGameManager();

	UFUNCTION(BlueprintCallable)
	ADefaultGameMode* GetGameMode() { return GameMode; }

	UFUNCTION(BlueprintCallable)
	virtual void Init();

	UFUNCTION(BlueprintNativeEvent)
	void DefaultManagerInit();
	UFUNCTION(BlueprintCallable)
	virtual void DefaultManagerInit_Implementation() {}

#pragma region StepManager

	UFUNCTION(BlueprintCallable)
	virtual void NextStep() {}

	UFUNCTION(BlueprintCallable)
	virtual void SkipStep() {}

	UFUNCTION(BlueprintCallable)
	virtual void RewindStep() {}

	UFUNCTION(BlueprintCallable)
	virtual void ReplayStep(FSelectButton selectButton) {}

	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void Reset_Skip();
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void Reset_Skip_Implementation() {}

	void CallNextStep();
	void CallRewindStep();
	void CallReplayStep(FSelectButton selectButton);

#pragma endregion

#pragma region SoundManager

	virtual float NarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f) { return 0.0f; }
	virtual float PlayNarrationByID(FString _SoundID, ENationType _type) { return 0.0f; }
	virtual void SetNarrationPaused(bool IsPlay) {}

	float CallNarrationFadeOut(float FadeDuration, float FadeVolumeLevel = 0.f);
	float CallPlayNarrationByID(FString _SoundID);
	void CallSetNarrationPaused(bool IsPlay);

#pragma endregion

#pragma region MovieManager

	virtual void SetMoviePlay() {}
	virtual void SetMoviePause() {}
	virtual void SetChangeMovieScene(MovieSceneType _type) {}
	virtual float GetMediaPlayTime() { return 0.0f; }

	void CallMoviePlay();
	void CallMoviePause();
	void CallChangeMovieScene(MovieSceneType _type);
	float CallMediaPlayTime();

#pragma endregion

#pragma region WidgetManager

	virtual void SetWidgetSwitchIndex(int index) {}
	virtual void SetNarrText(FString HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton) {}
	virtual void InmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton) {}
	virtual void InmateKeywordCardButton(TArray<FSelectButton> buttonText) {}
	virtual void SetWidgetVisible(ESlateVisibility option) {}
	virtual void SetIconType(CheckIconType _checkIconType) {}

	void CallSetWidgetSwitchIndex(int index);
	void CallSetNarrText(FString HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton);
	void CallInmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton);
	void CallInmateKeywordCardButton(TArray<FSelectButton> buttonText);
	void CallWidgetVisible(ESlateVisibility option);
	void CallSetIconType(CheckIconType _checkIconType);

#pragma endregion

};
