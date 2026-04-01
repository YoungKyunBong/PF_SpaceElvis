// Fill out your copyright notice in the Description page of Project Settings.


#include "FeedBackEachMovieActor.h"
#include "Manager/StepManager.h"

void AFeedBackEachMovieActor::ChangeScene()
{
	if(stepManager->InterMovieIndex.Num() == 0)
		return;

	stepManager->CallChangeMovieScene(sceneTypes[stepManager->InterMovieIndex[0]]);

	stepManager->InterMovieIndex.RemoveAt(0);
}
