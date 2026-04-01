#include "Actors/StepActor/OceanVillage/AIController/OceanVillageAIController.h"
#include "Actors/StepActor/OceanVillage/TextureFishCharacter.h"

void AOceanVillageAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    // AI 캐릭터에게 다음 포인트로 이동 요청
   /* if (ATextureFishCharacter* MyCharacter = Cast<ATextureFishCharacter>(GetCharacter()))
    {
        MyCharacter->MoveToNextTarget();
    }*/
}
