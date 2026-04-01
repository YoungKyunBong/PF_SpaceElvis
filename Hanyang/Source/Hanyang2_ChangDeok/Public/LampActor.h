// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LampActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class HANYANG2_CHANGDEOK_API ALampActor : public AActor
{
	GENERATED_BODY()

public:
	UMaterialInstanceDynamic* GetChangeMeshDynIns() { return LampMesh->CreateDynamicMaterialInstance(0); }

	UMaterialInstanceDynamic* GetChangeMeshDynIns_M2() { return LampMesh->CreateDynamicMaterialInstance(1); }

	UFUNCTION(BlueprintNativeEvent)
	void LightOff();
	UFUNCTION(BlueprintCallable)
	virtual void LightOff_Implementation() { LightOff(); }

	UFUNCTION(BlueprintNativeEvent)
	void LightOn();
	UFUNCTION(BlueprintCallable)
	virtual void LightOn_Implementation(){ LightOn(); }

protected:
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* LampMesh;
};
