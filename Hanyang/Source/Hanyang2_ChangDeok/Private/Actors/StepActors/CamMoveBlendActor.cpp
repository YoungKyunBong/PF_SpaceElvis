// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/CamMoveBlendActor.h"
#include "Kismet/GameplayStatics.h"

void ACamMoveBlendActor::CustomViewBlend()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(TargetCam, BlendTime);
}
