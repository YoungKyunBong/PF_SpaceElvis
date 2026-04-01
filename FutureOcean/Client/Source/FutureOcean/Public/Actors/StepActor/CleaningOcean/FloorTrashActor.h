

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Protocols.h"
#include "FloorTrashActor.generated.h"

class AFloor_CleaningOceanManager;

UCLASS()
class FUTUREOCEAN_API AFloorTrashActor : public AActor
{
	GENERATED_BODY()
	
public:	
	void Init(AFloor_CleaningOceanManager* _manager);

	UFUNCTION(BlueprintCallable)
	void ChangeOpValue();
	UFUNCTION(BlueprintCallable)
	bool GetPlaySound() { return bPlaySound; }
	int32 GetClearTrash() { return ClearTrash; }

	UFUNCTION(BlueprintNativeEvent)
	void CustomSetActorLocation();
	UFUNCTION(BlueprintCallable)
	virtual void CustomSetActorLocation_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void NS_CleanClear();
	UFUNCTION(BlueprintCallable)
	virtual void NS_CleanClear_Implementation() {}

	inline void SetOverlap(bool isA) { isStart = isA; }
protected:
	UFUNCTION(BlueprintCallable)
	void TempSetMesh(UMaterialInterface* _DefaultWidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline AFloor_CleaningOceanManager* GetFloorManager() { return floorManager; }
	//UFUNCTION()
	//void GetAmbientSounds();
	//UFUNCTION()
	//void PlaySound();
	//UFUNCTION()
	//void SendToServer();
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> SMC_FloorTrash;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> TempMesh;
	//UPROPERTY(EditAnywhere)
	//TObjectPtr<class AWhaleCharacter> Whale;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AAmbientSound>> SoundActors;
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MInsDyns;

	UPROPERTY(BlueprintReadWrite)
	class USphereComponent* C_Trigger;

	UPROPERTY(BlueprintReadOnly)
	bool isStart;

	bool bOverlap = false;
	bool bPlaySound = false;
	int32 MaterialCount = 0;
	int32 ClearTrash = 0;
	UPROPERTY(EditAnywhere)
	float OpValue = 1.0f;
	UPROPERTY(EditAnywhere)
	float OpChangeValue = 0.10f;

private:
	AFloor_CleaningOceanManager* floorManager;
};
