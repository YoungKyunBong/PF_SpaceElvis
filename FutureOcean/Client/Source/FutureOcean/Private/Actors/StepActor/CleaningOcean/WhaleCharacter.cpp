#include "Actors/StepActor/CleaningOcean/WhaleCharacter.h"
#include "Manager/CleaningOcean/Wall_CleaningOceanManager.h"
#include "Manager/CleaningOcean/Floor_CleaningOceanManager.h"
#include "Engine/TargetPoint.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

//재업로드 주석

void AWhaleCharacter::Init(class ADefaultManager* _manager)
{
	//GetTargetPoints();
	//SetSideType();
	if (IsWall)
		wallManager = Cast<AWall_CleaningOceanManager>(_manager);
	else
		floorManager = Cast<AFloor_CleaningOceanManager>(_manager);
	//bThreshold = true;
}

void AWhaleCharacter::CheckThreshold()
{
	if (bThreshold == true)
	{
		return;
	}
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = TargetPoint->GetActorLocation();
	//(근접 거리)
	float Threshold = 100.f;

	// 거리 계산
	float Distance = FVector::Dist(CurrentLocation, TargetLocation);

	if (Distance <= Threshold)
	{
		bTurn = false;
		if (IsWall)
			wallManager->SendWallSpawnWhaleEnd();
		else
			floorManager->SendCleaningOceanLevelEnd();
		return;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Recv %d"), 1));
		//SetSideType();
		//bThreshold = true;
	}

}
void AWhaleCharacter::SendSideTypeToServer()
{
	//UCleaningOceanWallManager* Manager = GetWorld()->GetSubsystem<UCleaningOceanWallManager>();
	//if (Manager)
	//{
	//	Manager->SendFloorSpawnTypeToServer();
	//}
	
}
void AWhaleCharacter::SetStartPoint(SIDE_TYPE _type)
{	
	SideType = _type;
	switch (_type)
	{
	case SIDE_TYPE::LeftSide:
	{
		SetActorLocation(LeftSide_TargetPoint->GetActorLocation());
		//SetActorTransform(LeftSide_TargetPoint->GetActorTransform());
		UE_LOG(LogTemp, Log, TEXT("SIDE_TYPE::LeftSide:"));
	}
	break;
	case SIDE_TYPE::RightSide:
	{
		SetActorTransform(RightSide_TargetPoint->GetActorTransform());
		UE_LOG(LogTemp, Log, TEXT("SIDE_TYPE::RightSide:"));
	}
	break;
	default:
		break;
	}
}

void AWhaleCharacter::SetSideType(SIDE_TYPE _type)
{
	//좌, 우 사이드 결정
	SideType = _type;
	// <<-------------------------------------------------- 여긴 이제 필요없을 듯 함
	//switch (_type)
	//{
	//case SIDE_TYPE::LeftSide:
	//{
	//	TargetPoint = LeftSide_TargetPoints[0];
	//}
	//	break;
	//case SIDE_TYPE::RightSide:
	//{
	//	TargetPoint = RightSide_TargetPoints[0];
	//}
	//	break;
	//default:
	//	break;
	//}

	////if(isA)
	//MoveObject();
	// >>--------------------------------------------------
}

//FVector AWhaleCharacter::GetTargetLocation()
//{
//	if (bThreshold == false)
//	{
//		vTargetLocation = TargetPoints[0]->GetActorLocation();
//	}
//	else
//	{
//		vTargetLocation = TargetPoints[0]->GetActorLocation();
//	}
//	return vTargetLocation;
//}

//void AWhaleCharacter::FindNextTarget()
//{
//	if (bThreshold == false && CurrentTargetIndex < EndWayPointIndex)
//	{
//		if (TargetPoints.Num() - 1 > CurrentTargetIndex)
//		{
//			CurrentTargetIndex += 1;
//		}
//	}
//}
void AWhaleCharacter::SendSideType_Implementation()
{
	wallManager->SendWallSpawnWhaleEnd();
}
void AWhaleCharacter::SendCleaningOceanLevelEnd()
{
	floorManager->SendCleaningOceanLevelEnd();
}
void AWhaleCharacter::ChaseTarget(float DeltaTime)
{
	CheckThreshold();
	FVector MyLocation = GetActorLocation();
	FVector TargetLocation = TargetPoint->GetActorLocation();
	FVector LookVector = (TargetLocation - MyLocation).GetSafeNormal();

	float fSpeed = 700.f;
	FVector NewLocation = MyLocation + fSpeed * DeltaTime * LookVector;
	SetActorLocation(NewLocation);
	LookAt(DeltaTime);
}

//void AWhaleCharacter::Floor_ChaseTarget(float DeltaTime)
//{
//	FVector MyLocation = GetActorLocation();
//	FVector TargetLocation = TargetPoint->GetActorLocation();
//	FVector LookVector = (TargetLocation - MyLocation).GetSafeNormal();
//
//	float fSpeed = 700.f;
//	FVector NewLocation = MyLocation + fSpeed * DeltaTime * LookVector;
//	SetActorLocation(NewLocation);
//	Floor_LookAt(DeltaTime);
//}

void AWhaleCharacter::LookAt(float DeltaTime)
{
	FQuat MyRotation = GetActorQuat();
	
	//if (bThreshold == true)
	//{
	//	CurrentTargetIndex = SideTypeIndex;
	//}
	FQuat TargetRotation = TargetPoint->GetActorQuat();

	double RotationSpeed = 0.13f * DeltaTime;

	FQuat InterpRotation = FQuat::Slerp(MyRotation, TargetRotation, RotationSpeed);

	SetActorRotation(InterpRotation);
}

//void AWhaleCharacter::Floor_LookAt(float DeltaTime)
//{
//	FQuat MyRotation = GetActorQuat();
//		
//	FQuat TargetRotation = TargetPoint->GetActorQuat();
//
//	double RotationSpeed = 0.13f * DeltaTime;
//
//	FQuat InterpRotation = FQuat::Slerp(MyRotation, TargetRotation, RotationSpeed);
//
//	SetActorRotation(InterpRotation);
//}



//void AWhaleCharacter::GetTargetPoints()
//{
//	//왼 오 조건을 추가해야 함
//	TArray<AActor*> FoundSpawnPoints;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), FoundSpawnPoints);
//	TargetPoints.Empty();
//	for (int i = 0; i < FoundSpawnPoints.Num(); ++i)
//	{
//		ATargetPoint* TargetPoint = Cast<ATargetPoint>(FoundSpawnPoints[i]);
//		TargetPoints.Add(TargetPoint);
//	}
//}

