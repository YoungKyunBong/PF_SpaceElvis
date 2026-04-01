// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/DownLoadWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UDownLoadWidget::C_Init()
{
	for(int i = 0; i < prograssbars.Num(); i++)
		prograssbars[i]->SetVisibility(ESlateVisibility::Hidden);
}

void UDownLoadWidget::SetDefault()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetCanvasPanelVisible(ESlateVisibility::Hidden);
	DownLoadLevelName = "";
	Percent = 0;
	for (int i = 0; i < prograssbars.Num(); i++)
	{
		prograssbars[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UDownLoadWidget::SetPercent(float _percent)
{
	int PercentToInt = (int)(_percent * 100);

	if (PercentToInt < 100)
	{
		PercentText = FString::FromInt(PercentToInt) + "%";

		if (PercentToInt % 10 == 0 && (int)(Percent * 100) != PercentToInt)
		{
			Percent = _percent;
			prograssbars[PercentToInt / 10 - 1]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		ChangeTextDownLoading();
	}
}

void UDownLoadWidget::DownLoadEnd_Implementation(bool IsDownLoadCancel)
{
	if(!IsDownLoadCancel)
		ChangeTextUnZip();
	else
	{
		DefaultText = DownLoadLevelName + downLoadStateText;
	}
}

void UDownLoadWidget::UnZipEnd_Implementation()
{
	PercentText = "100%";
	prograssbars[prograssbars.Num() - 1]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	IsFirstPlay = true;
	DefaultText = DownLoadLevelName + downLoadStateText;

	//if (IsVisibleCheckButton)
	SetCanvasPanelVisible(ESlateVisibility::SelfHitTestInvisible);
}

void UDownLoadWidget::SetCanvasPanelVisible(ESlateVisibility _visible)
{
	C_DownLoadCheckCanvasPanel->SetVisibility(_visible);
}

void UDownLoadWidget::SetText_CompleteDownLoad()
{
	downLoadStateText = TEXT(" 설치 완료");
	//IsVisibleCheckButton = true;
}

void UDownLoadWidget::SetText_CancelDownLoad()
{
	downLoadStateText = TEXT(" 설치 중단");
	//IsVisibleCheckButton = false;
}
