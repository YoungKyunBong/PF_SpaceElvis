#include "WidgetActor/StudentDetailWidget.h"
#include "Components/TextBlock.h"
#include "WidgetActor/StudentSessionMonitorWidget.h"

void UStudentDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("UStudentDetailWidget::NativeConstruct"));
}

void UStudentDetailWidget::SetDetailData(const FStudentRowData& InData)
{
	OnCrimeChanged.Broadcast(InData.CrimeType);
	if (TxtD_Name)         TxtD_Name->SetText(FText::FromString(InData.Name));
	if (TxtD_ID)           TxtD_ID->SetText(FText::FromString(InData.ID));
	if (TxtD_Birth)        TxtD_Birth->SetText(FText::FromString(InData.Birth));
	if (TxtD_CrimeType)    TxtD_CrimeType->SetText(FText::FromString(InData.CrimeType));
	if (TxtD_EduCourse)    TxtD_EduCourse->SetText(FText::FromString(InData.EduCourse));
	if (TxtD_VrType_1)       TxtD_VrType_1->SetText(FText::FromString(InData.VrType));
	if (TxtD_Name_1)         TxtD_Name_1->SetText(FText::FromString(InData.Name));
	if (TxtD_ID_1)           TxtD_ID_1->SetText(FText::FromString(InData.ID));
	if (TxtD_Birth_1)        TxtD_Birth_1->SetText(FText::FromString(InData.Birth));
	if (TxtD_CrimeType_1)    TxtD_CrimeType_1->SetText(FText::FromString(InData.CrimeType));
	if (TxtD_EduCourse_1)    TxtD_EduCourse_1->SetText(FText::FromString(InData.EduCourse));
	if (TxtD_VrType_1)       TxtD_VrType_1->SetText(FText::FromString(InData.VrType));
	if (TxtD_Pre1) TxtD_Pre1->SetText(FText::AsNumber(InData.Pre1));
	if (TxtD_Pre2) TxtD_Pre2->SetText(FText::AsNumber(InData.Pre2));
	if (TxtD_Pre3) TxtD_Pre3->SetText(FText::AsNumber(InData.Pre3));
	if (TxtD_Pre4) TxtD_Pre4->SetText(FText::AsNumber(InData.Pre4));
	if (TxtD_Pre1_1) TxtD_Pre1_1->SetText(FText::AsNumber(InData.Pre1));
	if (TxtD_Pre2_1) TxtD_Pre2_1->SetText(FText::AsNumber(InData.Pre2));
	if (TxtD_Pre3_1) TxtD_Pre3_1->SetText(FText::AsNumber(InData.Pre3));
	if (TxtD_Pre4_1) TxtD_Pre4_1->SetText(FText::AsNumber(InData.Pre4));

	if (TxtD_Pre5) TxtD_Pre5->SetText(FText::AsNumber(InData.Pre5));
	if (TxtD_Pre6) TxtD_Pre6->SetText(FText::AsNumber(InData.Pre6));
	if (TxtD_Pre7) TxtD_Pre7->SetText(FText::AsNumber(InData.Pre7));
	if (TxtD_Pre8) TxtD_Pre8->SetText(FText::AsNumber(InData.Pre8));


	if (TxtD_Post1) TxtD_Post1->SetText(FText::AsNumber(InData.Post1));
	if (TxtD_Post2) TxtD_Post2->SetText(FText::AsNumber(InData.Post2));
	if (TxtD_Post3) TxtD_Post3->SetText(FText::AsNumber(InData.Post3));
	if (TxtD_Post4) TxtD_Post4->SetText(FText::AsNumber(InData.Post4));
	if (TxtD_Post1_1) TxtD_Post1_1->SetText(FText::AsNumber(InData.Post1));
	if (TxtD_Post2_1) TxtD_Post2_1->SetText(FText::AsNumber(InData.Post2));
	if (TxtD_Post3_1) TxtD_Post3_1->SetText(FText::AsNumber(InData.Post3));
	if (TxtD_Post4_1) TxtD_Post4_1->SetText(FText::AsNumber(InData.Post4));

	if (TxtD_Post5) TxtD_Post5->SetText(FText::AsNumber(InData.Post5));
	if (TxtD_Post6) TxtD_Post6->SetText(FText::AsNumber(InData.Post6));
	if (TxtD_Post7) TxtD_Post7->SetText(FText::AsNumber(InData.Post7));
	if (TxtD_Post8) TxtD_Post8->SetText(FText::AsNumber(InData.Post8));
	
	if (TxtD_Concentration) TxtD_Concentration->SetText(FText::FromString(InData.AVConcentration));
	if (TxtD_Concentration_1) TxtD_Concentration_1->SetText(FText::FromString(InData.AVConcentration));
	if (TxtD_Satisfaction)
	{
		if (InData.Satisfaction == 0)
		{
			TxtD_Satisfaction->SetText(FText::FromString(TEXT("미완료")));
		}
		else
		{
			TxtD_Satisfaction->SetText(FText::FromString(TEXT("완료")));
		}
	}
	if (TxtD_Satisfaction_1)
	{
		if (InData.Satisfaction == 0)
		{
			TxtD_Satisfaction_1->SetText(FText::FromString(TEXT("미완료")));
		}
		else
		{
			TxtD_Satisfaction_1->SetText(FText::FromString(TEXT("완료")));
		}
	}



	//1-5 테이블 세팅
	auto ApplyRow = [&](int32 Index, UTextBlock* Score, UTextBlock* Note)
	{
		if (!Score || !Note)
			return;

		if (InData.SessionNotes.IsValidIndex(Index))
		{
			const FSessionNoteRow& Row = InData.SessionNotes[Index];
			Score->SetText(FText::FromString(Row.Score));
			Note->SetText(FText::FromString(Row.Note));
		}
		else
		{
			// 데이터 없으면 기본값
			Score->SetText(FText::FromString(TEXT("-")));
			Note->SetText(FText::FromString(TEXT("")));
		}
	};

	ApplyRow(0, Txt_Session1Score, Txt_Session1Note);
	ApplyRow(1, Txt_Session2Score, Txt_Session2Note);
	ApplyRow(2, Txt_Session3Score, Txt_Session3Note);
	ApplyRow(3, Txt_Session4Score, Txt_Session4Note);
	ApplyRow(4, Txt_Session5Score, Txt_Session5Note);

	SetDetailImage(InData.CrimeType);
}

