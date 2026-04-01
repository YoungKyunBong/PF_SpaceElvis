// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/StepActor.h"

// Sets default values
AStepActor::AStepActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStepActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStepActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

