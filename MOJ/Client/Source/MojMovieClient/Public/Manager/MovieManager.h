// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "MovieManager.generated.h"

class UMediaSource;

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AMovieManager : public ADefaultManager
{
	GENERATED_BODY()

public:
	virtual void Init() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void MoviePlay();
	UFUNCTION(BlueprintCallable)
	virtual void MoviePlay_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void MoviePause();
	UFUNCTION(BlueprintCallable)
	virtual void MoviePause_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void CmsMovieClose();
	UFUNCTION(BlueprintCallable)
	virtual void CmsMovieClose_Implementation() {}

public:
	virtual void SetMoviePlay() override;
	virtual void SetMoviePause() override;
	virtual void SetChangeMovieScene(MovieSceneType _type) override;

	virtual float GetMediaPlayTime() override { return MediaPlayTime; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	TArray<UMediaSource*> VideoSources;

	UPROPERTY(BlueprintReadOnly, Category = "Media")
	UMediaSource* ChangeMovieSource;

protected:
	UFUNCTION(BlueprintCallable)
	void SetMediaPlayTime(float time) { MediaPlayTime = time; }

protected:
	UFUNCTION(BlueprintNativeEvent)
	void NextSceneOpenSource();
	UFUNCTION(BlueprintCallable)
	virtual void NextSceneOpenSource_Implementation() {}

private:
	UFUNCTION()
	void CmsMoviePlay();

	UFUNCTION()
	void CmsMoviePause();

	bool IsFirstPlay = false;

	float MediaPlayTime;
};
