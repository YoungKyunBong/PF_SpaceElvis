#include "Actors/StepActor/KelpForest/CleaningOilActor.h"
#include "Manager/KelpForest/Floor_KelpForestManager.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

void ACleaningOilActor::Init(AFloor_KelpForestManager* _manager)
{
	MInsDyn = DC_CleaningOil->CreateDynamicMaterialInstance();

	//OilActor를 매니저에 등록
	FloorManager = _manager;
	
}

void ACleaningOilActor::ChangeOpValue()
{
	if (bOverlap == false)
	{
		return;
	}
	OpValue -= OpChangeValue;
	if (OpValue <= 0.0f)
	{
		OpValue = 0.0f;
		bOverlap = false;
		MInsDyn->SetScalarParameterValue("OpValue", OpValue);		
		FloorManager->CheckDisableOilCount();
		NiagaraComponent->Activate();
		PlayCleaningSound();
		EndOverlap();
	}
	else
	{
		MInsDyn->SetScalarParameterValue("OpValue", OpValue);
		FloorManager->SendOilOverlapToServer();
	}
}

void ACleaningOilActor::SetCollisionInteractionMesh(ECollisionEnabled::Type _collisionChannel)
{
	C_Trigger->SetCollisionEnabled(_collisionChannel);
}


