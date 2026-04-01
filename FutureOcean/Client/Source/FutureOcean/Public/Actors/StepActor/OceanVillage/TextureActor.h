

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextureActor.generated.h"

UCLASS()
class FUTUREOCEAN_API ATextureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextureActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
