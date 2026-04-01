#include "WidgetActor/SessionNoteRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"

void USessionNoteRowWidget::SetRowData(const FSessionNoteRow& InData)
{
	if (Txt_SessionIndex)
	{
		Txt_SessionIndex->SetText(
			FText::AsNumber(InData.SessionIndex)
		);
	}

	if (Txt_Score)
	{
		Txt_Score->SetText(FText::FromString(InData.Score));
	}

	if (Txt_Note)
	{
		Txt_Note->SetText(FText::FromString(InData.Note));
	}
}

FSessionNoteRow USessionNoteRowWidget::GetRowData() const
{
	FSessionNoteRow Out;

	if (Txt_SessionIndex)
	{
		Out.SessionIndex =
			FCString::Atoi(*Txt_SessionIndex->GetText().ToString());
	}

	if (Txt_Score)
	{
		Out.Score = Txt_Score->GetText().ToString();
	}

	if (Txt_Note)
	{
		Out.Note = Txt_Note->GetText().ToString();
	}

	return Out;
}
