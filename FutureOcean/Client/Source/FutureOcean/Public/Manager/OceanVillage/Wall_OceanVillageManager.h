

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "Containers/Map.h"
#include "../Protocols.h"
#include "Wall_OceanVillageManager.generated.h"

/**
 *
 */
class AGuideActor;
class AGuideTargetActor;
class ATextureFishCharacter;
class ATargetPoint;


USTRUCT(BlueprintType)
struct FFishInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	FFishInfo()
		: Name(TEXT("")), Path(TEXT("")), Index(0) {
	}

	FFishInfo(const FString& InName, const FString& InPath, int32 InIndex)
		: Name(InName), Path(InPath), Index(InIndex) {
	}
};
UCLASS()
class FUTUREOCEAN_API AWall_OceanVillageManager : public ADefaultManager
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type R);
	virtual	void C_Init() override;

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);
	UFUNCTION()
	void RecvGuideActorTargetChange(int _guideNum, int _targetActorNum);

	//UFUNCTION(BlueprintNativeEvent)
	UFUNCTION()
	void RecvFishActorTargetChange(int _fishNum, int _guideNum, bool IsFirst);
	//UFUNCTION(BlueprintCallable)
	//virtual void RecvFishActorTargetChange_Implementation(int _fishNum, int _guideNum, bool IsFirst);

	UFUNCTION()
	void RecvFishActorTransform(int _fishNum, FTransform _fishTransform);

	UFUNCTION()
	void RecvLoadPNG();

	virtual void SetCmsIsStart(bool isStart) override;

	TArray<AGuideTargetActor*> GetTargetActors();

	UFUNCTION(BlueprintCallable)
	void SendGuideActorTargetChange(int _guideNum, int _targetActorNum);

	UFUNCTION(BlueprintCallable)
	void SendFishActorTargetChange(int _fishNum, int _guideNum);

	inline void SendPlayEffectSound(EFFECT_SOUND_TYPE _type);

	UFUNCTION(BlueprintNativeEvent)
	void SetActors();
	UFUNCTION(BlueprintCallable)
	virtual void SetActors_Implementation() {}

	/*Get,Set*/
	FTimerHandle Get_FileSearchTimerHandle() { return FileSearchTimerHandle; }
	TArray<ATargetPoint*> Get_TargetPoints() { return TargetPoints; }
	FName Get_FishTagName() { return TagName; }
	UTexture2D* Get_CustomTexture() { return customMakeTexture; }
	void Set_CustomTexture() { customMakeTexture = nullptr; }
	FString Get_FullPath() { return FullPath; }

	virtual void Call_Intro_SQ_End() override;
	virtual void Call_DefaultLevelEnd() override;

protected:
	UFUNCTION(BlueprintCallable)
	void SetGuideActors(TArray<AGuideActor*> _guideActors);

	UFUNCTION(BlueprintCallable)
	void SetTargetActors(TArray<AGuideTargetActor*> _targetPointActors);

	UFUNCTION(BlueprintCallable) 
	void SetFishActors(TArray<ATextureFishCharacter*> _fishActors);

	UFUNCTION(BlueprintCallable)
	int SetFishActorToRandomGuideActor();
	UFUNCTION(BlueprintCallable)
	int SetFishActorToRandomGuideActor_ByTag(FName InDirTag);
	UFUNCTION()
	void StartFileSearchTimer();
	UFUNCTION()
	void SearchScannerFile();
	UFUNCTION()
	void SpawnActor(FString ActorPath, FName _TagName = NAME_None);	
	UFUNCTION()
	void FindSpawnPoints();

	UFUNCTION()
	FVector RandomLocation(const FVector& BaseLocation, float Radius, float Z_Radius);

	/*C++_Method*/
	UFUNCTION()
	bool CheckTxtFile();
	UFUNCTION()
	bool CheckJpgFile();
	/*UFUNCTION()
	UTexture2D* FiledToTexture2D();*/
	UFUNCTION()
	void FoundSpawnFish(FString _QRText, FString PngPath);

private:
	UPROPERTY()
	TMap<int, AGuideActor*> GuideActors;
	UPROPERTY()
	TMap<int, ATextureFishCharacter*> FishActors;
	UPROPERTY()
	TMap<int, AGuideTargetActor*> TargetPointActors;

	bool isFirstPlay;
	bool bTxtFileChecked;

	UPROPERTY()
	TArray<int32> AvailableGuideIndex;		// 사용 가능한 GuideActor의 인덱스
	
	TMap<FName, TArray<int32>> AvailableGuideIndexMap;
	UPROPERTY()
	TArray<FFishInfo> FishInfos;
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
	FString LatestPngPath;
	UPROPERTY()
	FName TagName;

	UPROPERTY()
	TObjectPtr<UTexture2D> customMakeTexture = nullptr;
	UPROPERTY()
	TObjectPtr<ATextureFishCharacter> SpawnedActor;
	UPROPERTY()
	TArray<FVector> SpawnPoints;
	UPROPERTY()
	TArray<int32> ApplyCount;
	UPROPERTY()
	TArray<FName> DirTagName;
	UPROPERTY()
	int32 DirIndex = 0;
	UPROPERTY()
	TArray<TObjectPtr<ATargetPoint>> TargetPoints;
	UPROPERTY()
	FTimerHandle FileSearchTimerHandle;
	UPROPERTY()
	TSet<FString> LoadingPaths;

	int32  CurrentSpawnIndex = 0;
    const int32 NumFishTypes = 15;  
    const float FileSearchInterval = 5.0f;	
};
