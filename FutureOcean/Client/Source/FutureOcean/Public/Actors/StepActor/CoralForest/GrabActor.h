#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabActor.generated.h"

class UStaticMeshComponent;
class ACoralPawn;

UCLASS()
class FUTUREOCEAN_API AGrabActor : public AActor
{
	GENERATED_BODY()

public:
	void Detach_Actor();

protected:
	/*BluePrintCallable_Method*/
	UFUNCTION(BlueprintCallable)
	void TempSetMesh();
	UFUNCTION(BlueprintCallable)
	void Get_CharacterActor(AActor* _OtherACtor);
	UFUNCTION(BlueprintCallable)
	void Attach_Actor();
	UFUNCTION(BlueprintCallable)
	void BeginOverlapFlow(AActor* _OtherACtor);

	/*C++_Method*/
	bool Check_Forward();
	void DestroyActor();


protected:
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* GrabActor;
	UPROPERTY()	
	ACoralPawn* CoralPawn;

	int MaterialCount = 0;
public:
	/*Editer*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMesh> TempMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AInteractionActor> InteractionActor;


};
