// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/StepActors/SqeStep.h"
#include "Actors/StepActors/StepActor.h"

// Sets default values
ASqeStep::ASqeStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASqeStep::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASqeStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASqeStep::Init(AStepManager* Manager)
{
	StepActor->Init(Manager);
}

void ASqeStep::CheckStep(AStepManager* Manager)
{
	StepActor->MyStep(Manager);
}

void ASqeStep::SkipStep()
{
	StepActor->SkipStep();
}

void ASqeStep::RewindStep()
{
	StepActor->RewindStep();
}

void ASqeStep::ResetSkip()
{
	StepActor->ResetSkip();
}

