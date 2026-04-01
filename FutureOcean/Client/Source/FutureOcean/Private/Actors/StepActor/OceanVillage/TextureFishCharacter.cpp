#include "Actors/StepActor/OceanVillage/TextureFishCharacter.h"
#include "Actors/StepActor/OceanVillage/GameMode/OceanVillageGameMode.h"
#include "Manager/OceanVillage/Wall_OceanVillageManager.h"
#include "Actors/StepActor/OceanVillage/GuideActor.h"
#include "FishAsyncTexLoader.h"
#include "Engine/TargetPoint.h"
#include <ImageUtils.h>
#include <Windows.h>
#include "../Protocols.h"


// Sets default values
ATextureFishCharacter::ATextureFishCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATextureFishCharacter::EndPlay(const EEndPlayReason::Type Reason)
{
	if (RuntimeLoader) RuntimeLoader->Cancel();   // ③ Play 중단 시 안전하게 취소
	Super::EndPlay(Reason);
	UE_LOG(LogTemp, Warning, TEXT("ATextureFishCharacter::Safe EndPlay"));
}

void ATextureFishCharacter::CustomInit_Implementation(AWall_OceanVillageManager* _manager)
{
	CastGameMode = _manager;
	//IsMove(true);
}

AActor* ATextureFishCharacter::RandomPoint(TArray<AActor*> PointActors)
{
	AActor* RandomPoint = GetRandomArrayItemNoRepeat(PointActors, AvailableIndex);

	return RandomPoint;
}

void ATextureFishCharacter::ApplyMaterial(const FString& InPngPath)
{
	FishTagName = CastGameMode->Get_FishTagName();
	RuntimeLoader =	UFishAsyncTexLoader::LoadTextureAsync(this, InPngPath, FishTagName);
	RuntimeLoader->OnLoaded.AddDynamic(this, &ATextureFishCharacter::OnTextureReady);
}

void ATextureFishCharacter::OnTextureReady(UTexture2D* Texture, FName TagName, FString Error)
{
	if (!Texture)
	{		
		UE_LOG(LogTemp, Error, TEXT("Fish texture load failed: %s"), *Error);
		return;
	}	
	if (!Tags.Contains(TagName))
	{
		return;
	}

	RuntimeTex = Texture;
	
	if (!MInsDyns)
		MInsDyns = TextureObejct->CreateDynamicMaterialInstance(0);

	MInsDyns->SetTextureParameterValue(FName("Line_Texture"), RuntimeTex);

	// 5)사운드
	if (!bSpawnFish)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Only Texture"));
		CastGameMode->SendPlayEffectSound(EFFECT_SOUND_TYPE::SoundType1);
		ApplyMaterialEffect();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Only Spawn"));
		CastGameMode->SendPlayEffectSound(EFFECT_SOUND_TYPE::SoundType1);
		SpawnFishEffect();
		UE_LOG(LogTemp, Log, TEXT("SpawnFishEffect Call"));
	}
	if (Tags.Contains(FishTagName))
	{
		Tags.Remove(FishTagName);
		FishTagName = NAME_None;
		//Tags.Add(TEXT("Left"));
		UE_LOG(LogTemp, Log, TEXT("Tag %s removed"), *CastGameMode->Get_FishTagName().ToString());
	}
	Delete_Texture();
}

//
//void ATextureFishCharacter::ApplyMaterial()
//{
//	FishTagName = CastGameMode->Get_FishTagName();
//	customMakeTexture = CastGameMode->Get_CustomTexture();
//
//	if (customMakeTexture == nullptr)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed::customMakeTexture"));
//		return;
//	}
//
//	if (Tags.Contains(FishTagName))
//	{
//		AsyncTask(ENamedThreads::GameThread, [this]()
//			{
//				SetTempMaterial(customMakeTexture);
//				TimerControl();
//			});
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("FoundTagName::Failed"));
//		return;
//	}
//}

