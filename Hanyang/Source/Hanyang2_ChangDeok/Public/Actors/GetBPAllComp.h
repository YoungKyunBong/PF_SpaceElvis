// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GetBPAllComp.generated.h"

UCLASS()
class HANYANG2_CHANGDEOK_API AGetBPAllComp : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<UStaticMeshComponent*> MyComponents;

public:
	UFUNCTION(BlueprintNativeEvent)
	void Init();
	UFUNCTION(BlueprintCallable)
	virtual void Init_Implementation() {}

	TArray<UStaticMeshComponent*> GetCompCount() { return MyComponents; }
};
