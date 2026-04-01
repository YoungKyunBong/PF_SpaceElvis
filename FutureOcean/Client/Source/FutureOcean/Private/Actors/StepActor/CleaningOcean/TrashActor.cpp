#include "Actors/StepActor/CleaningOcean/TrashActor.h"
#include "Engine/TargetPoint.h"


// Sets default values
ATrashActor::ATrashActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

// Called every frame
void ATrashActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATrashActor::Init()
{
	
}

void ATrashActor::TempSetMesh(UMaterialInterface* _DefaultWidgetClass)
{
	//Construction Script 에디터 시점에서 설정하는 값
	SMC_TrashActor->SetStaticMesh(TempMesh);	
}

void ATrashActor::DestroyActor()
{
	if (this != nullptr) {
		Destroy();
	}
}

