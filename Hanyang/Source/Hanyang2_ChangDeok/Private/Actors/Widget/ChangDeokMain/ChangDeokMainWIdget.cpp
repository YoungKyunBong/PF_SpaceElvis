// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Widget/ChangDeokMain/ChangDeokMainWIdget.h"
#include "Actors/Widget/ChangDeokMain/PopupButtonWidget.h"
#include "Actors/Widget/ChangDeokMain/PopupWidget.h"
#include "Actors/Widget/ChangDeokMain/DescriptButtonWidget.h"
#include "Actors/Widget/TextWidget.h"
#include "Actors/WidgetActor/ChangDeokMainWidgetActor.h"
#include "Actors/Widget/FadeWidget.h"
#include "Actors/Widget/DownLoadWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanelSlot.h"

void UChangDeokMainWIdget::Init()
{
	CheckInit();
}

void UChangDeokMainWIdget::BeginInit()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(2);
	C_DescriptButtonWidget->OnClickDescriptButton();
}

void UChangDeokMainWIdget::SetPopupButtons(UPopupButtonWidget* BackGround, UPopupButtonWidget* Chijo, UPopupButtonWidget* Oejo, UPopupButtonWidget* Yeonjo, UPopupButtonWidget* DaeBoDan)
{
	BackGround->SetMainWidget(this);
	Chijo->SetMainWidget(this);
	Oejo->SetMainWidget(this);
	Yeonjo->SetMainWidget(this);
	DaeBoDan->SetMainWidget(this);
}

void UChangDeokMainWIdget::OnPressed_SkipButton()
{
	WidgetActor->OnPressed_CallResetSkip(C_DescriptButtonWidget->MyStepManagerNumber);
}

void UChangDeokMainWIdget::CheckInit_Implementation()
{
	C_WidgetSwitcher->SetActiveWidgetIndex(0);
	C_DescriptButtonWidget->Init();
	C_TextWidget->SetDefault();
	C_TextWidget->SetIsEnabled(false);
	OnPressed_TimeChangeButton(); 
}

void UChangDeokMainWIdget::SetPopupInfo_Implementation(UPopupButtonWidget* _Button)
{
	C_PopupWidget->SetPanelEnable(!IsDownLoadProcessing);
	C_PopupWidget->SetInfo(_Button->_PopupInfo, _Button->_DownLoadData, LauncherPath);
	C_WidgetSwitcher->SetActiveWidgetIndex(1);

	if(C_DownLoadWidget->DownLoadLevelName.IsEmpty())
		C_DownLoadWidget->DownLoadLevelName = _Button->_PopupInfo.Name_Horizon;
}

void UChangDeokMainWIdget::SetWidgetActor(AChangDeokMainWidgetActor* _WidgetActor)
{
	WidgetActor = _WidgetActor;
	WidgetActor->GetFHttpDownloadCheck()->AddUFunction(this, FName("CheckDownLoadState"));
	WidgetActor->GetFHttpDownloadEnd()->AddUFunction(this, FName("EndDownLoadState"));
	WidgetActor->GetFUnZipEndState()->AddUFunction(this, FName("UnZipEndState"));
}

void UChangDeokMainWIdget::SetChangeText(FString text)
{
	C_TextWidget->SetChangeText(text);
}

void UChangDeokMainWIdget::OnPressed_Binding_DescriptButton()
{
	C_DescriptButtonWidget->OnClickDescriptButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	C_WidgetSwitcher->SetActiveWidgetIndex(2);
	WidgetActor->OnPressed_CallNextStep(C_DescriptButtonWidget->MyStepManagerNumber);
}

void UChangDeokMainWIdget::OnPressed_Binding_TextHideButton()
{
	C_DescriptButtonWidget->OnClickTextHideButton();
	C_TextWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UChangDeokMainWIdget::OnPressed_Binding_TextShowButton()
{
	C_DescriptButtonWidget->OnClickTextShowButton();
	C_TextWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UChangDeokMainWIdget::OnPressed_ChangeLevel()
{
	if (IsDownLoadProcessing)
	{
		//설치 중인 것에 대한 안내 문구
		C_PopupWidget->SetMainSwitcherIndex(1);
	}
	else
	{
		CustomOpenLevelFadeIn();
	}
}

//void UChangDeokMainWIdget::CustomOpenLevelFadeIn_Implementation()
//{
//	FString tempText;
//	tempText = C_PopupWidget->DownLoadData.FileName.Replace(TEXT(".zip"), TEXT(" "));
//	tempText.RemoveSpacesInline();
//
//	LauncherPath = C_PopupWidget->DownLoadData.Path + tempText + "/Windows/Hanyang2_ChangDeok.exe";
//}

void UChangDeokMainWIdget::OpenLevelFadeIn()
{
	C_FadeWidget->CustomFadeIn();
}

void UChangDeokMainWIdget::OnPressed_PlayChangeButton()
{
	WidgetActor->SetSoundPlay(C_TextWidget->IsPaused);
}

void UChangDeokMainWIdget::OnPressed_TimeChangeButton()
{
	WidgetActor->SetCustomTimeOfDay(C_TextWidget->C_TimeOfDay);
}

void UChangDeokMainWIdget::OnPressed_DownLoadButton()
{
	Init();
	C_DownLoadWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	C_DownLoadWidget->SetText_CompleteDownLoad();
	IsDownLoadProcessing = true;
	WidgetActor->Call_SetHttpData(C_PopupWidget->DownLoadData.Path, C_PopupWidget->DownLoadData.FileName);
}

void UChangDeokMainWIdget::OnPressed_DownLoadCheckButton()
{
	IsDownLoadProcessing = false;
	C_PopupWidget->SetPanelEnable(!IsDownLoadProcessing);
	C_DownLoadWidget->SetDefault();
}

void UChangDeokMainWIdget::OnPressed_CancelDownLoadButton()
{
	WidgetActor->Call_CancelDownLoad();
	C_DownLoadWidget->SetText_CancelDownLoad();
	CustomOpenLevelFadeIn();
}

void UChangDeokMainWIdget::CheckDownLoadState(float _Percent)
{
	C_DownLoadWidget->SetPercent(_Percent);
}

void UChangDeokMainWIdget::EndDownLoadState(bool IsDownLoadCancel)
{
	if(!IsDownLoadCancel)
		C_PopupWidget->SetMovePlaceButtonPanelEnable(false);
	C_DownLoadWidget->DownLoadEnd(IsDownLoadCancel);
}

void UChangDeokMainWIdget::UnZipEndState()
{
	C_PopupWidget->SetMovePlaceButtonPanelEnable(true);
	C_DownLoadWidget->UnZipEnd();
}
