

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuideActor.generated.h"

class AWall_OceanVillageManager;
class AGuideTargetActor;
class USceneComponent;

UCLASS()
class FUTUREOCEAN_API AGuideActor : public AActor
{
	GENERATED_BODY()
public:
	inline void SetMyNum(int _myNum) { myNum = _myNum; }
	inline int GetMyNum() { return myNum; }

	void CustomInit(AWall_OceanVillageManager* _manager);

	void SetChangeTarget(AGuideTargetActor* _currTargetActor);

	UFUNCTION(BlueprintNativeEvent)
	void IsMove(bool isStart);
	UFUNCTION(BlueprintCallable)
	virtual void IsMove_Implementation(bool isStart);

	void CustomStartTimer();
	UFUNCTION()	
	void ChangeTargetPoint();
protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetHoming(USceneComponent* _targetPoint);
	UFUNCTION(BlueprintCallable)
	virtual void SetHoming_Implementation(USceneComponent* _targetPoint) {}

private:
	int myNum;
	AWall_OceanVillageManager* wallManager;

	bool isFirstPlay;

	FTimerHandle MainHandle;
	

	TArray<int32> AvailableIndex;
	void GetRandomArrayItemNoRepeat(const TArray<AGuideTargetActor*>& Array, TArray<int32>& _AvailableIndex);

	//AGuideTargetActor* currTargetActor;
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ZoneTag = "Left";
};
