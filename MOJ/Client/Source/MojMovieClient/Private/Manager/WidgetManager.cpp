// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "Widget/MainWidget.h"

void AWidgetManager::Init()
{
	Super::Init();

	MainWidget->Init(this);
	GetGameManager()->RecvCmsMovieClose.AddDynamic(this, &AWidgetManager::MyStepSectionMovement);
}

void AWidgetManager::SendTrackingNumber(FString hitNum)
{
	GetGameManager()->Send_HeadTrackingNum(FCString::Atoi(*hitNum));
}

void AWidgetManager::SetWidgetSwitchIndex(int index)
{
	MainWidget->SetWidgetSwitchIndex(index);
}

void AWidgetManager::SetNarrText(FString _HeaderText, FString _textID, bool IsID, bool _IsVisibleNarrNextButton)
{
	if(IsID)
		MainWidget->SetNarrText(_HeaderText != "" ? GetGameManager()->GetNaText(_HeaderText, GetGameMode()->GetNationType()) : _HeaderText, GetGameManager()->GetNaText(_textID, GetGameMode()->GetNationType()), _IsVisibleNarrNextButton);
	else
		MainWidget->SetNarrText(_HeaderText, _textID, _IsVisibleNarrNextButton);
}	

void AWidgetManager::InmateSelectButton(FString HeaderText, TArray<FSelectButton> buttonText, bool _IsVisibleNextButton)
{
	TArray<FSelectButton> GetButtonText;
	for (int i = 0; i < buttonText.Num(); i++)
	{
		FSelectButton temp;
		temp.buttonText = GetGameManager()->GetNaText(buttonText[i].buttonText, GetGameMode()->GetNationType());
		temp.feedBackText = buttonText[i].feedBackText;
		temp.feedBackText_Sub = buttonText[i].feedBackText_Sub;
		temp.feedBackSound = buttonText[i].feedBackSound;
		temp.movieType = buttonText[i].movieType;
		temp.buttonType = buttonText[i].buttonType;
		temp.emojiType = buttonText[i].emojiType;
		GetButtonText.Add(temp);
	}

	FString _headerText;
	if (HeaderText != "")
	{
		_headerText = GetGameManager()->GetNaText(HeaderText, GetGameMode()->GetNationType());
	}

	MainWidget->InmateSelectButton(_headerText, GetButtonText, _IsVisibleNextButton);
}

void AWidgetManager::InmateKeywordCardButton(TArray<FSelectButton> buttonText)
{
	TArray<FSelectButton> GetButtonText;
	for (int i = 0; i < buttonText.Num(); i++)
	{
		FSelectButton temp;
		temp.buttonText = GetGameManager()->GetNaText(buttonText[i].buttonText, GetGameMode()->GetNationType());
		temp.feedBackText = buttonText[i].feedBackText;
		temp.feedBackText_Sub = buttonText[i].feedBackText_Sub;
		temp.feedBackSound = buttonText[i].feedBackSound;
		temp.movieType = buttonText[i].movieType;
		temp.buttonType = buttonText[i].buttonType;
		temp.emojiType = buttonText[i].emojiType;
		GetButtonText.Add(temp);
	}

	MainWidget->InmateKeywordCardButton(GetButtonText);
}

void AWidgetManager::SetWidgetVisible(ESlateVisibility option)
{
	MainWidget->SetWidgetVisible(option);
}

void AWidgetManager::SetIconType(CheckIconType _checkIconType)
{
	MainWidget->SetIconType(_checkIconType);
}

void AWidgetManager::MyStepSectionMovement()
{
	SetWidgetVisible(ESlateVisibility::Hidden);
}
