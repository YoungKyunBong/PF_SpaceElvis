// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/EndStepActor.h"
#include "Manager/StepManager.h"
#include "Kismet/GameplayStatics.h"

void AEndStepActor::SetStepManagerDefault()
{
	stepManager->StepCount = 0;
	SetInputModeDefault();
}

void AEndStepActor::SetInputModeDefault()
{
	FInputModeGameAndUI inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	inputMode.SetHideCursorDuringCapture(true);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(inputMode);
}
