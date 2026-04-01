#include "WidgetActor/StudentManageWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Manager/GameManager.h"

void UStudentManageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	//{
	//	GM->CreateDummyStudentData();
	//}

	if (Combo_FilterType)
	{
		Combo_FilterType->SetSelectedOption(TEXT("이름"));
	}
}
