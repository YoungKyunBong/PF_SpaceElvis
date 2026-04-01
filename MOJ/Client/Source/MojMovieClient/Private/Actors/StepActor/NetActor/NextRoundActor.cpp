// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActor/NetActor/NextRoundActor.h"
#include "Manager/StepManager.h"

void ANextRoundActor::CallTempNextRound()
{
	stepManager->Call_TempNextRound();
}
