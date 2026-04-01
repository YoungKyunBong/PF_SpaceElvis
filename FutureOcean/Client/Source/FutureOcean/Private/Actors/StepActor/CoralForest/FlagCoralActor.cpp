
#include "Actors/StepActor/CoralForest/FlagCoralActor.h"
#include "Manager/KelpForest/FlagActorManager.h"
#include "Manager/GameManager.h"

#include "Manager/CoralForest/Wall_CoralForestManager.h"
#include "Curves/CurveFloat.h"
#include <Kismet/GameplayStatics.h>

AFlagCoralActor::AFlagCoralActor()
{
	PrimaryActorTick.bCanEverTick = false;
	FadeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeTimeline"));
	WhiteTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("WhiteTimeline"));
	SpringTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpringTimeline")); // 추가
}

void AFlagCoralActor::BeginPlay()
{
	Super::BeginPlay();

	MInsDyn = FlagMeshComponent->CreateDynamicMaterialInstance(0);
	CurLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	// Bind update delegate
	FadeTimelineCallback.BindUFunction(this, FName("HandleFadeUpdate"));
	WhiteTimelineCallback.BindUFunction(this, FName("HandleWhiteUpdate"));
	// Bind finished delegate
	FadeTimelineFinishedCallback.BindUFunction(this, FName("HandleFadeFinished"));
	WhiteTimelineFinishedCallback.BindUFunction(this, FName("HandleWhiteFinished"));

	// 추가 스프링 타임라인 콜백 바인딩
	SpringScaleXCallback.BindUFunction(this, FName("HandleSpringScaleZ"));
	SpringScaleYCallback.BindUFunction(this, FName("HandleSpringScaleY"));
	SpringRotationCallback.BindUFunction(this, FName("HandleSpringRotation"));
	SpringTimelineFinishedCallback.BindUFunction(this, FName("HandleSpringFinished"));

	// 초기 트랜스폼 저장
	OriginalScale = FlagMeshComponent->GetRelativeScale3D();
	//OriginalRotation = GetRootComponent()->GetRelativeRotation();
	OriginalRotation = FlagMeshComponent->GetRelativeRotation();
	if (CoralType != CORAL_TYPE::type7)
	{
		//FlagMeshComponent->SetRelativeScale3D(FVector(0.f, 0.f, 0.f));
		FlagMeshComponent->SetVisibility(false);		
	}
	else
	{
		MInsDyn->SetScalarParameterValue("White_Color", 1.0f); // 석화		
		MInsDyn->SetScalarParameterValue("incolor", 1.0f);
	}	
}

void AFlagCoralActor::Init(AWall_CoralForestManager* _manager)
{
	
	coralManager = _manager;
	
}

void AFlagCoralActor::TempSetMesh()
{
	// Construction시점에 메시 적용
	FlagMeshComponent->SetStaticMesh(TempMesh);
	FlagMeshComponent->SetMaterial(0, DefaultWidgetClass);
}

void AFlagCoralActor::FadeSwitch()
{
	if (bFade == true)
	{
		return;
	}

	float playrate = 1.f / TimetoFade;
	FadeTimeline->SetLooping(false);

	FadeTimeline->AddInterpFloat(FadeCurve, FadeTimelineCallback);
	FadeTimeline->SetTimelineFinishedFunc(FadeTimelineFinishedCallback);
	FadeTimeline->SetPlayRate(playrate);

	FadeTimeline->PlayFromStart();
	
}

void AFlagCoralActor::WhiteSwitch()
{
	float playrate = 1.f / TimetoWhite;
	WhiteTimeline->SetLooping(false);

	WhiteTimeline->AddInterpFloat(WhiteCurve, WhiteTimelineCallback);
	WhiteTimeline->SetTimelineFinishedFunc(WhiteTimelineFinishedCallback);
	WhiteTimeline->SetPlayRate(playrate);

	WhiteTimeline->PlayFromStart();
	UE_LOG(LogTemp, Warning, TEXT("WhiteSwitch_Play"));
}

void AFlagCoralActor::PlaySpringEffect()
{
	// 타임라인 설정
	SpringEffectDuration = FMath::FRandRange(5.f, 12.5f);
	float PlayRate = 1.0f / SpringEffectDuration;
	SpringTimeline->SetLooping(false);

	// X축 스케일 커브 추가 (이 커브는 에디터에서 생성해야 함)
	if (SpringScaleXCurve)
	{
		SpringTimeline->AddInterpFloat(SpringScaleXCurve, SpringScaleXCallback);
	}

	SpringTimeline->SetTimelineFinishedFunc(SpringTimelineFinishedCallback);
	SpringTimeline->SetPlayRate(PlayRate);

	// 타임라인 재생 시작
	SpringTimeline->PlayFromStart();
	SpawnAnimSequence();
	
}

