#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Protocols.h"
#include "InteractionActor.generated.h"

class AFloor_CoralForestManager;

UCLASS()
class FUTUREOCEAN_API AInteractionActor : public AActor
{
	GENERATED_BODY()

public:
	/*C++_Method*/
	void DepthSwitch(bool bEnable = false);
	void VisibilitySwitch(bool bEnable = false);

	void Init(AFloor_CoralForestManager* _manager);

	void SetCollisionInteractionMesh(ECollisionEnabled::Type _collisionChannel);
protected:
	/*BlueprintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	void TempSetMesh();
	UFUNCTION(BlueprintCallable)
	bool Get_GrabActor(AActor* _OtherACtor);
	UFUNCTION(BlueprintCallable)
	void BeginOverlapFlow(AActor* _OtherACtor, UMaterialInterface* _DefaultWidgetClass);

	/*C++_Method*/
	UFUNCTION()
	void DestroyActor();

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> InteractionActor;

	UPROPERTY(BlueprintReadWrite)
	class UBoxComponent* C_Trigger;

public:
	/*Editer*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMesh> TempMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AFlagCoralActor> FlagCoralActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class AGrabActor> GrabActor;
	UPROPERTY()
	TObjectPtr<class UInteractionManager> InteractionActorManager = { nullptr };
	UPROPERTY(EditAnywhere)
	CORAL_TYPE CoralType;

private:
	AFloor_CoralForestManager* floorManager;
};
