#include "Actors/StepActor/OceanVillage/GameMode/OceanVillageGameMode.h"
#include "Actors/StepActor/OceanVillage/TextureFishCharacter.h"
#include "MyBlueprintFunctionLibrary.h"

#include "Engine/TargetPoint.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include <Kismet/GameplayStatics.h>
#include "ImageUtils.h"
#include <windows.h>

void AOceanVillageGameMode::SearchScannerFile()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			bool bCheckFile = CheckNewFile();
			if (bCheckFile)
			{
				UTexture2D* LoadedTexture = FiledToTexture2D();				
				AsyncTask(ENamedThreads::GameThread, [this, LoadedTexture]()
					{
						if (LoadedTexture)
						{
							customMakeTexture = LoadedTexture;
							FoundSpawnFish(QRText);
						}
					});
			}
		});
}

//void AOceanVillageGameMode::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

void AOceanVillageGameMode::init()
{
	StartFileSearchTimer();
	ApplyCount.Init(0, 12);

}

void AOceanVillageGameMode::StartFileSearchTimer()
{
	//FindSpawnPoints();
	GetWorld()->GetTimerManager().SetTimer(FileSearchTimerHandle,
		this, &AOceanVillageGameMode::SearchScannerFile, 5.0f, true);
}

bool AOceanVillageGameMode::CheckNewFile()
{
	// 파일 확장자가 png인 파일들을 검색
	//FString FilePath = TEXT("C:/unrealpj/FutureOcean/LoadFile/");
	FString FilePath = FPaths::ProjectDir() / TEXT("LoadFile/");
	TArray<FString> FoundFiles;
	TArray<FString> PngFiles;
	IFileManager& FileManager = IFileManager::Get();

	FileManager.FindFiles(FoundFiles, *FilePath, TEXT("*.txt"));

	if (FoundFiles.Num() > 0)
	{
		// 첫 번째 txt 파일을 대상으로 작업
		FString TxtFilePath = FPaths::Combine(FilePath, FoundFiles[0]);  // txt 파일 경로

		// txt 파일 내용 읽기
		FString PngDirectoryPath;
		FFileHelper::LoadFileToString(PngDirectoryPath, *TxtFilePath);
		PngDirectoryPath.ReplaceInline(TEXT("\\"), TEXT("/"), ESearchCase::CaseSensitive);
		PngDirectoryPath.ReplaceInline(TEXT("//"), TEXT("/"), ESearchCase::CaseSensitive);
		PngDirectoryPath.RemoveFromStart(TEXT("/"));
		PngDirectoryPath.RemoveFromEnd(TEXT("/"));
		FPlatformMisc::NormalizePath(PngDirectoryPath);
		ReadFilePath = PngDirectoryPath;

		// 읽은 경로에서 png 파일 찾기		
		FileManager.FindFiles(PngFiles, *PngDirectoryPath, TEXT("*.jpg"));
		UE_LOG(LogTemp, Log, TEXT("CheckNewFile::txt File Found"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CheckNewFile::LoadFile Not Found"));
	}
	if (PngFiles.Num() > 0)
	{
		QRText = UMyBlueprintFunctionLibrary::ExecuteQRCodeScript(ReadFilePath);
		UMyBlueprintFunctionLibrary::ExecuteJPGtoPNGScript(ReadFilePath);
		
		//UMyBlueprintFunctionLibrary::LoadJPGFromFile(ReadFilePath);
		UE_LOG(LogTemp, Log, TEXT("Completed: %s"), *QRText);
	}
	return PngFiles.Num() > 0;
}

UTexture2D* AOceanVillageGameMode::FiledToTexture2D()
{
	//png 텍스처 -> Texture2D변환
	TArray<FString> PngFiles;
	FString FilePath = ReadFilePath;

	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(PngFiles, *FilePath, TEXT("*.png"));

	UTexture2D* texture = nullptr;
	if (PngFiles.Num() > 0) {
		FString PngFilePath = FPaths::Combine(FilePath, PngFiles[0]);
		texture = FImageUtils::ImportFileAsTexture2D(PngFilePath);		
		
		if (texture == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed::ImportFileAsTexture2D"));
			return nullptr;
		}
		else
		{
			FullPath = PngFilePath;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No PNG Files Found"));
		return nullptr;
	}
	return texture;
}

void AOceanVillageGameMode::GetPixelColor(UTexture2D* Texture)
{
	//if (!Texture || !Texture->GetPlatformData() || Texture->GetPlatformData()->Mips.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Invalid Texture!"));
	//	return;
	//}

	//// Get the first mip level
	//FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
	//const FColor* FormatedImageData = static_cast<const FColor*>(Mip.BulkData.LockReadOnly());

	//if (!FormatedImageData)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Unable to lock texture data!"));
	//	return;
	//}

	///*int32 Width = Mip.SizeX;
	//int32 Height = Mip.SizeY;*/

	//int32 FoundCount = 0;
	//int32 Width = 200;
	//int32 Height = 200;

	///*Pixel 범위 지정 특정 컬러 탐색*/
	//for (int32 Y = 0; Y < Height; ++Y)
	//{
	//	for (int32 X = 0; X < Width; ++X)
	//	{
	//		const FColor& PixelColor = FormatedImageData[Y * Width + X];

	//		//UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//		// Check if the color is white and alpha is above 200
	//		//UE_LOG(LogTemp, Error, TEXT("Found Color (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//		//bool bClownPixelColor = PixelColor.R <= 255 && PixelColor.G <= 250 && PixelColor.B <= 250;
	//		bool bClownPixelColor = (PixelColor.R <= 100 && PixelColor.G <= 100 && PixelColor.B <= 100);
	//		if (bClownPixelColor == true)
	//		{
	//			FoundCount++;
	//			if (FoundCount == 12) break;
	//			UE_LOG(LogTemp, Error, TEXT("Found Color (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);

	//		}
	//		/*else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Barreleye";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Dumbo";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "GShark";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "GSquid";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Jely";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "MSnail";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "SeaHorse";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Shark";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Snipe";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Tripod";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}
	//		else if (PixelColor.R == 255 && PixelColor.G == 0 && PixelColor.B == 0)
	//		{
	//			bFoundAlpha = true;
	//			TagName = "Turtle";
	//			UE_LOG(LogTemp, Log, TEXT("Detected white pixel with alpha > 200 at (%d, %d): R=%d, G=%d, B=%d, A=%d"), X, Y, PixelColor.R, PixelColor.G, PixelColor.B, PixelColor.A);
	//			break;
	//		}*/
	//	}
	//	if (FoundCount == 12) break;
	//}
	////FoundSpawnFish(FoundCount);

	//// Unlock the bulk data
	//Mip.BulkData.Unlock();
}

void AOceanVillageGameMode::FoundSpawnFish(FString _QRText)
{
	FString ActorPath;
	FName GuideActorTagName;
	int32 SpawnCount = 1;
	if (_QRText.Equals(TEXT("Clown"), ESearchCase::IgnoreCase))
	{
		TagName = "Clown";
		// 생성 카운트? 넣어줘야 하나 2개 넘으면 생성 하는 코드를 여기에 만드는 게 나을듯
		//배열로?
		ApplyCount[0]++;
		if (ApplyCount[0] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_ClownFish.CBP_ClownFish_C'");
			SpawnActor(ActorPath, TagName);
		}

	}
	else if (_QRText.Equals(TEXT("Turtle"), ESearchCase::IgnoreCase))
	{
		TagName = "Turtle";
		ApplyCount[1]++;
		if (ApplyCount[1] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_TurtleFish.CBP_TurtleFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Barreleye"), ESearchCase::IgnoreCase))
	{
		TagName = "Barreleye";
		ApplyCount[2]++;
		if (ApplyCount[2] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_BarreleyeFish.CBP_BarreleyeFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Dumbo"), ESearchCase::IgnoreCase))
	{
		TagName = "Dumbo";
		ApplyCount[3]++;
		if (ApplyCount[3] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_DumboFish.CBP_DumboFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("GShark"), ESearchCase::IgnoreCase))
	{
		TagName = "GShark";
		ApplyCount[4]++;
		if (ApplyCount[4] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_GSharkFish.CBP_GSharkFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("GSquid"), ESearchCase::IgnoreCase))
	{
		TagName = "GSquid";
		ApplyCount[5]++;
		if (ApplyCount[5] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_GSquidFish.CBP_GSquidFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Jely"), ESearchCase::IgnoreCase))
	{
		TagName = "Jely";
		ApplyCount[6]++;
		if (ApplyCount[6] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_JelyFish.CBP_JelyFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("MSnail"), ESearchCase::IgnoreCase))
	{
		TagName = "MSnail";
		ApplyCount[7]++;
		if (ApplyCount[7] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_MSnailFish.CBP_MSnailFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("SeaHorse"), ESearchCase::IgnoreCase))
	{
		TagName = "SeaHorse";
		ApplyCount[8]++;
		if (ApplyCount[8] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_SeaHorseFish.CBP_SeaHorseFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Shark"), ESearchCase::IgnoreCase))
	{
		TagName = "Shark";
		ApplyCount[9]++;
		if (ApplyCount[9] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_SharkFish.CBP_SharkFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Snipe"), ESearchCase::IgnoreCase))
	{
		TagName = "Snipe";
		ApplyCount[10]++;
		if (ApplyCount[10] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_Snipe_EelFish.CBP_Snipe_EelFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else if (_QRText.Equals(TEXT("Tripod"), ESearchCase::IgnoreCase))
	{
		TagName = "Tripod";
		ApplyCount[11]++;
		if (ApplyCount[11] > SpawnCount)
		{
			ActorPath = TEXT("Blueprint'/Game/Dev/BP/OceanVillage/Actors/Fish/CBP_TripodFish.CBP_TripodFish_C'");
			SpawnActor(ActorPath, TagName);
		}
	}
	else
	{
		return;
	}
	//서치 타이머 정지
	GetWorld()->GetTimerManager().PauseTimer(FileSearchTimerHandle);
}

FVector AOceanVillageGameMode::RandomLocation(const FVector& BaseLocation, float Radius, float Z_Radius)
{
	//생성 위치
	float RandomX = FMath::RandRange(BaseLocation.X - Radius, BaseLocation.X + Radius);
	float RandomY = FMath::RandRange(BaseLocation.Y - Radius, BaseLocation.Y + Radius);
	float RandomZ = FMath::RandRange(BaseLocation.Z - Z_Radius, BaseLocation.Z + Z_Radius);

	return FVector(RandomX, RandomY, RandomZ);
}

AActor* AOceanVillageGameMode::AssignRandomGuide(AActor* FishActor)
{
	// GuideActors가 비어 있는 경우 nullptr 반환
	if (GuideActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GuideActors available!"));
		return nullptr;
	}

	// AvailableGuideIndices 초기화
	if (AvailableGuideIndex.Num() == 0)
	{
		for (int32 i = 0; i < GuideActors.Num(); ++i)
		{
			AvailableGuideIndex.Add(i);
		}
	}

	// 랜덤으로 GuideActor 선택
	int32 RandomIndex = FMath::RandRange(0, AvailableGuideIndex.Num() - 1);
	int32 SelectedIndex = AvailableGuideIndex[RandomIndex];
	AActor* SelectedGuide = GuideActors.IsValidIndex(SelectedIndex) ? GuideActors[SelectedIndex] : nullptr;
	UE_LOG(LogTemp, Log, TEXT("Selected Index: %d"), SelectedIndex);
	// 선택된 GuideActor의 인덱스를 사용 가능한 목록에서 제거
	AvailableGuideIndex.RemoveAt(RandomIndex);

	return SelectedGuide;
}


void AOceanVillageGameMode::SpawnActor(FString ActorPath, FName _TagName)
{
	// 액터 생성	
	FString BlueprintPath = ActorPath;
	UClass* BlueprintActorClass = LoadObject<UClass>(nullptr, *BlueprintPath);
	AActor* GuideActor;
	if (BlueprintActorClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CheckNewFile::LoadFile Not Found"));
		return;
	}

	FVector BaseLocation = FVector(24000.0f, -5950.0f, 3930.0f);
	FVector Location = RandomLocation(BaseLocation, 100, 100);
	FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (_TagName == NAME_None)
	{
		GuideActor = GetWorld()->SpawnActor<AActor>(BlueprintActorClass, Location, Rotation, SpawnParams);
	}
	else
	{
		SpawnedActor = GetWorld()->SpawnActor<ATextureFishCharacter>(BlueprintActorClass, Location, Rotation, SpawnParams);
		if (SpawnedActor)
		{
			SpawnedActor->Tags.Add(_TagName);
		}
	}

}


void AOceanVillageGameMode::FindSpawnPoints()
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

	//오
	/*if (FoundSpawnPoints.Num() > 0)
	{
		ATargetPoint* SpawnPoint = Cast<ATargetPoint>(FoundSpawnPoints[1]);
		if (SpawnPoint)
		{
			RightSpawnLocation = SpawnPoint->GetActorLocation();
			SpawnRotator = SpawnPoint->GetActorRotation();
		}
	}*/
}
