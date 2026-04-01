#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TextureFishCharacter.generated.h"

class UTexture2D;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class AWall_OceanVillageManager;
class USkeletalMeshComponent;
class UFishAsyncTexLoader;

UCLASS()
class FUTUREOCEAN_API ATextureFishCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATextureFishCharacter();
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type Reason);

	UFUNCTION()
	inline void SetMyNum(int _myNum) { myNum = _myNum; }
	UFUNCTION()
	inline int GetMyNum() { return myNum; }

public:
	UFUNCTION(BlueprintNativeEvent)
	void CustomInit(AWall_OceanVillageManager* _manager);
	UFUNCTION(BlueprintCallable)
	virtual void CustomInit_Implementation(AWall_OceanVillageManager* _manager);
	UFUNCTION(BlueprintNativeEvent)
	void SpawnFishEffect();
	UFUNCTION(BlueprintCallable)
	virtual void SpawnFishEffect_Implementation() {}
	UFUNCTION(BlueprintNativeEvent)
	void ApplyMaterialEffect();
	UFUNCTION(BlueprintCallable)
	virtual void ApplyMaterialEffect_Implementation() {}


	UFUNCTION()
	void SetTargetPoints(TArray<ATargetPoint*> Points);

public:
	/*BluePrintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	AActor* RandomPoint(TArray<AActor*> PointActors);
	UFUNCTION()
	void ApplyMaterial(const FString& InPngPath);
	UFUNCTION()
	void OnTextureReady(UTexture2D* Texture, FName TagName, FString Error);


public:
	UFUNCTION()
	AActor* GetRandomArrayItemNoRepeat(const TArray<AActor*>& Array, TArray<int32>& _AvailableIndex);

	UFUNCTION()
	void SetChangeTarget_ToFish(class AGuideActor* _currTargetActor);

	UFUNCTION(BlueprintNativeEvent)
	void IsMove(bool isStart);
	UFUNCTION(BlueprintCallable)
	virtual void IsMove_Implementation(bool isStart) {}

protected:
	/*C++_Method*/
	UFUNCTION()
	void SetTempMaterial(UTexture2D* Texture);
	UFUNCTION()
	void Delete_Texture();
	UFUNCTION()
	void TimerControl();

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetHoming(USceneComponent* _targetPoint);
	UFUNCTION(BlueprintCallable)
	virtual void SetHoming_Implementation(USceneComponent* _targetPoint) {}

protected:
	/*Set_Blueprint*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> TextureObejct;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> customMakeTexture;
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MInsDyns;
	UPROPERTY()
	TObjectPtr<AWall_OceanVillageManager> CastGameMode;
	UPROPERTY()
	TArray<TObjectPtr<class ATargetPoint>> TargetPoints;


	UPROPERTY(BlueprintReadOnly)
	bool bApplyMaterial = false;

	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	FName FishTagName;
	UPROPERTY()
	TArray<int32> AvailableIndex;

	FString FullPath;
	int32 LastIndex = -1;
	int32 myNum;
	int32 CurrentTargetIndex = 0;

	UPROPERTY()   //GC 가 캐릭터가 죽을 때까지 보존 TextureFishCharacter.h
	TObjectPtr<UTexture2D> RuntimeTex = nullptr;
	UPROPERTY()
	TObjectPtr<UFishAsyncTexLoader> RuntimeLoader = nullptr;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bSpawnFish = false;
};
