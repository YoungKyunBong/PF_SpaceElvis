

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "LightCaliActor.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class FUTUREOCEAN_API ALightCaliActor : public AActor
{
	GENERATED_BODY()

public:
	ALightCaliActor();
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "CustoRotation")
	void ApplyRotationSensitivity(float Sensitivity);

	UFUNCTION(BlueprintNativeEvent)
	void SphereTrace();
	UFUNCTION(BlueprintCallable)
	virtual void SphereTrace_Implementation() {}

	UFUNCTION(BlueprintCallable, Category = "Trace")
	bool SphereTraceCamouFish(FHitResult& OutHit, AActor*& OutHitActor, FColor TraceColor = FColor::Red, FColor TraceHitColor = FColor::Green, float DrawTime = 5.f);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float fRot_Sensitivity = 0.45f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float TraceDistance = 10000.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float TraceRadius = 250.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_GameTraceChannel1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> TargetArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LightAim;
};
