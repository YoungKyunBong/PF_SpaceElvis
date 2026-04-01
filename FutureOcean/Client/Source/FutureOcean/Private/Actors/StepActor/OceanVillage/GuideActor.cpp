
#include "Actors/StepActor/OceanVillage/GuideActor.h"
#include "Manager/OceanVillage/Wall_OceanVillageManager.h"
#include "Actors/StepActor/OceanVillage/GuideTargetActor.h"

void AGuideActor::CustomInit(AWall_OceanVillageManager* _manager)
{
	wallManager = _manager;
	//GetWorldTimerManager().SetTimer(MainHandle, this, &AGuideActor::ChangeTargetPoint, 5.0f, true);
}

void AGuideActor::SetChangeTarget(AGuideTargetActor* _currTargetActor)
{
	SetHoming(_currTargetActor ? _currTargetActor->GetRootComponent() : nullptr);
}

void AGuideActor::IsMove_Implementation(bool isStart)
{
	if (isStart)
		GetWorldTimerManager().UnPauseTimer(MainHandle);
	else
	{
		GetWorldTimerManager().PauseTimer(MainHandle);
	}
}

void AGuideActor::CustomStartTimer()
{
	GetWorldTimerManager().SetTimer(MainHandle, this, &AGuideActor::ChangeTargetPoint, 5.0f, true);
}

void AGuideActor::ChangeTargetPoint()
{
	//GetRandomArrayItemNoRepeat(wallManager->GetTargetActors(), AvailableIndex);
	TArray<AGuideTargetActor*> AllTargets = wallManager->GetTargetActors();
	TArray<AGuideTargetActor*> FilteredTargets;

	for (AGuideTargetActor* Target : AllTargets)
	{
		if (!Target) continue;

		// GuideActor의 Tags 중 하나라도 Target의 Tags에 포함되어 있으면 통과
		for (const FName& MyTag : Tags)
		{
			if (Target->Tags.Contains(MyTag))
			{
				FilteredTargets.Add(Target);
				break;
			}
		}
	}

	GetRandomArrayItemNoRepeat(FilteredTargets, AvailableIndex);
}

void AGuideActor::GetRandomArrayItemNoRepeat(const TArray<class AGuideTargetActor*>& Array, TArray<int32>& _AvailableIndex)
{
	// 배열이 비어있으면 nullptr 반환
	if (Array.Num() == 0)
	{
		return;
	}
	//Array[0]->Tags.Contains(TEXT("Left"));
	// 사용 가능한 인덱스 초기화
	if (_AvailableIndex.Num() == 0)
	{
		_AvailableIndex.Reserve(Array.Num());
		for (int32 i = 0; i < Array.Num(); ++i)
		{
			_AvailableIndex.Add(i);
		}
	}

	// 랜덤으로 인덱스 선택
	int32 RandomIndex = FMath::RandRange(0, _AvailableIndex.Num() - 1);
	int32 SelectedIndex = _AvailableIndex[RandomIndex];

	// 선택된 인덱스 제거
	_AvailableIndex.RemoveAt(RandomIndex);

	// 선택된 항목 반환
	//UE_LOG(LogTemp, Log, TEXT("Selected Index: %d"), SelectedIndex);
	wallManager->SendGuideActorTargetChange(myNum, Array[SelectedIndex]->GetMyNum());
	
}
