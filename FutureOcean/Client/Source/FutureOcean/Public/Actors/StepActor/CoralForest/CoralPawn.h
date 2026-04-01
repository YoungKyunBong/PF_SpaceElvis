#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CoralPawn.generated.h"

UCLASS()
class FUTUREOCEAN_API ACoralPawn : public APawn
{
	GENERATED_BODY()

public:
	/*C++_Method*/
	int Get_AttachedActors_Cnt();

protected:
	/*BlueprintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	void MoveForward(float AxisValue);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float AxisValue);

protected:
	FVector vCharacterLocation;
	FVector vForwardVector;
	FVector vRightVector;

	float	fMoveSpeed = 10.f;
	int		iAttachCnt = 0;
};
