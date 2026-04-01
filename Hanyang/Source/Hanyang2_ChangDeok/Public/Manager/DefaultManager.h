// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../GameManager.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "DefaultManager.generated.h"

class UGameManager;
class ADefaultGameMode;

UCLASS()
class HANYANG2_CHANGDEOK_API ADefaultManager : public AActor
{
	GENERATED_BODY()

private:
	UGameManager* GameIns;
	ADefaultGameMode* GameMode;

protected:
	UFUNCTION(BlueprintCallable)
	void SetGameManager(UGameManager* _GameIns) { GameIns = _GameIns; }

	UFUNCTION(BlueprintCallable)
	void SetGameMode(ADefaultGameMode* _GameMode) { GameMode = _GameMode; }

public:
	UFUNCTION(BlueprintCallable)
	UGameManager* GetGameManager() { return GameIns; }

	UFUNCTION(BlueprintCallable)
	ADefaultGameMode* GetGameMode() { return GameMode; }

	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetVisibility(bool IsVisible) {}

	virtual void SetTextToWidget(FString TextID) {}
	virtual void SetSkipButtonText(FString Text) {}
	virtual void CustomFadeIn() { }
	UFUNCTION(BlueprintCallable)
	virtual void CustomFadeOut() { }
	virtual void SetMainWidgetDefault() {}
	virtual void SetSubTextToWidget(FString TextID, double margin_Top, float _fontSize){}
	virtual void SetSubWidgetHidden(){}

	virtual void SetSoundPlay(bool IsPaused){}

	UFUNCTION(BlueprintNativeEvent)
	void SetCustomTimeOfDay(float _timeOfDay);
	UFUNCTION(BlueprintCallable)
	virtual void SetCustomTimeOfDay_Implementation(float _timeOfDay) {}

	virtual float Call_DownLoadPercent() { return 0.0f; }
	virtual void Call_SetHttpData(FString _Path, FString _Name){}

	FHttpDownloadCheck* GetFHttpDownloadCheck() { return &GameIns->HttpDownloadCheck; }
	FHttpDownloadEnd* GetFHttpDownloadEnd() { return &GameIns->HttpDownloadEnd; }
	FUnZipEndState* GetFUnZipEndState() { return &GameIns->UnZipEndState; }
	void Call_CancelDownLoad() { GameIns->CancelDownLoad(); }
};
