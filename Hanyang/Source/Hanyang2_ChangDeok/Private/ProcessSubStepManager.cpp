// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessSubStepManager.h"
#include "Manager/StepManager.h"
#include "Actors/StepActors/SqeStep.h"

void AProcessSubStepManager::SubStepInit()
{
	SubStepManager->Init();
	SubStepManager->NextStep();
}

void AProcessSubStepManager::SubStepSkip()
{
	SubStepManager->CallResetSkip();
	//for (int i = 0; i < SubStepManager->sqeSteps.Num(); i++)
	//{
	//	SubStepManager->sqeSteps[i]->ResetSkip();
	//}
}
