// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/DefaultGameMode.h"
#include "Manager/StepManager.h"
#include "Manager/SoundManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/MovieManager.h"

void ADefaultGameMode::SetStepManagers(TArray<AStepManager*> _StepManagers)
{
	for (int i = 0; i < _StepManagers.Num(); i++)
	{
		InWorldAllManager.Add(_StepManagers[i]->StepManagerNumber, _StepManagers[i]);
	}
}

AStepManager* ADefaultGameMode::GetCurrentStepManager(int StepManagerNum)
{
	if (InWorldAllManager.Contains(StepManagerNum))
		return InWorldAllManager[StepManagerNum];

	return nullptr;
}

#pragma region StepManager

void ADefaultGameMode::Call_ReStartStep()
{
	GetCurrentStepManager(0)->ReStartStep();
}

void ADefaultGameMode::Call_NextStep()
{
	GetCurrentStepManager(0)->NextStep();
}

void ADefaultGameMode::Call_RewindStep()
{
	GetCurrentStepManager(0)->RewindStep();
}

void ADefaultGameMode::Call_ReplayStep(FSelectButton selectButton)
{
	GetCurrentStepManager(0)->ReplayStep(selectButton);
}

#pragma endregion

#pragma region SoundManager

float ADefaultGameMode::Call_NarrationFadeOut(float FadeDuration, float FadeVolumeLevel)
{
	return SoundMgr->NarrationFadeOut(FadeDuration, FadeVolumeLevel);
}

float ADefaultGameMode::Call_PlayNarrationByID(FString _SoundID)
{
	return SoundMgr->PlayNarrationByID(_SoundID, NationType);
}

void ADefaultGameMode::Call_SetNarrationPaused(bool IsPlay)
{
	SoundMgr->SetNarrationPaused(IsPlay);
}

#pragma endregion

#pragma region MovieManager

void ADefaultGameMode::Call_MoviePlay()
{
	MovieManager->SetMoviePlay();
}

void ADefaultGameMode::Call_MoviePause()
{
	MovieManager->SetMoviePause();
}

void ADefaultGameMode::Call_ChangeMovieScene(MovieSceneType _type)
{
	MovieManager->SetChangeMovieScene(_type);
}

float ADefaultGameMode::Call_MediaPlayTime()
{
	return MovieManager->GetMediaPlayTime();
}

#pragma endregion

#pragma region WidgetManager

void ADefaultGameMode::Call_SetWidgetSwitchIndex(int index)
{
	WidgetManager->SetWidgetSwitchIndex(index);
}

void ADefaultGameMode::Call_SetNarrText(FString HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton)
{
	WidgetManager->SetNarrText(HeaderText, _textID, IsID, _IsVisibleNarrNextButton);
}

void ADefaultGameMode::Call_InmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton)
{
	WidgetManager->InmateSelectButton(HeaderText, buttonText, _IsVisibleNextButton);
}

void ADefaultGameMode::Call_InmateKeywordCardButton(TArray<FSelectButton> buttonText)
{
	WidgetManager->InmateKeywordCardButton(buttonText);
}

void ADefaultGameMode::Call_WidgetVisible(ESlateVisibility option)
{
	WidgetManager->SetWidgetVisible(option);
}

void ADefaultGameMode::Call_SetIconType(CheckIconType _checkIconType)
{
	WidgetManager->SetIconType(_checkIconType);
}

#pragma endregion