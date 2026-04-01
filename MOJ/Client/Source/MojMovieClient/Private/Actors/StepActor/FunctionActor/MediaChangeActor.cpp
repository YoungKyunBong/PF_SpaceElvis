// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/MediaChangeActor.h"
#include "Manager/StepManager.h"


void AMediaChangeActor::ChangeScene()
{
	stepManager->CallChangeMovieScene(sceneType);
}
