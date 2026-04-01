// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StepActors/SetRenderDepthActor.h"
#include "Kismet/KismetSystemLibrary.h"

//UMaterialInstanceDynamic* ASetRenderDepthActor::GetChangeMeshDynIns()
//{
//	return changeMesh->CreateDynamicMaterialInstance(0);
//}

void ASetRenderDepthActor::SetRenderDepth()
{
	changeMesh->SetRenderCustomDepth(true);

	GetWorldTimerManager().SetTimer(Handle, this, &ASetRenderDepthActor::SetTimer_DepthRenderOff, deleyTime, false);
}

void ASetRenderDepthActor::CheckSkip()
{
	GetWorldTimerManager().ClearTimer(Handle);
	changeMesh->SetRenderCustomDepth(false);
}

void ASetRenderDepthActor::SetTimer_DepthRenderOff()
{
	GetWorldTimerManager().ClearTimer(Handle);
	changeMesh->SetRenderCustomDepth(false);
}
