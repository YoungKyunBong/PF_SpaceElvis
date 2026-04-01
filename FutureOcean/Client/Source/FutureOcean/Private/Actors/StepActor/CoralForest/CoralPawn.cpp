#include "Actors/StepActor/CoralForest/CoralPawn.h"


void ACoralPawn::MoveForward(float AxisValue)
{
	vCharacterLocation = GetActorLocation();
	vForwardVector = GetActorForwardVector();
	FVector vNewLocation = vCharacterLocation + fMoveSpeed * AxisValue * vForwardVector;

	SetActorLocation(vNewLocation);
}

void ACoralPawn::MoveRight(float AxisValue)
{
	vCharacterLocation = GetActorLocation();
	vRightVector = GetActorRightVector();
	FVector vNewLocation = vCharacterLocation + fMoveSpeed * AxisValue * vRightVector;

	SetActorLocation(vNewLocation);
}

int ACoralPawn::Get_AttachedActors_Cnt()
{
	TArray<AActor*>AttachedActors;
	GetAttachedActors(AttachedActors);
	iAttachCnt = AttachedActors.Num();

	return iAttachCnt;
}

