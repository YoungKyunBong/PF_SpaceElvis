

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorCushionActor.generated.h"

UCLASS()
class FUTUREOCEAN_API AFloorCushionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorCushionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
