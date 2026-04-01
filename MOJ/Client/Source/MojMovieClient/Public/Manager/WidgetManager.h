// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InsideDataStruct.h"
#include "Manager/DefaultManager.h"
#include "WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class MOJMOVIECLIENT_API AWidgetManager : public ADefaultManager
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	class UMainWidget* MainWidget;

protected:
	virtual void Init() override;

protected:
	UFUNCTION(BlueprintCallable)
	void SendTrackingNumber(FString hitNum);

public:
	virtual void SetWidgetSwitchIndex(int index) override;
	virtual void SetNarrText(FString _HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton) override;
	virtual void InmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton) override;
	virtual void InmateKeywordCardButton(TArray<FSelectButton> buttonText) override;
	virtual void SetWidgetVisible(ESlateVisibility option) override;
	virtual void SetIconType(CheckIconType _checkIconType) override;

private:
	UFUNCTION()
	void MyStepSectionMovement();
};
