// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Manager/GameManager.h"
#include "WidgetActor/LogRowWidget.h"
#include "LogListWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOJCMSCLIENT_API ULogListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UScrollBox* SB_LogList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ULogRowWidget> RowWidgetClass;

private:
	UGameManager* GM = nullptr;

	void Rebuild();
	void OnLogUpdated();
};
