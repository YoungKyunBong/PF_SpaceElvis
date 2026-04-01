#include "Actors/StepActor/CleaningOcean/FloorTrashActor.h"
#include "Manager/CleaningOcean/Floor_CleaningOceanManager.h"
//#include "Manager/CleaningOcean/CleaningOceanFloorManager.h"
//#include "Actors/StepActor/CleaningOcean/WhaleCharacter.h"
#include "Sound/AmbientSound.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>

void AFloorTrashActor::Init(AFloor_CleaningOceanManager* _manager)
{
	floorManager = _manager;
	MaterialCount = SMC_FloorTrash->GetNumMaterials();
	for (int i = 0; i < MaterialCount; ++i)
	{
		MInsDyns.Add(SMC_FloorTrash->CreateDynamicMaterialInstance(i));
	}
	//floorManager->SendPlayWhaleSound();	
	//GetAmbientSounds();
}

void AFloorTrashActor::ChangeOpValue()
{
	if (bOverlap == true)
	{
		return;
	}	
	
	OpValue -= OpChangeValue;
	if (FMath::IsNearlyEqual(OpValue, 0.0f, KINDA_SMALL_NUMBER))
	{
		OpValue = 0.f;
		bOverlap = true;

		floorManager->SendPlayWhaleSound();		
		C_Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		NS_CleanClear();		
	}

	for (int i = 0; i < MaterialCount; ++i) {
		MInsDyns[i]->SetScalarParameterValue("Fade_Out", OpValue);
	}
}

void AFloorTrashActor::TempSetMesh(UMaterialInterface* _DefaultWidgetClass)
{
	SMC_FloorTrash->SetStaticMesh(TempMesh);

	/*MaterialCount = SMC_FloorTrash->GetNumMaterials();

	for (int i = 0; i < MaterialCount; ++i)
	{
		SMC_FloorTrash->SetMaterial(i, _DefaultWidgetClass);
	}*/
}

//void AFloorTrashActor::GetAmbientSounds()
//{
//	TArray<AActor*> FoundAmbientSounds;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientSound::StaticClass(), FoundAmbientSounds);
//	SoundActors.Empty();
//	for (int i = 0; i < FoundAmbientSounds.Num(); ++i)
//	{
//		AAmbientSound* TargetPoint = Cast<AAmbientSound>(FoundAmbientSounds[i]);
//		SoundActors.Add(TargetPoint);
//	}
//}

//void AFloorTrashActor::PlaySound()
//{
//	ClearTrash++;
//	SoundActors[0]->Play();
//	float FadeDuration = 0.0f;
//	float TargetVolume = 1.0f / ClearTrash;
//	SoundActors[0]->AdjustVolume(FadeDuration, TargetVolume);
//
//	Whale->SetClearIndex();
//}

//void AFloorTrashActor::SendToServer()
//{
//	if (UWorld* World = GetWorld())
//	{
//		UCleaningOceanFloorManager* Manager = World->GetSubsystem<UCleaningOceanFloorManager>();
//		if (Manager)
//		{
//			Manager->SendPlayWhaleSound();
//			Manager->GetSoundType();
//		}
//	}
//}


