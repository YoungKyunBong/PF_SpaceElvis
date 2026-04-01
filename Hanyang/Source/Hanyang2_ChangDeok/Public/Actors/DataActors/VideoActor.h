// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/StepActors/StepActor.h"
//#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "VideoActor.generated.h"

/**
 * 
 */

class UMediaPlayer;
class UMediaSource;
class UMaterial;

UCLASS()
class HANYANG2_CHANGDEOK_API AVideoActor : public AStepActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMediaSource* MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Material;
};
