// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/StudentRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UStudentRowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Edit)
	{
		Btn_Edit->OnClicked.AddDynamic(this, &UStudentRowWidget::OnEditButtonClicked);	
	}

	if (Btn_Info)
	{
		Btn_Info->OnClicked.AddDynamic(this, &UStudentRowWidget::HandleInfoClicked);
	}
}



void UStudentRowWidget::SetRowData(const FStudentRowData& InData)
{
	CachedData = InData;

	
	if (Txt_Name)      Txt_Name->SetText(FText::FromString(InData.Name));
	if (Txt_ID)      Txt_ID->SetText(FText::FromString(InData.ID));
	if (Txt_Birth)    Txt_Birth->SetText(FText::FromString(InData.Birth));
	if (Txt_CrimeType) Txt_CrimeType->SetText(FText::FromString(InData.CrimeType));
	if (Txt_EduCourse) Txt_EduCourse->SetText(FText::FromString(InData.EduCourse));
	if (Txt_EduPeriod) Txt_EduPeriod->SetText(FText::FromString(InData.EduPeriod));
	if (Txt_VrType)    Txt_VrType->SetText(FText::FromString(InData.VrType));
	if (Txt_VrSession)    Txt_VrSession->SetText(FText::FromString(InData.VrSession));
	if (Txt_Start)      Txt_Start->SetText(FText::FromString(InData.Start));
	if (Txt_End)      Txt_End->SetText(FText::FromString(InData.End));
	if (Txt_Fin)  Txt_Fin->SetText(FText::FromString(InData.Fin));
	//--------------------------------------------------------------------//
	if (Txt_Manager) Txt_Manager->SetText(FText::FromString(InData.Manager));
	if (Txt_RegisterDate) Txt_RegisterDate->SetText(FText::FromString(InData.RegisterDate));
	if (Txt_UpdateDate) Txt_UpdateDate->SetText(FText::FromString(InData.UpdateDate));
	
	if (Txt_Pre1) Txt_Pre1->SetText(FText::AsNumber(InData.Pre1));
	if (Txt_Pre2) Txt_Pre2->SetText(FText::AsNumber(InData.Pre2));
	if (Txt_Pre3) Txt_Pre3->SetText(FText::AsNumber(InData.Pre3));
	if (Txt_Pre4) Txt_Pre4->SetText(FText::AsNumber(InData.Pre4));
	if (Txt_Pre5) Txt_Pre5->SetText(FText::AsNumber(InData.Pre5));
	if (Txt_Pre6) Txt_Pre6->SetText(FText::AsNumber(InData.Pre6));
	if (Txt_Pre7) Txt_Pre7->SetText(FText::AsNumber(InData.Pre7));
	if (Txt_Pre8) Txt_Pre8->SetText(FText::AsNumber(InData.Pre8));

	if (Txt_Post1) Txt_Post1->SetText(FText::AsNumber(InData.Post1));
	if (Txt_Post2) Txt_Post2->SetText(FText::AsNumber(InData.Post2));
	if (Txt_Post3) Txt_Post3->SetText(FText::AsNumber(InData.Post3));
	if (Txt_Post4) Txt_Post4->SetText(FText::AsNumber(InData.Post4));
	if (Txt_Post5) Txt_Post5->SetText(FText::AsNumber(InData.Post5));
	if (Txt_Post6) Txt_Post6->SetText(FText::AsNumber(InData.Post6));
	if (Txt_Post7) Txt_Post7->SetText(FText::AsNumber(InData.Post7));
	if (Txt_Post8) Txt_Post8->SetText(FText::AsNumber(InData.Post8));

	
	if (Txt_AVConcentration) Txt_AVConcentration->SetText(FText::FromString(InData.AVConcentration));
	if (Txt_Satisfaction)
	{
		if (InData.Satisfaction == 0)
		{
			Txt_Satisfaction->SetText(FText::FromString(TEXT("미진행")));
		}
		else
		{
			Txt_Satisfaction->SetText(FText::FromString(TEXT("진행")));
		}
	}
}

void UStudentRowWidget::HandleInfoClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("UStudentRowWidget::HandleInfoClicked - %s"), *CachedData.Name);
	OnRowInfoClicked.Broadcast(CachedData);
}

void UStudentRowWidget::OnEditButtonClicked()
{
	OnEditClicked.Broadcast(CachedData);
}