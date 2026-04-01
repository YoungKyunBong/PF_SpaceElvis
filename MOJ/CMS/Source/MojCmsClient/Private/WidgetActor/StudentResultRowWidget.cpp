#include "WidgetActor/StudentResultRowWidget.h"
#include "Components/TextBlock.h"

void UStudentResultRowWidget::SetRowData(const FStudentRowData& InData)
{
	if (Txt_Name)           Txt_Name->SetText(FText::FromString(InData.Name));
	if (Txt_ID)             Txt_ID->SetText(FText::FromString(InData.ID));
	if (Txt_Birth)          Txt_Birth->SetText(FText::FromString(InData.Birth));
	if (Txt_CrimeType)      Txt_CrimeType->SetText(FText::FromString(InData.CrimeType));
	if (Txt_EduCourse)      Txt_EduCourse->SetText(FText::FromString(InData.EduCourse));
	if (Txt_VRType)         Txt_VRType->SetText(FText::FromString(InData.VrType));
	if (Txt_AVConcentration)Txt_AVConcentration->SetText(FText::FromString(InData.AVConcentration));

	// 사전검사 (Pre1~3)
	if (Txt_Pre_Attack)        Txt_Pre_Attack->SetText(FText::AsNumber(InData.Pre1));
	if (Txt_Pre_Violence)      Txt_Pre_Violence->SetText(FText::AsNumber(InData.Pre2));
	if (Txt_Pre_Relationship)  Txt_Pre_Relationship->SetText(FText::AsNumber(InData.Pre3));

	// 사후검사 (Post1~3)
	if (Txt_Post_Attack)       Txt_Post_Attack->SetText(FText::AsNumber(InData.Post1));
	if (Txt_Post_Violence)     Txt_Post_Violence->SetText(FText::AsNumber(InData.Post2));
	if (Txt_Post_Relationship) Txt_Post_Relationship->SetText(FText::AsNumber(InData.Post3));

	// 만족도
	if (Txt_Satisfaction)
	{
		// 숫자만 보여주고 싶으면 AsNumber만 써도 됨
		FString SatStr = FString::Printf(TEXT("%d점"), InData.Satisfaction);
		Txt_Satisfaction->SetText(FText::FromString(SatStr));
	}

	// 진행상태는 일단 더미로 "진행"으로 표시 (원하면 GameManager 데이터에 필드 추가)
	if (Txt_Status)
	{
		Txt_Status->SetText(FText::FromString(TEXT("진행")));
	}
}
