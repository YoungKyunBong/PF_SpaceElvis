#include "Actors/StepActor/CoralForest/GrabActor.h"
#include "Actors/StepActor/CoralForest/InteractionActor.h"
#include "Actors/StepActor/CoralForest/CoralPawn.h"


void AGrabActor::TempSetMesh()
{
	GrabActor->SetStaticMesh(TempMesh);
}

void AGrabActor::Get_CharacterActor(AActor* _OtherACtor)
{
	if (CoralPawn != nullptr) return;

	ACoralPawn* Player = Cast<ACoralPawn>(_OtherACtor);
	if (Player == nullptr) return;

	CoralPawn = Player;
}

void AGrabActor::Attach_Actor()
{
	if (CoralPawn == nullptr) return;

	int iAttachNum = CoralPawn->Get_AttachedActors_Cnt();

	if (iAttachNum == 0 && Check_Forward() == true) {
		bool bAttachSuccess = false;
		bAttachSuccess = AttachToActor(CoralPawn, FAttachmentTransformRules::KeepWorldTransform);
		if (InteractionActor == nullptr) return;

		InteractionActor->DepthSwitch(bAttachSuccess);
		InteractionActor->VisibilitySwitch(bAttachSuccess);
	}
}

void AGrabActor::BeginOverlapFlow(AActor* _OtherACtor)
{
	Get_CharacterActor(_OtherACtor);
	Attach_Actor();
}

bool AGrabActor::Check_Forward()
{
	if (CoralPawn == nullptr) return false;

	FVector vGrabLocation = GetActorLocation();
	FVector vCharacterLocation = CoralPawn->GetActorLocation();
	FVector vDirVector = vGrabLocation - vCharacterLocation;
	FVector vCharacterForward = CoralPawn->GetActorForwardVector();

	float fdot = FVector::DotProduct(vCharacterForward, vDirVector);

	if (fdot >= 0.f)
		return true;
	else
		return false;
}

void AGrabActor::DestroyActor()
{
	if (this != nullptr) {
		Destroy();
	}
}

void AGrabActor::Detach_Actor()
{
	if (this != nullptr) {
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		DestroyActor();
	}
}