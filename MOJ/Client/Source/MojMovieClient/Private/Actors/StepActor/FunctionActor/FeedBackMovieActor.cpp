// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/FunctionActor/FeedBackMovieActor.h"
#include "Manager/StepManager.h"

void AFeedBackMovieActor::ChangeScene()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), stepManager->BeforeSelectIndex));
	stepManager->CallChangeMovieScene(sceneTypes[stepManager->BeforeSelectIndex]);
}
