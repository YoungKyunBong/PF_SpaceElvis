#include "Manager/CoralForest/Wall_CoralForestManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/CoralForest/FlagCoralActor.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Kismet/GameplayStatics.h"


AWall_CoralForestManager::AWall_CoralForestManager()
{
	PrimaryActorTick.bCanEverTick = false;
	envFloatValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvFloatValueTimeLine"));
	envColorValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvColorValueTimeLine"));
}

void AWall_CoralForestManager::C_Init()
{
	Super::C_Init();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFlagCoralActor::StaticClass(), OutActors);

	for (auto iter : OutActors)
	{
		auto tempActor = Cast<AFlagCoralActor>(iter);
		tempActor->Init(this);
		FlagCoralActors.Add(Cast<AFlagCoralActor>(tempActor));

		if (tempActor->Get_CoralType() == CORAL_TYPE::type7)
			alphaTotalCount++;
		else
		{
			FlagCount++;
		}
	}

	PlaySequenceActor->CustomInit(this);
	
	GetGameManager()->RecvCoralLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvCoralOverlap.AddUFunction(this, FName("OverlapInteraction"));
	GetGameManager()->Send_CoralLevelLoadingEnd();

	//Test Debug SetCmsIsStart	-> SetCmsIsStart() 함수에서 실행 되어야 함.
}

void AWall_CoralForestManager::OverlapInteraction(CORAL_TYPE _Type)
{
	if (IsPlayTime == false) return;
	

	for (AFlagCoralActor* Coral : FlagCoralActors)
	{
		if (!Coral || Coral->Get_CoralType() != _Type) continue;

		/*WeakPtr 캡처*/
		TWeakObjectPtr<AFlagCoralActor> WeakCoral = Coral;

		/*랜덤 딜레이 생성*/
		const int32 Delay = FMath::RandRange(1, 8);

		/*델리게이트 + 타이머*/
		FTimerDelegate Del;
		Del.BindLambda([WeakCoral]()
			{
				if (!WeakCoral.IsValid()) return;          // 파괴됐으면 skip
				
				WeakCoral->PlaySpringEffect();             // 스프링
				WeakCoral->PlayNiagaraEffect();            // 나이아가라
			});

		/*개별 타이머 시작*/
		FTimerHandle TmpHandle;
		GetWorld()->GetTimerManager()
			.SetTimer(TmpHandle, Del, (float)Delay, false);
	}
}

void AWall_CoralForestManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);

	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);

	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CoralForestManager::TimeOutEvent, Playtime, false);
}

void AWall_CoralForestManager::EndInteractionChangeOpValue()
{
	FlagFinishCount++;
	if (FlagCount == FlagFinishCount)
	{
		GetGameManager()->Send_CoralWhiteSwitch();
		for (auto FlagCoralActor : FlagCoralActors)
		{
			FlagCoralActor->WhiteSwitch();
		}
	}
}

void AWall_CoralForestManager::PlayfishSwimming()
{
	if (GetGameManager()->GetPlaceType() == PROTOCOLSUB_TYPE::Floor) return;

		sendCount++;
	if (alphaTotalCount == sendCount)
	{
		//환경 변경 신호 Send 하는 것으로 변경
		if (!IsFail)
		{
			SendOceanCleanChange();
			GetWorldTimerManager().ClearTimer(FinishHandle);		
		}

		// 물고기 생성 작업 Native 이벤트 콜		
		PlayFishSwim();

		//ChangeSkipBinding();
	}
}

void AWall_CoralForestManager::SendLevelEnd()
{
	GetWorldTimerManager().ClearTimer(FinishHandle);
	GetGameManager()->Send_CoralEnd();
	UE_LOG(LogTemp, Log, TEXT("SendCoralEnd."));
}

//void AWall_CoralForestManager::TimeOutEvent()
//{
//	Super::TimeOutEvent();
//
//	//ChangeSkipBinding();
//	//SendOceanCleanChange();
//	//IsPlayTime = false;
//
//	//for (auto FlagCoralActor : FlagCoralActors)
//	//{
//	//	if (FlagCoralActor->Get_CoralType() != CORAL_TYPE::type7 && FlagCoralActor->Get_CoralFade() == false)
//	//	{
//	//		FlagCoralActor->FadeSwitch();
//	//		FlagCoralActor->PlaySpringEffect();
//	//		FlagCoralActor->PlayNiagaraEffect();
//	//	}
//	//}
//	//엔딩 씬전환
//	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CoralForestManager::SendLevelEnd, Finishtime, false);
//}