AActor* ATextureFishCharacter::GetRandomArrayItemNoRepeat(const TArray<AActor*>& Array, TArray<int32>& _AvailableIndex)
{
	/*전 인덱스 중복 방지*/
	//// 배열이 비어있는 경우 nullptr 반환
	//if (Array.Num() == 0)
	//{		
	//	return nullptr;
	//}

	//int32 NewIndex = _LastIndex;
	//while (NewIndex == _LastIndex)
	//{
	//	NewIndex = FMath::RandRange(0, Array.Num() - 1);		
	//}
	//
	//// 인덱스를 업데이트하고 선택된 항목 반환
	//_LastIndex = NewIndex;
	//
	//return Array[NewIndex];

	  // 배열이 비어있으면 nullptr 반환
	if (Array.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Array.Num(): %d"), Array.Num());
		return nullptr;
	}

	// 사용 가능한 인덱스 초기화
	if (_AvailableIndex.Num() == 0)
	{
		_AvailableIndex.Reserve(Array.Num());
		for (int32 i = 0; i < Array.Num(); ++i)
		{
			_AvailableIndex.Add(i);
		}
	}

	// 랜덤으로 인덱스 선택
	int32 RandomIndex = FMath::RandRange(0, _AvailableIndex.Num() - 1);
	int32 SelectedIndex = _AvailableIndex[RandomIndex];
	// 선택된 인덱스 제거
	UE_LOG(LogTemp, Log, TEXT("RandomIndex Index: %d"), RandomIndex);
	_AvailableIndex.RemoveAt(RandomIndex);
	// 선택된 항목 반환
	UE_LOG(LogTemp, Log, TEXT("Selected Index: %d"), SelectedIndex);
	return Array.IsValidIndex(SelectedIndex) ? Array[SelectedIndex] : nullptr;
}

void ATextureFishCharacter::SetChangeTarget_ToFish(AGuideActor* _currTargetActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SkipStep"));
	SetHoming(_currTargetActor ? _currTargetActor->GetRootComponent() : nullptr);
}

void ATextureFishCharacter::Delete_Texture()
{
	FullPath = CastGameMode->Get_FullPath();
	//텍스처 삭제
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]() {
		if (FPaths::FileExists(FullPath))
		{
			IFileManager& FileManager = IFileManager::Get();
			FileManager.Delete(*FullPath);
		}
		});
}

void ATextureFishCharacter::TimerControl()
{
	//FTimerHandle GameModeTimerHandle = CastGameMode->Get_FileSearchTimerHandle();
	///*게임모드 핸들*/
	//GetWorld()->GetTimerManager().UnPauseTimer(GameModeTimerHandle);
	//UE_LOG(LogTemp, Log, TEXT("Apply Material: UnPause Timer"));	

}

void ATextureFishCharacter::SetTargetPoints(TArray<ATargetPoint*> Points)
{
	TargetPoints = Points;
}

void ATextureFishCharacter::SetTempMaterial(UTexture2D* Texture)
{
	if (Texture)
	{
		// 다이내믹 머티리얼 인스턴스 생성
		/*UMaterialInterface* _DefaultWidgetClass = LoadObject<UMaterialInterface>(NULL, TEXT("Material'/Game/Dev/Material/M_TempFish_Inst.M_TempFish_Inst'"));
		MInsDyns = UMaterialInstanceDynamic::Create(_DefaultWidgetClass, this);*/

		// 텍스처 설정 전 압축 및 스트리밍 설정 최적화
		Texture->CompressionSettings = TC_VectorDisplacementmap; // 또는 상황에 맞는 압축 설정	

		// Tag를 지우는 코드
		if (Tags.Contains(FishTagName))
		{
			Tags.Remove(FishTagName);
			UE_LOG(LogTemp, Log, TEXT("Tag %s removed"), *FishTagName.ToString());
		}

		MInsDyns = TextureObejct->CreateDynamicMaterialInstance(0);
		//MInsDyns->SetScalarParameterValue(FName("MipBiasParameter"), DesiredLODBias);
		//float DesiredLODBias = 7.0f; // 원하는 LOD bias 값		

		MInsDyns->SetTextureParameterValue(FName("Line_Texture"), Texture);
		TextureObejct->SetMaterial(0, MInsDyns);

		bApplyMaterial = true;
		CastGameMode->Set_CustomTexture();
		SpawnFishEffect();

		if (!bSpawnFish)
		{
			//CastGameMode->SendPlayEffectSound();
			ApplyMaterialEffect();
		}
		else
		{
			SpawnFishEffect();
			//CastGameMode->SendPlayEffectSound();
			UE_LOG(LogTemp, Log, TEXT("SpawnFishEffect Call"));
		}
	}
}
