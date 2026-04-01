// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/ChangePossessActor.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/StepManager.h"
#include "GameMode/DefaultGameMode.h"


void AChangePossessActor::CustomPossess()
{
	if(MoveStartPoint)
		SetStartPos();

	if(PossessPawn)
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(PossessPawn);
}

void AChangePossessActor::SetMainWidgetDefault()
{
	stepManager->GetGameMode()->GetWidgetActor()->SetMainWidgetDefault();
}

void AChangePossessActor::SetStartPos()
{
	PossessPawn->SetActorTransform(FTransform(MoveStartPoint->GetActorRotation(), MoveStartPoint->GetActorLocation(), FVector(1.f, 1.f, 1.f)));
}

void AChangePossessActor::CallCustomFadeIn()
{
	stepManager->GetGameMode()->GetWidgetActor()->CustomFadeIn();
}

void AChangePossessActor::CallCustomFadeOut()
{
	stepManager->GetGameMode()->GetWidgetActor()->CustomFadeOut();
}