// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/MoviePlayerActor.h"
#include "Manager/StepManager.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "Kismet/KismetSystemLibrary.h"

void AMoviePlayerActor::Init(AStepManager* Manager)
{
	Super::Init(Manager);

	//MediaPlayer->OpenSource(MediaSource);

	//MediaPlayer->Play();

	//MediaPlayer->Pause();
}

void AMoviePlayerActor::PlayMovie()
{
	stepManager->CallMoviePlay();
}

void AMoviePlayerActor::PauseMovie()
{
	stepManager->CallMoviePause();
}
