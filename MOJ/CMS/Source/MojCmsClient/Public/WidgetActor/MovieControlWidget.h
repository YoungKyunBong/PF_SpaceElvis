// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "MovieControlWidget.generated.h"

USTRUCT(BlueprintType)
struct FTempPlayerRoundData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SessionNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayRoundNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StatusCode;
};

class UInmateWidget;
class UInmatePlayRoundWidget;
class UInmateProgramLogWidget;
class UScrollBox;

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API UMovieControlWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UInmateWidget* _inmateWidget);

public:
	void SetInmateDataInfo();

	void RecvCmsNextRound();

	void RecvHeartRate(FString rate);

public:
	UFUNCTION(BlueprintNativeEvent)
	void RecvTrackingNum(int num);
	UFUNCTION(BlueprintCallable)
	virtual void RecvTrackingNum_Implementation(int num){}

	UFUNCTION(BlueprintNativeEvent)
	void CallProgramStartOnClick();
	UFUNCTION(BlueprintCallable)
	virtual void CallProgramStartOnClick_Implementation();

	void TempChangeCode(UInmatePlayRoundWidget* _widget);

protected:
	UFUNCTION(BlueprintCallable)
	void Call_Play_OnClick();

	UFUNCTION(BlueprintCallable)
	void Call_Pause_OnClick();

protected:
	UPROPERTY(BlueprintReadWrite)
	class UVerticalBox* VerticalBox;

	UPROPERTY(BlueprintReadWrite)
	UScrollBox* C_ScrollBox_LogText;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateName;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateNum;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_InmateHeartRate;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_CrimeType;

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* EditableTextBox_SituationNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTempPlayerRoundData> TempPlayerRoundDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UInmatePlayRoundWidget> TUInmatePlayRoundWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UInmateProgramLogWidget> TUInmateProgramLogWidget;

private:
	UInmateWidget* InmateWidget;

	TArray<UInmatePlayRoundWidget*> InmatePlayRoundWidgets;
};