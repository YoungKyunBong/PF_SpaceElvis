#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OceanVillageGameMode.generated.h"

class ATargetPoint;
class ATextureFishCharacter;
/**
 *
 */
UCLASS()
class FUTUREOCEAN_API AOceanVillageGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void init();
	UFUNCTION(BlueprintCallable)
	AActor* AssignRandomGuide(AActor* FishActor);

public:
	/*Get,Set*/
	FTimerHandle Get_FileSearchTimerHandle() { return FileSearchTimerHandle; }
	TArray<ATargetPoint*> Get_TargetPoints() { return TargetPoints; }
	FName Get_FishTagName() { return TagName; }
	UTexture2D* Get_CustomTexture() { return customMakeTexture; }
	void Set_CustomTexture() { customMakeTexture = nullptr; }
	FString Get_FullPath() { return FullPath; }

protected:
	/*BlueprintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	void StartFileSearchTimer();
	UFUNCTION(BlueprintCallable)
	void SearchScannerFile();

protected:
	/*C++_Method*/
	UFUNCTION()
	bool CheckNewFile();
	UFUNCTION()
	UTexture2D* FiledToTexture2D();
	UFUNCTION()
	void GetPixelColor(UTexture2D* Texture);
	void FoundSpawnFish(FString _QRText);

	UFUNCTION(BlueprintCallable)
	void SpawnActor(FString ActorPath, FName _TagName = NAME_None);

	void FindSpawnPoints();
	FVector RandomLocation(const FVector& BaseLocation, float Radius, float Z_Radius);


private:
	UPROPERTY()
	FTimerHandle FileSearchTimerHandle;
	UPROPERTY()
	FVector RightSpawnLocation;
	UPROPERTY()
	FVector LeftSpawnLocation;
	UPROPERTY()
	FRotator SpawnRotator;
	UPROPERTY()
	FString ReadFilePath;
	UPROPERTY()
	FString FullPath;
	UPROPERTY()
	FString QRText;
	UPROPERTY()
	FName TagName;

private:
	UPROPERTY()
	TObjectPtr<UTexture2D> customMakeTexture = nullptr;
	UPROPERTY()
	TObjectPtr<ATextureFishCharacter> SpawnedActor;

	TArray<int32> ApplyCount;
	UPROPERTY()
	TArray<TObjectPtr<ATargetPoint>> TargetPoints;

	TArray<int32> AvailableGuideIndex;		// 사용 가능한 GuideActor의 인덱스
	// Fish와 GuideActor 배열
	UPROPERTY()
	TArray<TObjectPtr<AActor>> FishActors;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> GuideActors;
};
