#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "CleaningOilActor.generated.h"

UCLASS()
class FUTUREOCEAN_API ACleaningOilActor : public APawn
{
	GENERATED_BODY()


public:
	/*BlueprintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	void Init(AFloor_KelpForestManager* _manager);
	UFUNCTION(BlueprintCallable)
	void ChangeOpValue();
	UFUNCTION(BlueprintNativeEvent)
	void EndOverlap();
	UFUNCTION(BlueprintCallable)
	virtual void EndOverlap_Implementation() {}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UDecalComponent> DC_CleaningOil;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> C_Trigger;

	void SetCollisionInteractionMesh(ECollisionEnabled::Type _collisionChannel);

	UFUNCTION(BlueprintNativeEvent)
	void PlayCleaningSound();
	UFUNCTION(BlueprintCallable)
	virtual void PlayCleaningSound_Implementation() {}

	inline void SetOverlap(bool isA) { bOverlap = isA; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* NiagaraEffect;

private:
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> MInsDyn;
	UPROPERTY()
	TObjectPtr<class UGameInstance> GameInstance = { nullptr };
	UPROPERTY()
	TObjectPtr<class UCleaningOilManager> CleaningOilManager = { nullptr };
	UPROPERTY()
	TObjectPtr<class AFloor_KelpForestManager> FloorManager = { nullptr };

public:
	UPROPERTY(EditAnywhere)
	float OpValue = 1.0f;
	UPROPERTY(EditAnywhere)
	float OpChangeValue = 0.1f;

	UPROPERTY(BlueprintReadOnly)	
	bool bOverlap = true;
};
