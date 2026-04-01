// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DefaultManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"

void ADefaultManager::SetGameManager(UGameManager* _GameIns)
{
	GameIns = _GameIns;
}

UGameManager* ADefaultManager::GetGameManager()
{
	return GameIns;
}

void ADefaultManager::Init()
{
	DefaultManagerInit();
}

#pragma region StepManager

void ADefaultManager::CallNextStep()
{
	GameMode->Call_NextStep();
}

void ADefaultManager::CallRewindStep()
{
	GameMode->Call_RewindStep();
}

void ADefaultManager::CallReplayStep(FSelectButton selectButton)
{
	GameMode->Call_ReplayStep(selectButton);
}

#pragma endregion

#pragma region SoundManager

float ADefaultManager::CallNarrationFadeOut(float FadeDuration, float FadeVolumeLevel)
{
	return GameMode->Call_NarrationFadeOut(FadeDuration, FadeVolumeLevel);
}

float ADefaultManager::CallPlayNarrationByID(FString _SoundID)
{
	return GameMode->Call_PlayNarrationByID(_SoundID);
}

void ADefaultManager::CallSetNarrationPaused(bool IsPlay)
{
	GameMode->Call_SetNarrationPaused(IsPlay);
}

#pragma endregion

#pragma region MovieManager

void ADefaultManager::CallMoviePlay()
{
	GameMode->Call_MoviePlay();
}

void ADefaultManager::CallMoviePause()
{
	GameMode->Call_MoviePause();
}

void ADefaultManager::CallChangeMovieScene(MovieSceneType _type)
{
	GameMode->Call_ChangeMovieScene(_type);
	GameIns->SetMovieNum(_type);
}

float ADefaultManager::CallMediaPlayTime()
{
	return GameMode->Call_MediaPlayTime();
}

#pragma endregion

#pragma region WidgetManager

void ADefaultManager::CallSetWidgetSwitchIndex(int index)
{
	GameMode->Call_SetWidgetSwitchIndex(index);
}

void ADefaultManager::CallSetNarrText(FString HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton)
{
	GameMode->Call_SetNarrText(HeaderText, _textID, IsID, _IsVisibleNarrNextButton);
}

void ADefaultManager::CallInmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton)
{
	GameMode->Call_InmateSelectButton(HeaderText, buttonText, _IsVisibleNextButton);
}

void ADefaultManager::CallInmateKeywordCardButton(TArray<FSelectButton> buttonText)
{
	GameMode->Call_InmateKeywordCardButton(buttonText);
}

void ADefaultManager::CallWidgetVisible(ESlateVisibility option)
{
	GameMode->Call_WidgetVisible(option);
}

void ADefaultManager::CallSetIconType(CheckIconType _checkIconType)
{
	GameMode->Call_SetIconType(_checkIconType);
}

#pragma endregion