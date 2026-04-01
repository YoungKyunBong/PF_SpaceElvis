

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrashActor.generated.h"

UCLASS()
class FUTUREOCEAN_API ATrashActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrashActor();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void Init();
	UFUNCTION(BlueprintCallable)
	void TempSetMesh(UMaterialInterface* _DefaultWidgetClass);
	UFUNCTION(BlueprintCallable)
	void DestroyActor();

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> SMC_TrashActor{ nullptr };
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> TempMesh{ nullptr };
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> MInsDyns{ nullptr };
	UPROPERTY()
	TObjectPtr<class UGameInstance> GameInstance = { nullptr };

	int32 MaterialCount = 0;
};
