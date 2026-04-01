#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"          // FSessionNoteRow 사용
#include "SessionNoteRowWidget.generated.h"

class UTextBlock;
class UEditableTextBox;
class UMultiLineEditableTextBox;

UCLASS()
class MOJCMSCLIENT_API USessionNoteRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetRowData(const FSessionNoteRow& InData);

	UFUNCTION(BlueprintCallable)
	FSessionNoteRow GetRowData() const;

protected:
	// 회기 (1,2,3,4,5)
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_SessionIndex;

	// 집중도 (50%, 55.4% ...)
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Score;

	// 회기별 특이사항 (멀티라인)
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Note;
};