void AFlagCoralActor::PlayNiagaraEffect()
{
	/*if (NiagaraEffectComponent_Barrier)
	{
		NiagaraEffectComponent_Barrier->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NiagaraEffectComponent_Barrier is not set!"));
	}*/
	if (NiagaraEffectComponent_Bomb)
	{
		NiagaraEffectComponent_Bomb->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NiagaraEffectComponent_Barrier is not set!"));
	}
}

void AFlagCoralActor::HandleFadeUpdate(float Value)
{
	if (MInsDyn)
	{
		MInsDyn->SetScalarParameterValue("Fade_Out", Value); // 투명화 풀림
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("MInsDyn nullptr."));
	}
	if (bFade == false)
	{
		bFade = true;
		UE_LOG(LogTemp, Log, TEXT("Fade timeline Update."));
	}
}

void AFlagCoralActor::HandleWhiteUpdate(float Value)
{
	if (CoralType == CORAL_TYPE::type7)
	{
		MInsDyn->SetScalarParameterValue("White_Color", Value); // 석화		
		MInsDyn->SetScalarParameterValue("incolor", Value);
		UE_LOG(LogTemp, Log, TEXT("White_Color Incolor Play."));
	}
}

void AFlagCoralActor::HandleSpringScaleZ(float Value)
{
	// 현재 스케일과 회전 가져오기
	//FVector CurrentScale = FlagMeshComponent->GetRelativeScale3D();

	// X축 스케일 업데이트 (길이 변화)
	//FlagMeshComponent->SetRelativeScale3D(FVector(CurrentScale.X, CurrentScale.Y, Value * OriginalScale.Z));	
	//FlagMeshComponent->SetRelativeScale3D(FVector(Value * OriginalScale.X, Value * OriginalScale.Y, Value * OriginalScale.Z));
}

void AFlagCoralActor::HandleSpringScaleY(float Value)
{
	// 현재 스케일과 회전 가져오기
	FVector CurrentScale = FlagMeshComponent->GetRelativeScale3D();

	// Y축 스케일 업데이트 (두께 변화)
	//FlagMeshComponent->SetRelativeScale3D(FVector(CurrentScale.X, Value * OriginalScale.Y, CurrentScale.Z));

}

void AFlagCoralActor::HandleSpringRotation(float Value)
{
	// 현재 스케일과 회전 가져오기	
	FRotator CurrentRotation = GetRootComponent()->GetRelativeRotation();
	//FRotator CurrentRotation = FlagMeshComponent->GetRelativeRotation();

	// Z축 회전 업데이트 (좌우 흔들림)
	//FlagMeshComponent->SetRelativeRotation(FRotator(CurrentRotation.Pitch , CurrentRotation.Yaw , OriginalRotation.Roll * Value * 10.f));
	//GetRootComponent()->SetRelativeRotation(FRotator(OriginalRotation.Pitch * Value, CurrentRotation.Yaw , CurrentRotation.Roll));
	//FlagMeshComponent->SetWorldRotation(FRotator(CurrentRotation.Pitch , CurrentRotation.Yaw , Value));
}

void AFlagCoralActor::HandleFadeFinished()
{		
	if (CurLevelName == FloorLevelName) return;


	coralManager->EndInteractionChangeOpValue();
	//bFade = true;
	UE_LOG(LogTemp, Log, TEXT("Fade timeline finished."));
}

void AFlagCoralActor::HandleWhiteFinished()
{		
	if (CurLevelName == FloorLevelName) return;

	// 물고기 생성하는 로직
	coralManager->PlayfishSwimming();

	UE_LOG(LogTemp, Log, TEXT("White timeline finished."));
}

void AFlagCoralActor::HandleSpringFinished()
{	
	if (CurLevelName == FloorLevelName) return;

	coralManager->EndInteractionChangeOpValue();
	bFade = true;
	UE_LOG(LogTemp, Log, TEXT("Fade timeline finished."));
	//FlagMeshComponent->SetRelativeScale3D(OriginalScale);
	//GetRootComponent()->SetRelativeRotation(OriginalRotation);
	//FlagMeshComponent->SetRelativeRotation(OriginalRotation);
}

