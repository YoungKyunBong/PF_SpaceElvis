// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InmatePlayRoundWidget.generated.h"

class UMovieControlWidget;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UInmatePlayRoundWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetActiveButton();
	UFUNCTION(BlueprintCallable)
	virtual void SetActiveButton_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
	void SetDeActiveButton();
	UFUNCTION(BlueprintCallable)
	virtual void SetDeActiveButton_Implementation() {}

	UFUNCTION(BlueprintCallable)
	void Init(UMovieControlWidget* _movieControlWidget);

public:
	void SetPlayerRoundData(FString _sessionNum, FString _playRoundNum, FString _statusCode);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetWidgetData();
	UFUNCTION(BlueprintCallable)
	virtual void SetWidgetData_Implementation() {}

	UFUNCTION(BlueprintCallable)
	void ChangeStatusCode(FString text);

	UFUNCTION(BlueprintCallable)
	void Call_ProgramStart_OnClick();

public:
	UPROPERTY(BlueprintReadOnly)
	FString SessionNum;

	UPROPERTY(BlueprintReadOnly)
	FString PlayRoundNum;

	UPROPERTY(BlueprintReadOnly)
	FString StatusCode;

private:
	UMovieControlWidget* MovieControlWidget;
};
