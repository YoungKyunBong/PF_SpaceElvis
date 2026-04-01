


#include "Manager/StepManager.h"
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
		stepActors[StepCount++]->MyStep(this);
	}
}

void AStepManager::Init()
{
	for (int i = 0; i < stepActors.Num(); i++)
	{
		stepActors[i]->Init(this);
	}
}

void AStepManager::NextStep()
{
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

void AStepManager::Reset_Skip_Implementation()
{
	for (int i = 0; i < stepActors.Num(); i++)
	{
		stepActors[i]->ResetSkip();
	}
}

void AStepManager::CallResetSkip()
{
	Reset_Skip();
}

bool AStepManager::CheckStepCount()
{
	return StepCount != stepActors.Num();
}

void AStepManager::Call_AnimFadeWidget(bool IsFadeIn)
{
	GetGameMode()->Call_AnimFadeWidget(IsFadeIn);
}

//void AStepManager::Call_WidgetSwitcherIndex(int _index)
//{
//	GetGameMode()->Call_WidgetSwitcherIndex(_index);
//}

void AStepManager::Call_CmsIsStart(bool _IsStart)
{
	if (!IsGameEnd) {
		if (CheckStepCount())
			SetGamePlay(!_IsStart);
	}
}

void AStepManager::Call_LastStep()
{
	if (!IsGameEnd) {
		if (CheckStepCount())
			stepActors[stepActors.Num() - 1]->MyStep(this);
	}
}

void AStepManager::SetGamePlay(bool _IsGameStop)
{
	IsGameStop = _IsGameStop;
	StepStart();
}
