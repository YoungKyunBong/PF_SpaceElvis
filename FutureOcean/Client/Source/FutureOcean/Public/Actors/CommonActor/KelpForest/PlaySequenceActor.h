

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Protocols.h"
#include "PlaySequenceActor.generated.h"

UCLASS()
class FUTUREOCEAN_API APlaySequenceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	void CustomInit(class ADefaultManager* _manager);

	UFUNCTION(BlueprintNativeEvent)
	void PlaySequence(Lv_Sq_Type _type);
	UFUNCTION(BlueprintCallable)
	virtual void PlaySequence_Implementation(Lv_Sq_Type _type);

	UFUNCTION(BlueprintNativeEvent)
	void CustomStopSequence();
	UFUNCTION(BlueprintCallable)
	virtual void CustomStopSequence_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void CustomClearSequence();
	UFUNCTION(BlueprintCallable)
	virtual void CustomClearSequence_Implementation() {}

	UFUNCTION(BlueprintCallable)
	void Call_OilLevelEnd();

	UPROPERTY(EditAnywhere)
	bool IsWall;

private:
	class ADefaultManager* wallManager;
	Lv_Sq_Type currType;

};
