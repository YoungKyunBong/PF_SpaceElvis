#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentManageWidget.generated.h"

// 🔹 여기서 사용할 UCLASS/위젯들은 미리 forward declare 해줘야 함
class UStudentListWidget;
class UStudentEditWidget;
class UComboBoxString;
class UEditableTextBox;

UCLASS()
class MOJCMSCLIENT_API UStudentManageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	// 오른쪽 리스트 (WBP_StudentList)
	UPROPERTY(meta = (BindWidget))
	UStudentListWidget* StudentList;

	// 왼쪽 편집 패널 (WBP_StudentEdit)
	UPROPERTY(meta = (BindWidget))
	UStudentEditWidget* StudentEdit;

	// 필터 콤보
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Combo_FilterType;

	// 검색 텍스트
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Txt_Search;
};
