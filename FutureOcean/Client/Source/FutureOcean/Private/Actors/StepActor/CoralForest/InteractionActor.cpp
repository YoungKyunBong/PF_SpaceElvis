
#include "Actors/StepActor/CoralForest/InteractionActor.h"
#include "Manager/CoralForest/Floor_CoralForestManager.h"
#include "Manager/KelpForest/InteractionManager.h"
#include "Actors/StepActor/CoralForest/GrabActor.h"
#include "Components/BoxComponent.h"

void AInteractionActor::Init(AFloor_CoralForestManager* _manager)
{
	//if (InteractionActorManager = GetWorld()->GetSubsystem<UInteractionManager>())
	//{
	//	InteractionActorManager->RegisterInteractionActor(this);
	//}
	floorManager = _manager;

	DepthSwitch();
	//VisibilitySwitch();
}

void AInteractionActor::TempSetMesh()
{
	InteractionActor->SetStaticMesh(TempMesh);
}

void AInteractionActor::DepthSwitch(bool bEnable)
{
	InteractionActor->SetRenderCustomDepth(bEnable);
}

void AInteractionActor::VisibilitySwitch(bool bEnable)
{
	InteractionActor->SetVisibility(bEnable);
}

bool AInteractionActor::Get_GrabActor(AActor* _OtherACtor)
{
	AGrabActor* CastGrabActor = Cast<AGrabActor>(_OtherACtor);
	if (CastGrabActor == nullptr)
	{
		return false;
	}
	else if (CastGrabActor == GrabActor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AInteractionActor::DestroyActor()
{
	if (this != nullptr) {
		Destroy();
	}
}

void AInteractionActor::SetCollisionInteractionMesh(ECollisionEnabled::Type _collisionChannel)
{
	C_Trigger->SetCollisionEnabled(_collisionChannel);
}

void AInteractionActor::BeginOverlapFlow(AActor* _OtherACtor, UMaterialInterface* _DefaultWidgetClass)
{
	bool bCast_GrabActor = Get_GrabActor(_OtherACtor);

	if (bCast_GrabActor == true) {
		DepthSwitch();
		floorManager->SendOverlapToServer(CoralType);
		//InteractionActorManager->SendOverlapToServer(CoralType);
		
		/*if (FlagCoralActor != nullptr)
			FlagCoralActor->SetMaterial(_DefaultWidgetClass);*/

		if (GrabActor != nullptr)
			GrabActor->Detach_Actor();
		DestroyActor();
	}
}
