// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DataActors/SoundActor.h"
#include "GameMode/DefaultGameMode.h"
#include "Manager/SoundManager.h"
#include "Manager/StepManager.h"
#include "Kismet/KismetSystemLibrary.h"

void ASoundActor::PlayNarr()
{
	float deleyTime = stepManager->GetGameMode()->GetSoundMgr()->PlayNarrationByID(SoundID);

	GetWorldTimerManager().SetTimer(Handle, this, &ASoundActor::SetTimer_PlayNarr, deleyTime, false);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), deleyTime));
}

float ASoundActor::CheckSkip()
{
	GetWorldTimerManager().ClearTimer(Handle);
	return stepManager->GetGameMode()->GetSoundMgr()->NarrationFadeOut(0.5);
}

//void ASoundActor::MyStep_Implementation(AStepManager* Manager)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlaySound!")));
//}

void ASoundActor::SetTimer_PlayNarr()
{
	GetWorldTimerManager().ClearTimer(Handle);
	stepManager->NextStep();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Next Step!")));
}
 