// <<------------------------------------------------------ 네이밍 실수로 인해서
// RecvLevelEnd() : Skip 기능
// RecvCoralLevelEnd() : LevelEnd 기능
// 요렇게 씀

//void AWall_CoralForestManager::RecvLevelEnd()
//{
//	//Super::RecvLevelEnd();
//
//	GetWorldTimerManager().ClearTimer(FinishHandle);
//	PlaySequenceActor->ClearSequence();
//	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
//	//ChangeSkipBinding();
//}

void AWall_CoralForestManager::RecvCoralLevelEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvCoralLevelEnd"));
	GetGameMode()->Call_LevelEnd(0);
}

// >>------------------------------------------------------

void AWall_CoralForestManager::SetCmsIsStart(bool isStart)
{
	if (isOneTime)
	{
		isOneTime = false;
		//if(GetGameManager()->GetNodeType() == ClientNodeType::Node0)
			//타임라인 시작 함수 선언
			//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CoralForestManager::TimeOutEvent, Playtime, false);

	}

	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

void AWall_CoralForestManager::RecvPlayTimeOutEvent()
{
	//Super::RecvPlayTimeOutEvent();

	IsFail = true;

	ChangeEnvironment();

	for (AFlagCoralActor* Coral : FlagCoralActors)
	{
		if (Coral->Get_CoralType() != CORAL_TYPE::type7 && Coral->Get_CoralFade() == false)
		{
			/*WeakPtr 캡처*/
			TWeakObjectPtr<AFlagCoralActor> WeakCoral = Coral;

			/*랜덤 딜레이 생성*/
			const int32 Delay = FMath::RandRange(1, 8);

			/*델리게이트 + 타이머*/
			FTimerDelegate Del;
			Del.BindLambda([WeakCoral]()
				{
					if (!WeakCoral.IsValid()) return;          // 파괴됐으면 skip

					WeakCoral->PlaySpringEffect();             // 스프링
					WeakCoral->PlayNiagaraEffect();            // 나이아가라
				});

			/*개별 타이머 시작*/
			FTimerHandle TmpHandle;
			GetWorld()->GetTimerManager()
				.SetTimer(TmpHandle, Del, (float)Delay, false);
		}
	}

	GetWorldTimerManager().ClearTimer(FinishHandle);
	TimeOutDelay();
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CoralForestManager::TimeOutDelay, Finishtime, false);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep2"));
}

void AWall_CoralForestManager::RecvOceanCleanChange()
{
	Super::RecvOceanCleanChange();

	ChangeEnvironment();
}

void AWall_CoralForestManager::Call_Intro_SQ_End()
{
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_CoralForestManager::TimeOutEvent, Playtime, false);
}

void AWall_CoralForestManager::Call_DefaultLevelEnd()
{
	if(!checkTestGame)
		GetGameManager()->Send_CoralEnd();
}

//void AWall_CoralForestManager::SetTimeLine_EnvFloatValue()
//{
//	float playrate = 1.f / envDefaultTimeRate;
//	envFloatValue_TimeLine->SetLooping(false);
//
//	envFloatValue_TimeLine->AddInterpFloat(envFloatValue_Curve, envFloatValue_TimelineCallback);
//	envFloatValue_TimeLine->SetTimelineFinishedFunc(envFloatValue_TimelineFinishedCallback);
//	envFloatValue_TimeLine->SetPlayRate(playrate);
//
//	envFloatValue_TimeLine->PlayFromStart();
//}

void AWall_CoralForestManager::SetTimeLine_EnvColorValue()
{
}

void AWall_CoralForestManager::TimeOutDelay()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TimeOutDelay"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

PROTOCOLSUB_TYPE AWall_CoralForestManager::Get_Type()
{
	return GetGameManager()->GetPlaceType();
}

void AWall_CoralForestManager::Send_CoralOverlap(CORAL_TYPE _Type)
{
	if (GetGameManager()->GetIsLocalGame())
		OverlapInteraction(_Type);
	else
	{
		if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
			GetGameManager()->Send_CoralOverlap(_Type);
	}
}

//void AWall_CoralForestManager::ChangeSkipBinding()
//{
//	GetGameManager()->RecvCmsControllerSkip.Clear();
//	GetGameManager()->RecvCmsControllerSkip.AddUFunction(this, FName("RecvCoralLevelEnd"));
//}
