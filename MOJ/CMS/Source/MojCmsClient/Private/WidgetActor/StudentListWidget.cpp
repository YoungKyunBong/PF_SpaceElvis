#include "WidgetActor/StudentListWidget.h"
#include "Components/ScrollBox.h"
#include "Manager/GameManager.h"

void UStudentListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("UStudentListWidget::NativeConstruct"));

	if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	{
		// 델리게이트 구독
		GM->OnStudentRowsUpdated.AddUObject(this, &UStudentListWidget::OnStudentRowsUpdated);

		// 이미 데이터가 있다면 바로 한 번 빌드
		OriginalRows = GM->GetStudentRows();
		UE_LOG(LogTemp, Warning, TEXT("StudentListWidget NativeConstruct - Initial Rows: %d"), OriginalRows.Num());
		BuildList(OriginalRows);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StudentListWidget: GameManager not found!"));
	}

	SearchHintText = TEXT("성명 키워드로 교육생 검색");
}

void UStudentListWidget::OnStudentRowsUpdated()
{
	if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	{
		OriginalRows = GM->GetStudentRows();
		UE_LOG(LogTemp, Warning, TEXT("OnStudentRowsUpdated - Rows: %d"), OriginalRows.Num());
		ApplyFilters();
	}
}

void UStudentListWidget::BuildList(const TArray<FStudentRowData>& Rows)
{
	UE_LOG(LogTemp, Warning, TEXT("BuildList CALLED with %d items"), Rows.Num());

	if (!SB_List)
	{
		UE_LOG(LogTemp, Error, TEXT("BuildList: SB_List is NULL"));
		return;
	}
	if (!RowWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("BuildList: RowWidgetClass is NULL"));
		return;
	}

	SB_List->ClearChildren();

	for (const FStudentRowData& RowData : Rows)
	{
		UStudentRowWidget* RowWidget =
			CreateWidget<UStudentRowWidget>(this, RowWidgetClass);

		if (RowWidget)
		{
			RowWidget->SetRowData(RowData);

			RowWidget->OnEditClicked.AddDynamic(this, &UStudentListWidget::OnRowEditRequested);

			
			SB_List->AddChild(RowWidget);

			//info 연결
			RowWidget->OnRowInfoClicked.AddDynamic(
					   this, &UStudentListWidget::HandleRowInfoClicked);
		}
	}
}

void UStudentListWidget::OnFilterTypeChanged(const FString& SelectedType)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFilterTypeChanged: %s"), *SelectedType);

	if (SelectedType == TEXT("성명"))
	{
		CurrentFilterType = EFilterType::Name;
		SearchHintText = TEXT("성명 키워드로 교육생 검색");
	}
	else if (SelectedType == TEXT("범죄유형"))
	{
		CurrentFilterType = EFilterType::CrimeType;
		SearchHintText = TEXT("범죄유형 키워드로 교육생 검색");
	}
	else if (SelectedType == TEXT("교육시기"))
	{
		CurrentFilterType = EFilterType::EduPeriod;
		SearchHintText = TEXT("교육시기 키워드로 교육생 검색");
	}
	else if (SelectedType == TEXT("수료여부"))
	{
		CurrentFilterType = EFilterType::Fin;
		SearchHintText = TEXT("수료여부 키워드로 교육생 검색");
	}

	ApplyFilters();
}

void UStudentListWidget::OnSearchTextChanged(const FString& Text)
{
	CurrentSearchKeyword = Text;
	ApplyFilters();
}

void UStudentListWidget::ApplyFilters()
{
	UE_LOG(LogTemp, Warning, TEXT("ApplyFilters: Mode=%d, Keyword=%s"),
		(int32)CurrentFilterType, *CurrentSearchKeyword);

	FString Key = CurrentSearchKeyword;
	Key.TrimStartAndEndInline();
	Key.ToLowerInline();

	if (Key.IsEmpty())
	{
		BuildList(OriginalRows);
		return;
	}

	TArray<FStudentRowData> Filtered;

	for (const auto& Row : OriginalRows)
	{
		FString Compare;

		switch (CurrentFilterType)
		{
		case EFilterType::Name:
			Compare = Row.Name;
			break;
		case EFilterType::CrimeType:
			Compare = Row.CrimeType;
			break;
		case EFilterType::EduPeriod:
			Compare = Row.EduPeriod;
			break;
		case EFilterType::Fin:
			Compare = Row.Fin;
			break;
		default:
			Compare = Row.Name;
			break;
		}

		Compare.ToLowerInline();

		if (Compare.Contains(Key))
			Filtered.Add(Row);
	}

	BuildList(Filtered);
}

void UStudentListWidget::OnRowEditRequested(const FStudentRowData& Data)
{
	OnRequestEdit.Broadcast(Data);  // 부모(ManageWidget)에게 전달
}

void UStudentListWidget::ModifyRow(const FStudentRowData& Data, int updateIndex)
{
	OriginalRows[updateIndex] = Data;

	//// ID 로 기존 학생 찾기
	//for (auto& Row : OriginalRows)
	//{
	//	if (Row.ID == Data.ID)
	//	{
	//		Row = Data; // 수정된 데이터로 덮어쓰기
	//		break;
	//	}
	//}

	BuildList(OriginalRows);
}

void UStudentListWidget::HandleRowInfoClicked(const FStudentRowData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("StudentListWidget::HandleRowInfoClicked %s"), *Data.Name);

	// 바깥으로 한 번 더 쏴줌 (InWidget, StudentDetail 등이 받을 수 있게)
	OnStudentSelected.Broadcast(Data);
}
