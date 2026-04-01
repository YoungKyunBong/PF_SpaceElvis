
#include "Manager/CleaningOcean/Floor_CleaningOceanManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/CleaningOcean/FloorTrashActor.h"
#include "Actors/StepActor/CleaningOcean/WhaleCharacter.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Kismet/GameplayStatics.h"

AFloor_CleaningOceanManager::AFloor_CleaningOceanManager()
{
	PrimaryActorTick.bCanEverTick = false;
	envFloatValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvFloatValueTimeLine"));
	envColorValue_TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EnvColorValueTimeLine"));
}

void AFloor_CleaningOceanManager::C_Init()
{
	Super::C_Init();

	whaleActor->Init(this);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFloorTrashActor::StaticClass(), OutActors);

	for (auto iter : OutActors)
	{
		auto tempActor = Cast<AFloorTrashActor>(iter);
		tempActor->Init(this);
		floorTrashActors.Add(Cast<AFloorTrashActor>(tempActor));
	}

	trashActorCount = floorTrashActors.Num();

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->RecvCleaningLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvWallSpawnWhaleEnd.AddUFunction(this, FName("RecvWallSpawnWhaleEnd"));
	GetGameManager()->RecvPlayWhaleSound.AddUFunction(this, FName("RecvPlayWhaleSound"));
	GetGameManager()->RecvFloorSpawnWhale.AddUFunction(this, FName("RecvFloorSpawnWhale"));
	GetGameManager()->RecvPlayEffectSound.AddUFunction(this, FName("RecvPlayEffectSound"));

	//currSoundType = EFFECT_SOUND_TYPE::SoundType0;
	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Dirty);

	GetGameManager()->Send_CleaningLevelLoadingEnd();

	AddRange = ChangeRange / trashActorCount;

	trashActorOverlapCount = 1;

	//trashCount = floorTrashActors.Num();
}

void AFloor_CleaningOceanManager::RecvLevelLoadingEnd(bool isStart)
{
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);

	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);

	GetGameManager()->Send_WallSpawnWhale(floorTrashActors.Num());
	// Test Code 나중에 서버 연동하면 꼭 지우도록.
	//for(int i = 0; i < floorTrashActors.Num(); i++)
	//	SendPlayWhaleSound();
	SetCmsIsStart(true);
}

void AFloor_CleaningOceanManager::RecvWallSpawnWhaleEnd()
{
	isWallSpawnWhaleEnd = true;
	SetCmsIsStart(true);
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType1);
}

void AFloor_CleaningOceanManager::RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE _type)
{
	GetGameMode()->Call_PlayCustomSound((uint8)SOUND_TYPE::Effect, (uint8)_type);
	WorldSetting(_type);
}

void AFloor_CleaningOceanManager::RecvFloorSpawnWhale(SIDE_TYPE _type, bool _isSuccess)
{
	//whaleActor->SetIsMove(true);
	whaleActor->SetStartPoint(_type);
	whaleActor->MoveObject();
	ChangeEnvironment();
	//whaleActor->SetSideType(_type);
	//whaleActor->IsWhaleMove(true);
	GetGameManager()->Send_PlayEffectSound(EFFECT_SOUND_TYPE::SoundType2);
	GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::BGM, BGSound_Clean);

	if(_isSuccess)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroSucessType);
	else
	{
		SetCmsIsStart(false);
	}
}

void AFloor_CleaningOceanManager::RecvPlayEffectSound(EFFECT_SOUND_TYPE _type)
{
	currSoundType = _type;
	switch (_type)
	{
	case EFFECT_SOUND_TYPE::SoundType0:
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
		GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::Effect, WallWhaleSound);
		RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE::Default);
	}
		break;
	case EFFECT_SOUND_TYPE::SoundType1:
	{
		GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::Effect, FloorWhaleSound);
	}
		break;
	case EFFECT_SOUND_TYPE::SoundType2:
	{
		GetGameMode()->Call_SetCustomSound((uint8)SOUND_TYPE::Effect, WallWhaleSound);
		RecvPlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE::Default);
	}
		break;
	case EFFECT_SOUND_TYPE::SoundType3:
		break;
	default:
		break;
	}
}

void AFloor_CleaningOceanManager::SendPlayWhaleSound()
{
	GetGameManager()->Send_PlayWhaleSound();
	UE_LOG(LogTemp, Log, TEXT("Success PlauWhaleSound"));
}

void AFloor_CleaningOceanManager::SendCleaningOceanLevelEnd()
{
	//GetGameManager()->Send_CleaningOceanEnd();
}

int AFloor_CleaningOceanManager::CountOverlap(bool isAdd)
{
	if(isAdd)
		trashActorOverlapCount++;
	else
		trashActorOverlapCount--;

	return trashActorOverlapCount;
}

void AFloor_CleaningOceanManager::SetCmsIsStart(bool isStart)
{
	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();

	//if(isStart)
	//	GetGameManager()->Send_PlayEffectSound(currSoundType);

	//if(!isWallSpawnWhaleEnd && !GetGameManager()->GetIsLocalGame())
	//	return;

	for (auto iter : floorTrashActors)
	{
		iter->SetOverlap(isStart);
	}

	SetCushionActors(isStart);

	whaleActor->SetIsMove(isStart);
}

void AFloor_CleaningOceanManager::SetTimeLine_EnvFloatValue()
{
	float playrate = 1.f / envDefaultTimeRate;
	envFloatValue_TimeLine->SetLooping(false);

	envFloatValue_TimeLine->AddInterpFloat(envFloatValue_Curve, envFloatValue_TimelineCallback);
	envFloatValue_TimeLine->SetTimelineFinishedFunc(envFloatValue_TimelineFinishedCallback);
	envFloatValue_TimeLine->SetPlayRate(playrate);

	envFloatValue_TimeLine->PlayFromStart();
}

void AFloor_CleaningOceanManager::SetTimeLine_EnvColorValue()
{
}

void AFloor_CleaningOceanManager::Call_Intro_SQ_End()
{
	for (auto iter : floorTrashActors)
	{
		iter->CustomSetActorLocation();
	}
}
