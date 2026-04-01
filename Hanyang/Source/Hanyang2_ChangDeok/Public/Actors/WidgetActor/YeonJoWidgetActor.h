// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "YeonJoWidgetActor.generated.h"

/**
 * 
 */

class ALevelScriptActor_YeonJo;

UCLASS()
class HANYANG2_CHANGDEOK_API AYeonJoWidgetActor : public ADefaultManager
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();

	void SetEmissiveActorValues(float _TimeEmissive);

	virtual void SetTextToWidget(FString TextID) override;

	void OnPressed_CallNextStep(int StepManagerNum);

	void OnPressed_CallResetSkip(int StepManagerNum);

	virtual void CustomFadeIn() override;

	virtual void CustomFadeOut() override;

	virtual void SetMainWidgetDefault() override;

	virtual void SetWidgetVisibility(bool IsVisible) override;

	virtual void SetSkipButtonText(FString Text) override;

	virtual void SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize) override;

	virtual void SetSubWidgetHidden() override;

	virtual void SetSoundPlay(bool IsPaused) override;

	UPROPERTY(EditAnywhere)
	TArray<class ASetRenderDepthActor*> RenderDepthActors;

	UPROPERTY(EditAnywhere)
	TArray<class ASetRenderDepthActor*> RenderDepthActors_M2;

	UPROPERTY(EditAnywhere)
	TArray<class ALampActor*> LampActor_M2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AGetBPAllComp*> OthersBP;

protected:
	UPROPERTY(EditAnywhere)
	TArray<class AStaticMeshActor*> EmissiveActors;

	UPROPERTY(EditAnywhere)
	TArray<class AStaticMeshActor*> EmissiveActors_M2;

private:
	void SetEmissiveActorInsDyn();

	ALevelScriptActor_YeonJo* LevelBP;

	TArray<UMaterialInstanceDynamic*> EmissiveActorInsDyn;
};
