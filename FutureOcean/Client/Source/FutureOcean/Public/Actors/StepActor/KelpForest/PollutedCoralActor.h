

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Protocols.h"
#include "PollutedCoralActor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UPollutedCoralManager;

UCLASS()
class FUTUREOCEAN_API APollutedCoralActor : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void ChangeOpValue(int32 _OilCount);
	UFUNCTION(BlueprintCallable)
	void Init(AWall_KelpForestManager* _manager);
protected:
	/*BlueprintCallable_Method*/	
	UFUNCTION(BlueprintCallable)
	void TempSetMesh(UMaterialInterface* _DefaultWidgetClass);


protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> SMC_PollutedCoral;

public:
	/*Editer*/
	UPROPERTY(EditAnywhere, Category = "ParameterValue")
	float OpValue = 0.3f;
	UPROPERTY(EditAnywhere, Category = "ParameterValue")
	float OpChangeValue = 0.10f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> TempMesh;

	
	UPROPERTY(BlueprintReadWrite)
	FName ParameterName;
private:
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MInsDyns;
	UPROPERTY()
	TObjectPtr<class UGameInstance> GameInstance = { nullptr };
	UPROPERTY()
	TObjectPtr<class AWall_KelpForestManager> WallManager = { nullptr };

	int32 MaterialCount = 0;
	int32 OilActorCount = 0;
	

};
