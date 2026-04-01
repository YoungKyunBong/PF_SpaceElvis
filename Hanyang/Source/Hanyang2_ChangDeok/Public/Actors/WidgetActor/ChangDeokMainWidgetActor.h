// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "ChangDeokMainWidgetActor.generated.h"

/**
 * 
 */

class ALevelScriptActor_ChangDeokMain;

//USTRUCT(Atomic, BlueprintType)
//struct FMyStructTest
//{
//	GENERATED_USTRUCT_BODY()
//protected:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int a;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int b;
//};

UCLASS()
class HANYANG2_CHANGDEOK_API AChangDeokMainWidgetActor : public ADefaultManager
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	virtual void SetTextToWidget(FString TextID) override;

	void OnPressed_CallNextStep(int StepManagerNum);

	void OnPressed_CallResetSkip(int StepManagerNum);

	virtual void CustomFadeIn() override;

	virtual void CustomFadeOut() override;

	virtual void SetMainWidgetDefault() override;

	virtual void SetSoundPlay(bool IsPaused) override;

	virtual float Call_DownLoadPercent() override;

	virtual void Call_SetHttpData(FString _Path, FString _Name) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<int, FMyStructTest> structMapTest;
private:
	ALevelScriptActor_ChangDeokMain* LevelBP;

};