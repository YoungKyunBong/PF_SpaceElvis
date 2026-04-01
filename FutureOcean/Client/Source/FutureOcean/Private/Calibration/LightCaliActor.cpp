#include "Calibration/LightCaliActor.h"
#include "Components/ArrowComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include <LiveLinkComponentController.h>
// Sets default values
ALightCaliActor::ALightCaliActor()
{
	PrimaryActorTick.bCanEverTick = true;    
}

// Called when the game starts or when spawned
void ALightCaliActor::BeginPlay()
{
	Super::BeginPlay(); 
    TargetArrow = FindComponentByClass<UArrowComponent>();
    LightAim = FindComponentByClass<UStaticMeshComponent>();
   
}

// Called every frame
void ALightCaliActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ApplyRotationSensitivity(fRot_Sensitivity);
    SphereTrace();
}

void ALightCaliActor::ApplyRotationSensitivity(float Sensitivity)
{
    // 현재 회전값 얻기
    FRotator CurrentRot = GetActorRotation();

    // 감도 적용
    float NewPitch = CurrentRot.Pitch * fRot_Sensitivity;
    float NewYaw = CurrentRot.Yaw * fRot_Sensitivity;
    float NewRoll = 0.0f; 
    // float NewRoll = CurrentRot.Roll * fRot_Sensitivity;


    FRotator NewRot = FRotator(NewPitch, NewYaw, NewRoll);

    // 회전 적용
    SetActorRotation(NewRot);
}


bool ALightCaliActor::SphereTraceCamouFish(FHitResult& OutHit, AActor*& OutHitActor, FColor TraceColor, FColor TraceHitColor, float DrawTime)
{
    OutHitActor = nullptr;
    if (!TargetArrow) return false;
    
    FVector Start = GetActorLocation();
    FVector Dir = GetActorForwardVector();
    FVector End = Start + (Dir * TraceDistance);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.bTraceComplex = false;

    // Sphere Trace    
    bool bHit = GetWorld()->SweepSingleByChannel(
        OutHit,
        Start,
        End,
        FQuat::Identity,
        ECC_GameTraceChannel1, // CamouFish 채널
        FCollisionShape::MakeSphere(TraceRadius),
        Params 
    );

    // 디버그 라인
    /*FColor LineColor = bHit ? TraceHitColor : TraceColor;
    DrawDebugLine(GetWorld(), Start, End, bHit ? TraceHitColor : TraceColor, false, 0.025f, 0, 1.f);*/
    
    //  디버그 캡슐
    /*FVector CapsuleCenter = (End + Start) * 0.5f;
    FVector CapsuleDirection = (End - Start).GetSafeNormal();
    FRotator CapsuleRotation = FRotationMatrix::MakeFromZ(CapsuleDirection).Rotator();

    float HalfHeight = (End - Start).Size() * 0.5f;
	float CapsuleRadius = TraceRadius;
    DrawDebugCapsule(
        GetWorld(),
        CapsuleCenter,
        HalfHeight,
        TraceRadius,
        CapsuleRotation.Quaternion(),
        bHit ? TraceHitColor : TraceColor,
        false,
        0.05f,
        0,
        1.0f
    );*/

    // 디버그 스피어 그리기 (충돌 지점)
    if (bHit)
    {
        //DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, TraceRadius, 12, FColor::Red, false, 0.05f);
        OutHitActor = OutHit.GetActor();
       
    }
    if (bHit && OutHit.GetActor())
    {
        OutHitActor = OutHit.GetActor();
        LightAim->SetWorldLocation(OutHit.ImpactPoint);
        LightAim->SetVisibility(false);
    }
    else
    {       
        LightAim->SetWorldLocation(Start + (Dir * 700.f));
        LightAim->SetVisibility(false);
    }

    return bHit;    
}

