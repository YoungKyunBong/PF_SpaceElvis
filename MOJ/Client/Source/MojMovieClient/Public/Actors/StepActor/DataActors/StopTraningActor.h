// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActor/StepActor.h"
#include "StopTraningActor.generated.h"

UENUM(BlueprintType)
enum class ProcessIconType : uint8
{
	ProcessStart = 0x00,
	ProcessStop = 0x01,
	ProcessThink = 0x02,
	ProcessOptions = 0x03,
	ProcessPick = 0x04,
};
/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AStopTraningActor : public AStepActor
{
	GENERATED_BODY()
public:
	virtual void CmsSectionMovement() override;

protected:
	UPROPERTY(EditAnywhere);
	MovieSceneType stopStartSceneTypes;

	UPROPERTY(EditAnywhere);
	TArray<MovieSceneType> startSceneTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> ThinkButtonTextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> OptionButtonTextID;

	UPROPERTY(EditAnywhere);
	TArray<MovieSceneType> cureSceneTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NarrEndDelay = 0.5f;

	UPROPERTY(BlueprintReadWrite)
	ProcessIconType processIconType;

protected:
	void SetTextToWidget(FString TextID);
	void SetButtonTextToWidget();

protected:
	UFUNCTION(BlueprintCallable)
	void Call_PlayMovie(ProcessIconType _type);

	UFUNCTION(BlueprintCallable)
	void ChangeScene();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelay();

	UFUNCTION(BlueprintCallable)
	void SetMovieDelayPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetThinkText(ProcessIconType _type);

	UFUNCTION(BlueprintCallable)
	void SetOptionText(ProcessIconType _type);

	UFUNCTION(BlueprintCallable)
	void PlayNarr(FString SoundID);

	UFUNCTION(BlueprintCallable)
	void SetNarrationPaused(bool IsPlay);

	UFUNCTION(BlueprintCallable)
	void SetBeforeSelectIndex(FSelectButton selectButton);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Step")
	void PlayMovie(ProcessIconType _type);
	UFUNCTION(BlueprintCallable, Category = "Step")
	virtual void PlayMovie_Implementation(ProcessIconType _type);
	
	UPROPERTY(BlueprintReadOnly)
	bool isSelect = true;
private:
	FTimerHandle Handle;

	int CureIndex = 0;
	int processIndex = 0;

	void SetTimer_MovieDelay();

	void SetTimer_PlayNarr();


};
