// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChangDeokMain/PopupWidget.h"
#include "Actors/Widget/ChangDeokMain/PopupButtonWidget.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"

//void UPopupWidget::Init()
//{
//	LevelNames.Add("Popup_BackGround", "Level_ChangDeok_BackGround_Dev");
//	LevelNames.Add("Popup_Chijo", "Level_ChiJo_Dev");
//	LevelNames.Add("Popup_DaeBoDan", "Level_DaeBoDan_Dev");
//	LevelNames.Add("Popup_Oejo", "Level_OeJo_Dev");
//	LevelNames.Add("Popup_Yeonjo", "Level_YeonJo_Dev");
//}

void UPopupWidget::SetInfo(FPopupInfo _PopupInfo, FDownLoadData _DownLoadData, FString& _LauncherPath)
{
	DownLoadText = _PopupInfo.Name_Horizon + DownLoadNameText;
	PopupInfo = _PopupInfo;
	DownLoadData = _DownLoadData;

	FString tempText;
	tempText = _DownLoadData.FileName.Replace(TEXT(".zip"), TEXT(" "));
	tempText.RemoveSpacesInline();

	_LauncherPath = _DownLoadData.Path + tempText + "/Windows/Hanyang2_ChangDeok.exe";

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*(_LauncherPath)))
		C_ButtonSwitcher->SetActiveWidgetIndex(1);
	else
		C_ButtonSwitcher->SetActiveWidgetIndex(0);
}

void UPopupWidget::SetMainSwitcherIndex(int index)
{
	C_MainSwitcher->SetActiveWidgetIndex(index);
}

//void UPopupWidget::OnPressed_OpenLevel()
//{
//	UGameplayStatics::OpenLevel(GetWorld(), LevelNames[PopupInfo.PlaceSampleImage->GetFName()]);
//}