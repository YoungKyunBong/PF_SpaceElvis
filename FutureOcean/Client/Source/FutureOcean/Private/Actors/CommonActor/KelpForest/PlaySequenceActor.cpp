
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Manager/KelpForest/Wall_KelpForestManager.h"

void APlaySequenceActor::CustomInit(ADefaultManager* _manager)
{
	//if (IsWall)
		wallManager = _manager;
}

void APlaySequenceActor::PlaySequence_Implementation(Lv_Sq_Type _type)
{
	if(_type != Lv_Sq_Type::Cms_Type)
		currType = _type;
}

void APlaySequenceActor::Call_OilLevelEnd()
{
	CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Call_OilLevelEnd"));
	//if (IsWall)
	{
		switch (currType)
		{
		case Lv_Sq_Type::IntroType:
			wallManager->Call_Intro_SQ_End();
			break;
		case Lv_Sq_Type::OutroSucessType:
		case Lv_Sq_Type::OutroFailType:
			wallManager->Call_DefaultLevelEnd();
			break;
		case Lv_Sq_Type::InteractionType:
			wallManager->Call_Interaction_SQ_End();
			break;
		case Lv_Sq_Type::Cms_Type:
			break;
		default:
			break;
		}
	}
}
