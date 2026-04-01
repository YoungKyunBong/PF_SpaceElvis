

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Protocols.h"
#include "WhaleCharacter.generated.h"

class ATargetPoint;

//재업로드 주석
UCLASS()
class FUTUREOCEAN_API AWhaleCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bTurn;

	UPROPERTY(BlueprintReadWrite)
	bool isMove;

public:
	// Called every frame
//	virtual void Tick(float DeltaTime) override;
	void Init(class ADefaultManager* _manager);

	UFUNCTION(BlueprintNativeEvent)
	void IsWhaleMove(bool _isMove);
	UFUNCTION(BlueprintCallable)
	virtual void IsWhaleMove_Implementation(bool _isMove) {}
	UFUNCTION(BlueprintNativeEvent)
	void SendSideType();
	UFUNCTION(BlueprintCallable)
	virtual void SendSideType_Implementation();

	UFUNCTION(BlueprintCallable)
	void SendCleaningOceanLevelEnd();

	UFUNCTION(BlueprintNativeEvent)
	void MoveObject();
	UFUNCTION(BlueprintCallable)
	virtual void MoveObject_Implementation(){}

	void SetSideType(SIDE_TYPE _type);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	SIDE_TYPE GetSideType() { return SideType; }

	//UFUNCTION(BlueprintCallable)
	//FVector GetTargetLocation(); 
	//UFUNCTION(BlueprintCallable)
	//void FindNextTarget();
	UFUNCTION(BlueprintCallable)
	void ChaseTarget(float DeltaTime);
	//UFUNCTION(BlueprintCallable)
	//void Floor_ChaseTarget(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void LookAt(float DeltaTime);
	//UFUNCTION(BlueprintCallable)
	//void Floor_LookAt(float DeltaTime);
	UFUNCTION()
	void CheckThreshold();

	UFUNCTION()
	void SendSideTypeToServer();
	//UFUNCTION(BlueprintCallable)
	//int32 GetCurTargetIndex() { return CurrentTargetIndex; }
	UFUNCTION(BlueprintCallable)
	int32 GetClearIndex() { return ClearIndex; }

	UFUNCTION(BlueprintCallable)
	void SetClearIndex(int index) { ClearIndex = index; }
	UFUNCTION(BlueprintCallable)
	void SetStartPoint(SIDE_TYPE _type);
	UFUNCTION(BlueprintCallable)
	inline void SetIsMove(bool isA) { isMove = isA; }

	//void GetTargetPoints();
	ATargetPoint* TargetPoint;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<ATargetPoint> LeftSide_TargetPoint;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<ATargetPoint> RightSide_TargetPoint;

	UPROPERTY(EditAnywhere)
	bool IsWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USphereComponent> CollisionSphere;

private:
	class AWall_CleaningOceanManager* wallManager;
	class AFloor_CleaningOceanManager* floorManager;

	FVector vTargetLocation = { 0.f,0.f,0.f };
	SIDE_TYPE SideType = SIDE_TYPE::LeftSide;

	//int32 CurrentTargetIndex = 0;
	//int32 EndWayPointIndex = 3;
	//int32 SideTypeIndex = 0;
	int32 ClearIndex = 0;

	bool bThreshold = false;
};
