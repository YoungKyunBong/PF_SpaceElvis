// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/StepManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/StepActor.h"
#include "Kismet/GameplayStatics.h"

void AStepManager::SetNameCheck(AActor* checkActor, FString appendName)
{
#if WITH_EDITOR

	//editor only code -- doesn't appear in final game
	checkActor->SetActorLabel(appendName);
#endif
}

void AStepManager::StepStart()
{
	if (CheckStepCount() && !IsGameStop)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("StepStart"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug StepCount : %d"), StepCount));
		stepActors[StepCount++]->MyStep(this);
	}
}

void AStepManager::Init()
{
	Super::Init();

	//GetGameManager()->RecvCmsControllerStart.AddUFunction(this, FName("NextStep"));
	GetGameManager()->RecvCmsControllerPlay.AddUFunction(this, FName("MyStepPlay"));
	GetGameManager()->RecvCmsControllerPause.AddUFunction(this, FName("MyStepPause"));

	GetGameManager()->RecvCmsMovieNum.AddUFunction(this, FName("MyStepSectionMovement"));

	//InterMovieIndex.Add(0);
	//InterMovieIndex.Add(1);

	//MultSelectMovieIndex.Add(0);
	//MultSelectMovieIndex.Add(1);
	//MultSelectMovieIndex.Add(2);

	//MultNoneSelectMovieIndex.Add(3);
	//MultNoneSelectMovieIndex.Add(4);
	//MultNoneSelectMovieIndex.Add(5);
	//MultNoneSelectMovieIndex.Add(6);
	//MultNoneSelectMovieIndex.Add(7);

	//InterMovieIndex.Add(0);
	//InterMovieIndex.Add(1);
	//InterMovieIndex.Add(2);

	for (int i = 0; i < stepActors.Num(); i++)
	{
		stepActors[i]->Init(this);
	}
}

void AStepManager::NextStep()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NextStep"));
	if (!IsGameEnd)
		StepStart();
}

void AStepManager::SkipStep()
{
	if (!IsGameEnd) {
		if (CheckStepCount())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
			stepActors[StepCount]->SkipStep();
		}
	}
}

void AStepManager::RewindStep()
{
	if (CheckStepCount())
		stepActors[StepCount - 1]->RewindStep();
}

void AStepManager::ReplayStep(FSelectButton selectButton)
{
	if (CheckStepCount())
		stepActors[StepCount - 1]->ReplayStep(selectButton);
}

void AStepManager::ReturnStep()
{
	if(ReturnStepIndex != -1)
		stepActors[ReturnStepIndex]->ReturnStep();

	ReturnStepIndex = -1;
}

void AStepManager::Reset_Skip_Implementation()
{
	for (int i = 0; i < stepActors.Num(); i++)
	{
		stepActors[i]->ResetSkip();
	}
}

void AStepManager::Call_TempNextRound()
{
	GetGameManager()->Send_TempNextRound();
}

void AStepManager::MyStepPlay()
{
	stepActors[StepCount - 1]->MyStepPause(false);
}

void AStepManager::MyStepPause()
{
	stepActors[StepCount - 1]->MyStepPause(true);
}

void AStepManager::MyStepSectionMovement(int num)
{
	if(SectionMovementStepCount.Num() == 0)
		return;

	stepActors[StepCount - 1]->CmsSectionMovement();

	StepCount = SectionMovementStepCount[num];

	NextStep();
}

bool AStepManager::CheckStepCount()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CheckStepCount"));
	return StepCount != stepActors.Num();
}

void AStepManager::Call_LastStep()
{
	if (!IsGameEnd) {
		if (CheckStepCount())
			stepActors[stepActors.Num() - 1]->MyStep(this);
	}
}

void AStepManager::SetReturnStepIndex()
{
	ReturnStepIndex = StepCount - 1;
}

void AStepManager::ReStartStep()
{
	if (!IsGameEnd) {
		if (CheckStepCount())
		{
			StepStart();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug ReStart StepCount : %d"), StepCount));
		}
	}
}

FString AStepManager::GetNarrText(FString _textID)
{
	return 	GetGameManager()->GetNaText(_textID, GetGameMode()->GetNationType());
}