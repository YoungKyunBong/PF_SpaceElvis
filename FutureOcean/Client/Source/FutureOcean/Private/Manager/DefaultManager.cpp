
#include "Manager/DefaultManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Actors/CommonActor/KelpForest/PlaySequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"

//void ADefaultManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	//GetGameManager()->Send_CmsControllerStop();
//}

void ADefaultManager::C_Init()
{
	CustomInit();

	//GetGameManager()->RecvCleaningLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));

	GetGameManager()->RecvInfoMovieEnd.AddUFunction(this, FName("RecvInfoMovieLevelEnd"));
	GetGameManager()->RecvCoralEnd.AddUFunction(this, FName("RecvCoralLevelEnd"));
	GetGameManager()->RecvCleaningOceanEnd.AddUFunction(this, FName("RecvLevelEnd"));
	GetGameManager()->RecvOilEnd.AddUFunction(this, FName("RecvLevelEnd"));
	//GetGameManager()->RecvCamouFishEnd.AddUFunction(this, FName("RecvLevelEnd"));

	GetGameManager()->RecvCmsControllerStart.AddUFunction(this, FName("RecvCmsStart"));
	GetGameManager()->RecvCmsControllerStop.AddUFunction(this, FName("RecvCmsStop"));
	GetGameManager()->RecvCmsControllerSkip.AddUFunction(this, FName("RecvLevelEnd"));
	GetGameManager()->RecvCmsControllerReset.AddUFunction(this, FName("RecvCmsReset"));
	GetGameManager()->RecvCmsControllerNewPlayer.AddUFunction(this, FName("RecvCmsNewPlayerReset"));

	GetGameManager()->RecvOceanCleanChange.AddUFunction(this, FName("RecvOceanCleanChange"));
	GetGameManager()->RecvPlayTimeOutEvent.AddUFunction(this, FName("RecvPlayTimeOutEvent"));

	checkTestGame = GetGameManager()->GetIsTestGame();

	envFloatValue_TimelineCallback.BindUFunction(this, FName("Binding_EnvFloatUpdate"));
	envFloatValue_TimelineFinishedCallback.BindUFunction(this, FName("Binding_EnvFloatFinished"));

	envColorValue_TimelineCallback.BindUFunction(this, FName("Binding_EnvColorUpdate"));
	envColorValue_TimelineFinishedCallback.BindUFunction(this, FName("Binding_EnvColorFinished"));
}

void ADefaultManager::RecvLevelEnd()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	GetGameMode()->Call_LevelEnd(0);
}

void ADefaultManager::RecvCmsStart()
{
	SetCmsIsStart(true);
	IsCmsState = true;
}

void ADefaultManager::RecvCmsStop()
{
	SetCmsIsStart(false);
	IsCmsState = false;
}

void ADefaultManager::RecvCmsReset(RESET_TYPE _type)
{
	switch (_type)
	{
	case RESET_TYPE::WorldReset:
	{
		switch (GameIns->GetPlaceType())
		{
		case PROTOCOLSUB_TYPE::Wall:
			UGameplayStatics::OpenLevel(GetWorld(), "InfoMovie_Wall_Dev");
			break;
		case PROTOCOLSUB_TYPE::Floor:
			UGameplayStatics::OpenLevel(GetWorld(), "InfoMovie_Floor_Dev");
			break;
		default:
			break;
		}
	}
		break;
	case RESET_TYPE::LevelReset:
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
		break;
	default:
		break;
	}
}

void ADefaultManager::RecvCmsNewPlayerReset(FString _levelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), (FName)_levelName);
}

void ADefaultManager::RecvOceanCleanChange()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvOceanCleanChange"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroSucessType);
}

void ADefaultManager::SendOceanCleanChange()
{
	GameIns->Send_OceanCleanChange();
}

void ADefaultManager::RecvPlayTimeOutEvent()
{
	PlaySequenceActor->CustomClearSequence();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvPlayTimeOutEvent"));
	PlaySequenceActor->PlaySequence(Lv_Sq_Type::OutroFailType);
}

void ADefaultManager::ChangeEnvironment_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	SetTimeLine_EnvFloatValue();
}

void ADefaultManager::TimeOutEvent()
{
	GetGameManager()->Send_PlayTimeOutEvent();
}

//<<------------------------------------------------------------------------------ юс╫ц
void ADefaultManager::SendCmsPlay()
{
	GetGameManager()->Send_CmsControllerStart();
}

void ADefaultManager::SendCmsStop()
{
	GetGameManager()->Send_CmsControllerStop();
}

void ADefaultManager::SendCmsSkip()
{
	GetGameManager()->Send_CmsControllerSkip();
}

void ADefaultManager::SendCmsReset(RESET_TYPE _type)
{
	GetGameManager()->Send_CmsControllerReset(_type);
}

void ADefaultManager::SendTempBgWall()
{
	GetGameManager()->Send_TempBG_Wall();
}

void ADefaultManager::SendTempBgFloor()
{
	GetGameManager()->Send_TempBG_Floor();
}

//>>-----------------------------------------------------------------------------

void ADefaultManager::Binding_EnvFloatUpdate(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	C_PostProcessVolume->Settings.ColorGamma = FMath::Lerp(PostProcessValue_ColorGamma_Before, PostProcessValue_ColorGamma_After, Value);
	//C_PostProcessVolume->Settings.BloomIntensity = FMath::Lerp(PostProcessValue_BloomIntensity_Before, PostProcessValue_BloomIntensity_After, Value);
	//C_PostProcessVolume->Settings.AutoExposureBias = FMath::Lerp(PostProcessValue_AutoExposureBias_Before, PostProcessValue_AutoExposureBias_After, Value);
	//C_PostProcessVolume->Settings.LocalExposureHighlightContrastScale = FMath::Lerp(PostProcessValue_LocalExposureHighlightContrastScale_Before, PostProcessValue_LocalExposureHighlightContrastScale_After, Value);
	//C_PostProcessVolume->Settings.LocalExposureDetailStrength = FMath::Lerp(PostProcessValue_LocalExposureDetailStrength_Before, PostProcessValue_LocalExposureDetailStrength_After, Value);
	//C_PostProcessVolume->Settings.ColorSaturation = FMath::Lerp(PostProcessValue_ColorSaturation_Before, PostProcessValue_ColorSaturation_After, Value);
	//C_PostProcessVolume->Settings.Sharpen = FMath::Lerp(PostProcessValue_Sharpen_Before, PostProcessValue_Sharpen_After, Value);

	//C_ExponentialHeightFog->GetComponent()->SetFogInscatteringColor(FMath::Lerp(ExponentialHeightFog_FogInscatteringColor_Before, ExponentialHeightFog_FogInscatteringColor_After, Value));
}

void ADefaultManager::Binding_EnvFloatFinished()
{
	
}

void ADefaultManager::Binding_EnvColorUpdate(FLinearColor Value)
{
}

void ADefaultManager::Binding_EnvColorFinished()
{
}
