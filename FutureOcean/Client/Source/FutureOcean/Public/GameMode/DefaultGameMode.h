

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Protocols.h"
#include "DefaultGameMode.generated.h"


class ASoundManager;
/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void SetStepManagers(TArray<AStepManager*> _StepManagers);

	UFUNCTION(BlueprintCallable)
	void SetSoundManager(ASoundManager* _soundManager);

	UFUNCTION(BlueprintCallable)
	void SetWidgetActor(ADefaultManager* _WidgetActor) { WidgetActor = _WidgetActor; }

public:
	UFUNCTION(BlueprintCallable)
	AStepManager* GetCurrentStepManager(int StepManagerNum);

	UFUNCTION(BlueprintCallable)
	ADefaultManager* GetWidgetActor() { return WidgetActor; }

	UFUNCTION(BlueprintCallable)
	void Call_AnimFadeWidget(bool IsFadeIn);

	//void Call_FadeImageOp(float _op);

	UFUNCTION(BlueprintCallable)
	void Call_WidgetSwitcherIndex(int _index);

	UFUNCTION(BlueprintCallable)
	void Call_LevelEnd(int StepManagerNum);
	void Call_StepManager_SkipStep(int StepManagerNum);
	void Call_StepManager_CmsIsStart(int StepManagerNum, bool _IsStart);

	void Call_SetCustomSound(uint8 _type, class USoundBase* _sound);
	void Call_PlayCustomSound(uint8 _soundType, uint8 _volumeType);

	void Call_WorldPlayEffectSounds(EFFECT_SOUND_TYPE _type);

private:
	AStepManager* CurrStepManager = nullptr;
	ASoundManager* SoundManager = nullptr;
	ADefaultManager* WidgetActor = nullptr;

	TMap<int, AStepManager*> InWorldAllManager;
};
