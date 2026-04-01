
#include "Manager/OceanVillage/Wall_OceanVillageManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/StepActor/OceanVillage/GuideActor.h"
#include "Actors/StepActor/OceanVillage/GuideTargetActor.h"
#include "Actors/StepActor/OceanVillage/TextureFishCharacter.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"

#include "Engine/TargetPoint.h"
#include "MyBlueprintFunctionLibrary.h"
#include "ImageUtils.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include <Kismet/GameplayStatics.h>


void AWall_OceanVillageManager::EndPlay(const EEndPlayReason::Type R)
{
	GetWorld()->GetTimerManager().ClearTimer(FileSearchTimerHandle);
	// 이미 예약된 AsyncTask 는 WeakPtr 검사로 자동 무시됨
	Super::EndPlay(R);
	UE_LOG(LogTemp, Warning, TEXT("AWall_OceanVillageManager::Safe EndPlay"));
}

void AWall_OceanVillageManager::C_Init()
{
	Super::C_Init();

	GetGameManager()->RecvOceanVillageLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));
	GetGameManager()->RecvGuideActorTargetChange.AddUFunction(this, FName("RecvGuideActorTargetChange"));
	GetGameManager()->RecvFishActorTargetChange.AddUFunction(this, FName("RecvFishActorTargetChange"));
	GetGameManager()->RecvFishActorTransform.AddUFunction(this, FName("RecvFishActorTransform"));

	GetGameManager()->RecvLoadPNG.AddUFunction(this, FName("RecvLoadPNG"));

	PlaySequenceActor->CustomInit(this);

	GetGameManager()->Send_OceanVillageLevelLoadingEnd();

	FishInfos =
	{
		{ TEXT("Clown"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_ClownFish.CBP_ClownFish_C'"), 0 },
		{ TEXT("Turtle"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_TurtleFish.CBP_TurtleFish_C'"), 1 },
		{ TEXT("Barreleye"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_BarreleyeFish.CBP_BarreleyeFish_C'"), 2 },
		{ TEXT("Dumbo"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_DumboFish.CBP_DumboFish_C'"), 3 },
		{ TEXT("GShark"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_GSharkFish.CBP_GSharkFish_C'"), 4 },
		{ TEXT("GSquid"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_GSquidFish.CBP_GSquidFish_C'"), 5 },
		{ TEXT("Jely"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_JelyFish.CBP_JelyFish_C'"), 6 },
		{ TEXT("MSnail"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_MSnailFish.CBP_MSnailFish_C'"), 7 },
		{ TEXT("SeaHorse"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_SeaHorseFish.CBP_SeaHorseFish_C'"), 8 },
		{ TEXT("Shark"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_SharkFish.CBP_SharkFish_C'"), 9 },
		{ TEXT("Angler"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_AnglerFish.CBP_AnglerFish_C'"), 10 },
		{ TEXT("Tripod"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_TripodFish.CBP_TripodFish_C'"), 11 },
		{ TEXT("ChromisNotatus"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_ChromisNotatusFish.CBP_ChromisNotatusFish_C'"), 12 },
		{ TEXT("Herring"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_HerringFish.CBP_HerringFish_C'"), 13 },
		{ TEXT("StripedBeakfish"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_StripedBeakFish.CBP_StripedBeakFish_C'"), 14 }
		//{ TEXT("Snipe"), TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_Snipe_EelFish.CBP_Snipe_EelFish_C'"), 10 },

	};

	FVector BaseLocation = FVector(-845.915034f, 2217.093781f, 1900.000000f);
	SpawnPoints.Add(BaseLocation + FVector(0.f, 1200.f, 0.f));
	SpawnPoints.Add(BaseLocation + FVector(0.f, -1200.f, 0.f));
	SpawnPoints.Add(BaseLocation + FVector(0.f, 2500.f, 0.f));
	SpawnPoints.Add(BaseLocation + FVector(0.f, -2500.f, 0.f));
	DirTagName = {
	TEXT("RIght"),
	TEXT("Left")
	};
	isFirstPlay = true;

	ApplyCount.Init(0, NumFishTypes);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("SkipStep"));
}

void AWall_OceanVillageManager::RecvLevelLoadingEnd(bool isStart)
{
	SetActors();
	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::IntroType);
	//GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_OceanVillageManager::TimeOutEvent, Playtime, false);
	//SetCmsIsStart(isStart);

}

void AWall_OceanVillageManager::RecvGuideActorTargetChange(int _guideNum, int _targetActorNum)
{
	GuideActors[_guideNum]->SetChangeTarget(TargetPointActors[_targetActorNum]);
}

void AWall_OceanVillageManager::RecvFishActorTargetChange(int _fishNum, int _guideNum, bool IsFirst)
{
	FishActors[_fishNum]->SetChangeTarget_ToFish(GuideActors[_guideNum]);
}


//void AWall_OceanVillageManager::RecvFishActorTargetChange_Implementation(int _fishNum, int _guideNum, bool IsFirst)
//{
//	FishActors[_fishNum]->SetChangeTarget_ToFish(GuideActors[_guideNum]);
//}

void AWall_OceanVillageManager::RecvFishActorTransform(int _fishNum, FTransform _fishTransform)
{
	//Node0 Pc 로부터 물고기 위치값을 받아 Node1의 동일 물고기에게 위치값 전달
}

void AWall_OceanVillageManager::RecvLoadPNG()
{

	/* 자기 자신을 안전하게 참조할 WeakPtr */
	TWeakObjectPtr<AWall_OceanVillageManager> Self(this);

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask,
		[Self]()
		{
			/*백그라운드 스레드*/
			if (!Self.IsValid()) return;                         // 파괴되었으면 즉시 종료

			/* 1) Python 실행 */
			const FString Dir = Self->ReadFilePath;
			FString QR = UMyBlueprintFunctionLibrary::ExecuteQRCodeScript(Dir);
			UMyBlueprintFunctionLibrary::ExecuteJPGtoPNGScript(Dir);

			/* 2) 방금 만들어진 PNG 찾기 */
			TArray<FString> PngFiles;
			IFileManager::Get().FindFiles(PngFiles, *Dir, TEXT("*.png"));
			if (PngFiles.IsEmpty())
			{
				/* GameThread 에서 타이머 재개만 처리 */
				AsyncTask(ENamedThreads::GameThread, [Self]()
					{
						if (!Self.IsValid()) return;
						Self->GetWorld()->GetTimerManager().UnPauseTimer(Self->FileSearchTimerHandle);
						UE_LOG(LogTemp, Warning, TEXT("No PNG file found"));
					});
				return;
			}

			const FString PngPath = Dir / PngFiles[0];

			/* GameThread 로 전환 */
			AsyncTask(ENamedThreads::GameThread,
				[Self, QRText = MoveTemp(QR), PngPath]()         // 값 캡처
				{
					if (!Self.IsValid()) return;                     //  다시 한 번 확인
					// RecvLoadPNG() 진입 직후
					if (Self->LoadingPaths.Contains(PngPath))
					{
						UE_LOG(LogTemp, Warning, TEXT("Already loading %s ? skip"), *PngPath);
						return;                         // 두 번째 호출 무시
					}
					UE_LOG(LogTemp, Log, TEXT("QRText: %s"), *QRText);

					Self->LoadingPaths.Add(PngPath);

					Self->FoundSpawnFish(QRText, PngPath);           // 안전 호출

					Self->LoadingPaths.Remove(PngPath);       // 완료실패 시 정리
				});
		});
}


void AWall_OceanVillageManager::SetCmsIsStart(bool isStart)
{
	//isStart ? MoviePlayerActor->CMS_Start() : MoviePlayerActor->CMS_Stop();

	if (isFirstPlay)
	{
		isFirstPlay = false;
		if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
		{
			for (int i = 0; i < GuideActors.Num(); i++)
			{
				GuideActors[i]->CustomStartTimer();
				GuideActors[i]->ChangeTargetPoint();
			}
		}
	}

	for (int i = 0; i < GuideActors.Num(); i++)
	{
		GuideActors[i]->IsMove(isStart);
	}

	for (int i = 0; i < FishActors.Num(); i++)
	{
		FishActors[i]->IsMove(isStart);
	}

	if (isStart)
	{
		StartFileSearchTimer();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	}

	if (isStart)
		PlaySequenceActor->PlaySequence(Lv_Sq_Type::Cms_Type);
	else
		PlaySequenceActor->CustomStopSequence();
}

TArray<AGuideTargetActor*> AWall_OceanVillageManager::GetTargetActors()
{
	TArray<AGuideTargetActor*> outArray;
	outArray.Empty();

	TargetPointActors.GenerateValueArray(outArray);
	return outArray;
}

void AWall_OceanVillageManager::SendGuideActorTargetChange(int _guideNum, int _targetActorNum)
{
	GetGameManager()->Send_GuideActorTargetChange(_guideNum, _targetActorNum);
}

void AWall_OceanVillageManager::SendFishActorTargetChange(int _fishNum, int _guideNum)
{
	//GetGameManager()->Send_FishActorTargetChange(_fishNum, _guideNum);
}

inline void AWall_OceanVillageManager::SendPlayEffectSound(EFFECT_SOUND_TYPE _type) { GetGameManager()->Send_PlayEffectSound(_type); }

void AWall_OceanVillageManager::Call_Intro_SQ_End()
{
	SetCmsIsStart(true);
	IsCmsState = true;
	GetWorld()->GetTimerManager().SetTimer(FinishHandle, this, &AWall_OceanVillageManager::TimeOutEvent, Playtime, false);
}

void AWall_OceanVillageManager::Call_DefaultLevelEnd()
{
	//GetGameManager()->Send_CmsControllerSkip();
}

void AWall_OceanVillageManager::SetGuideActors(TArray<AGuideActor*> _guideActors)
{
	//for (int i = 0; i < _guideActors.Num(); i++)
	//{
	//	//int tempNum = i + 1;
	//	_guideActors[i]->SetMyNum(i);
	//	_guideActors[i]->CustomInit(this);
	//	GuideActors.Add(i, _guideActors[i]);
	//	AvailableGuideIndex.Add(i);
	//}
	GuideActors.Empty();
	AvailableGuideIndex.Empty();
	AvailableGuideIndexMap.Empty();

	// "Left"와 "Right" 태그 기반으로 GuideActor를 구분하고 등록
	for (int i = 0; i < _guideActors.Num(); ++i)
	{
		AGuideActor* GuideActor = _guideActors[i];
		if (!IsValid(GuideActor)) continue;

		GuideActor->SetMyNum(i);
		GuideActor->CustomInit(this);

		GuideActors.Add(i, GuideActor);
		AvailableGuideIndex.Add(i);

		// Tag 기준 분류
		if (GuideActor->Tags.Contains("Left"))
		{
			AvailableGuideIndexMap.FindOrAdd("Left").Add(i);
		}
		else if (GuideActor->Tags.Contains("Right"))
		{
			AvailableGuideIndexMap.FindOrAdd("Right").Add(i);
		}
	}

}

void AWall_OceanVillageManager::SetTargetActors(TArray<AGuideTargetActor*> _targetPointActors)
{
	for (int i = 0; i < _targetPointActors.Num(); i++)
	{
		int tempNum = i + 1;
		_targetPointActors[i]->SetMyNum(tempNum);
		TargetPointActors.Add(tempNum, _targetPointActors[i]);
	}
}

void AWall_OceanVillageManager::SetFishActors(TArray<ATextureFishCharacter*> _fishActors)
{
	for (int i = 0; i < _fishActors.Num(); i++)
	{
		_fishActors[i]->SetMyNum(i);
		_fishActors[i]->CustomInit(this);
		FishActors.Add(i, _fishActors[i]);
		GetGameManager()->Send_FishActorTargetChange(i, GuideActors[SetFishActorToRandomGuideActor()]->GetMyNum(), true);
	}
}

int AWall_OceanVillageManager::SetFishActorToRandomGuideActor()
{
	// 랜덤으로 GuideActor 선택
	int32 RandomIndex = FMath::RandRange(0, AvailableGuideIndex.Num() - 1);
	int32 SelectedIndex = AvailableGuideIndex[RandomIndex];
	// 선택된 GuideActor의 인덱스를 사용 가능한 목록에서 제거
	AvailableGuideIndex.RemoveAt(RandomIndex);
	return SelectedIndex;
}

int AWall_OceanVillageManager::SetFishActorToRandomGuideActor_ByTag(FName InDirTag)
{
	if (!AvailableGuideIndexMap.Contains(InDirTag)) return -1;

	TArray<int32>& AvailableList = AvailableGuideIndexMap[InDirTag];

	if (AvailableList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Available GuideActor with tag: %s"), *InDirTag.ToString());
		return -1;
	}

	int32 RandIndex = FMath::RandRange(0, AvailableList.Num() - 1);
	int32 SelectedIndex = AvailableList[RandIndex];
	AvailableList.RemoveAt(RandIndex); // 중복 방지

	return SelectedIndex;
}

void AWall_OceanVillageManager::StartFileSearchTimer()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(FileSearchTimerHandle))
		GetWorld()->GetTimerManager().SetTimer(FileSearchTimerHandle,
			this, &AWall_OceanVillageManager::SearchScannerFile, FileSearchInterval, true);
}

void AWall_OceanVillageManager::SearchScannerFile()
{
	// 백그라운드 스레드에서 파일 검색 수행
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			bool txtFound = false;
			if (!bTxtFileChecked)
			{
				txtFound = CheckTxtFile();

				AsyncTask(ENamedThreads::GameThread, [this, txtFound]()
					{
						bTxtFileChecked = txtFound;
					});
			}

			if (bTxtFileChecked)
			{
				bool jpgFound = CheckJpgFile();

				// jpg 파일을 찾았을 때만 메인 스레드 작업 예약
				if (jpgFound)
				{
					AsyncTask(ENamedThreads::GameThread, [this]()
						{
							// 타이머 일시 중지
							GetWorld()->GetTimerManager().PauseTimer(FileSearchTimerHandle);
							UE_LOG(LogTemp, Log, TEXT("Found jpg File: Pause Timer"));
							// Python 스크립트 실행
							GetGameManager()->Send_LoadPNG();
							UE_LOG(LogTemp, Log, TEXT("Send_LoadPNG"));
						});
				}
			}
		});
}

void AWall_OceanVillageManager::SpawnActor(FString ActorPath, FName _TagName)
{
	FString BlueprintPath = ActorPath;
	UClass* BlueprintActorClass = LoadObject<UClass>(nullptr, *BlueprintPath);

	if (BlueprintActorClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CheckNewFile::LoadFile Not Found"));
		return;
	}

	/*Spawn Parameter*/

	FVector Location = SpawnPoints[CurrentSpawnIndex];
	FName DirName = DirTagName[DirIndex];
	FRotator Rotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnedActor = GetWorld()->SpawnActor<ATextureFishCharacter>(BlueprintActorClass, Location, Rotation, SpawnParams);
	if (SpawnedActor)
	{
		SpawnedActor->Tags.Add(_TagName);
		SpawnedActor->Tags.Add(DirName);
		int i = FishActors.Num();
		SpawnedActor->SetMyNum(i);
		SpawnedActor->CustomInit(this);
		FishActors.Add(i, SpawnedActor);
		SpawnedActor->bSpawnFish = true;
		int GuideIndex = SetFishActorToRandomGuideActor_ByTag(DirName);
		if (GuideIndex != -1)
		{
			GetGameManager()->Send_FishActorTargetChange(i, GuideIndex, false);
		}
	}
	CurrentSpawnIndex = (CurrentSpawnIndex + 1) % SpawnPoints.Num();
	DirIndex = (DirIndex + 1) % DirTagName.Num();
}

FVector AWall_OceanVillageManager::RandomLocation(const FVector& BaseLocation, float Radius, float Z_Radius)
{
	//생성 위치
	float RandomX = FMath::RandRange(BaseLocation.X - Radius, BaseLocation.X + Radius);
	float RandomY = FMath::RandRange(BaseLocation.Y - Radius, BaseLocation.Y + Radius);
	float RandomZ = FMath::RandRange(BaseLocation.Z - Z_Radius, BaseLocation.Z + Z_Radius);

	return FVector(RandomX, RandomY, RandomZ);
}

void AWall_OceanVillageManager::FindSpawnPoints()
{
	//왼 오 조건을 추가해야 함
	TArray<AActor*> FoundSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), FoundSpawnPoints);
	TargetPoints.Empty();
	for (int i = 0; i < FoundSpawnPoints.Num(); ++i)
	{
		ATargetPoint* TargetPoint = Cast<ATargetPoint>(FoundSpawnPoints[i]);
		TargetPoints.Add(TargetPoint);
	}
	//왼
	if (FoundSpawnPoints.Num() > 0)
	{
		ATargetPoint* SpawnPoint = Cast<ATargetPoint>(FoundSpawnPoints[33]);
		if (SpawnPoint)
		{
			LeftSpawnLocation = SpawnPoint->GetActorLocation();
			SpawnRotator = SpawnPoint->GetActorRotation();
		}
	}
}

bool AWall_OceanVillageManager::CheckTxtFile()
{
	// 파일 확장자가 txt인 파일들을 검색
	FString FilePath = FPaths::ProjectDir() / TEXT("LoadFile/");
	TArray<FString> FoundFiles;
	IFileManager& FileManager = IFileManager::Get();

	FileManager.FindFiles(FoundFiles, *FilePath, TEXT("*.txt"));

	if (FoundFiles.Num() > 0)
	{
		// 첫 번째 txt 파일을 대상으로 작업
		FString TxtFilePath = FPaths::Combine(FilePath, FoundFiles[0]);  // txt 파일 경로

		// txt 경로 정규화
		FString PngDirectoryPath;
		FFileHelper::LoadFileToString(PngDirectoryPath, *TxtFilePath);
		PngDirectoryPath.ReplaceInline(TEXT("\\"), TEXT("/"), ESearchCase::CaseSensitive);
		PngDirectoryPath.ReplaceInline(TEXT("//"), TEXT("/"), ESearchCase::CaseSensitive);
		PngDirectoryPath.RemoveFromStart(TEXT("/"));
		PngDirectoryPath.RemoveFromEnd(TEXT("/"));
		FPlatformMisc::NormalizePath(PngDirectoryPath);
		ReadFilePath = PngDirectoryPath;
		UE_LOG(LogTemp, Log, TEXT("CheckNewFile::txt File Found"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CheckNewFile::LoadFile Not Found"));
		return false;
	}
}

bool AWall_OceanVillageManager::CheckJpgFile()
{
	// 저장된 경로에서 png 파일 찾기
	TArray<FString> PngFiles;
	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(PngFiles, *ReadFilePath, TEXT("*.jpg"));

	if (PngFiles.Num() > 0)
	{
		/*PythonScript::Copy jpg file*/
		UMyBlueprintFunctionLibrary::ExecuteCopyFirstJPGScript(ReadFilePath);

		return true;
	}

	return false;
}
//
//UTexture2D* AWall_OceanVillageManager::FiledToTexture2D()
//{
//	//png 텍스처 -> Texture2D변환
//	TArray<FString> PngFiles;
//	FString FilePath = ReadFilePath;
//
//	IFileManager& FileManager = IFileManager::Get();
//	FileManager.FindFiles(PngFiles, *FilePath, TEXT("*.png"));
//
//	UTexture2D* texture = nullptr;
//	if (PngFiles.Num() > 0) {
//		FString PngFilePath = FPaths::Combine(FilePath, PngFiles[0]);
//		texture = FImageUtils::ImportFileAsTexture2D(PngFilePath);
//
//		if (texture == nullptr)
//		{
//			UE_LOG(LogTemp, Error, TEXT("Failed::ImportFileAsTexture2D"));
//			return nullptr;
//		}
//		else
//		{
//			FullPath = PngFilePath;
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("No PNG Files Found"));
//		return nullptr;
//	}
//	return texture;
//}

void AWall_OceanVillageManager::FoundSpawnFish(FString _QRText, FString PngPath)
{
	FullPath = PngPath;
	int32 SpawnIndex = 0;
	for (const FFishInfo& Info : FishInfos)
	{
		if (_QRText.Equals(Info.Name, ESearchCase::IgnoreCase))
		{
			TagName = *Info.Name;
			ApplyCount[Info.Index]++;
			if (ApplyCount[Info.Index] > SpawnIndex)
			{
				SpawnActor(Info.Path, TagName);
			}

			// TagName에 맞는 ATextureFishCharacter 인스턴스를 찾아 ApplyMaterial 호출
			for (auto It = FishActors.CreateConstIterator(); It; ++It)
			{
				ATextureFishCharacter* FishActor = It->Value;
				if (FishActor->Tags.Contains(TagName))
				{
					FishActor->ApplyMaterial(PngPath);
					GetWorld()->GetTimerManager().UnPauseTimer(FileSearchTimerHandle);
					UE_LOG(LogTemp, Log, TEXT("ApplyMaterial: UnPause Timer"));
					return;
				}

			}
		}
	}

}
