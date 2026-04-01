#include "WidgetActor/StudentResultListWidget.h"

#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Manager/GameManager.h"

void UStudentResultListWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("UStudentResultListWidget::NativeConstruct"));

    if (UWorld* World = GetWorld())
    {
        GM = World->GetGameInstance<UGameManager>();
    }

    if (!GM)
    {
        UE_LOG(LogTemp, Error, TEXT("StudentResultListWidget: GameManager not found!"));
        return;
    }

    if (Btn_Export)
    {
        Btn_Export->OnClicked.AddDynamic(this, &UStudentResultListWidget::OnExportExcelClicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget: Btn_Export is NULL (BindWidget 확인 필요)"));
    }

    if (Btn_Drug)
    {
        Btn_Drug->OnClicked.AddDynamic(this, &UStudentResultListWidget::OnDrugClicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget: Btn_Drug is NULL (BindWidget 확인 필요)"));
    }

    if (Btn_Else)
    {
        Btn_Else->OnClicked.AddDynamic(this, &UStudentResultListWidget::OnElseClicked);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget: Btn_Else is NULL (BindWidget 확인 필요)"));
    }


    // 1) GameManager 델리게이트 구독
    GM->OnStudentRowsUpdated.AddUObject(
        this, &UStudentResultListWidget::OnStudentRowsUpdated);

    // 2) 현재 StudentRows로 리스트 한 번 그리기
    RebuildListFromGameManager();
}

void UStudentResultListWidget::OnStudentRowsUpdated()
{
    UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget::OnStudentRowsUpdated"));
    RebuildListFromGameManager();
}

void UStudentResultListWidget::RebuildListFromGameManager()
{
    if (!GM)
    {
        UE_LOG(LogTemp, Error, TEXT("RebuildListFromGameManager: GM is NULL"));
        return;
    }
    if (!SB_ResultList)
    {
        UE_LOG(LogTemp, Error, TEXT("RebuildListFromGameManager: SB_ResultList is NULL"));
        return;
    }
    if (!RowWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("RebuildListFromGameManager: RowWidgetClass is NULL (BP에서 지정 필요)"));
        return;
    }

    const TArray<FStudentRowData>& Rows = GM->GetStudentRows();
    UE_LOG(LogTemp, Warning, TEXT("RebuildListFromGameManager: Rows = %d"), Rows.Num());

    SB_ResultList->ClearChildren();

    for (const FStudentRowData& RowData : Rows)
    {
        const bool bIsDrug = IsDrugCrime(RowData.CrimeType);

        switch (CurrentFilterMode)
        {
        case ECrimeFilterMode::Drug:
            if (!bIsDrug)
            {
                continue;
            }
            break;

        case ECrimeFilterMode::Else:
            if (bIsDrug)
            {
                continue;
            }
            break;

        case ECrimeFilterMode::All:
        default:
            break;
        }

        UStudentRowWidget* RowWidget = nullptr;

        if (bIsDrug && DrugRowWidgetClass)
        {
            RowWidget = CreateWidget<UStudentRowWidget>(this, DrugRowWidgetClass);
        }
        else
        {
            RowWidget = CreateWidget<UStudentRowWidget>(this, RowWidgetClass);
        }

        if (!RowWidget) 
            continue;

        RowWidget->SetRowData(RowData);
        SB_ResultList->AddChild(RowWidget);
    }
}



static FString EscapeCSV(const FString& In)
{
	FString S = In;
	S.ReplaceInline(TEXT("\""), TEXT("\"\"")); // " -> ""

	if (S.Contains(TEXT(",")) || S.Contains(TEXT("\"")) ||
		S.Contains(TEXT("\n")) || S.Contains(TEXT("\r")))
	{
		return FString::Printf(TEXT("\"%s\""), *S);
	}
	return S;
}

void UStudentResultListWidget::OnExportExcelClicked()
{
    if (!GM)
    {
        GM = GetWorld()->GetGameInstance<UGameManager>();
    }
    if (!GM)
    {
        UE_LOG(LogTemp, Error, TEXT("OnExportExcelClicked: GameManager is NULL"));
        return;
    }

    const TArray<FStudentRowData>& Rows = GM->GetStudentRows();
    if (Rows.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnExportExcelClicked: No rows to export"));
        return;
    }

    FString CSV;

    // 🔹 헤더 (엑셀에서 컬럼명으로 보임)
    CSV += TEXT("이름,수용번호,생년월일,범죄유형,교육과정,교육시기,VR유형,시작일,종료일,수료여부,담당자,등록일,수정일,평균집중도,만족도,사전1,사전2,사전3,사전4,사후1,사후2,사후3,사후4\r\n");

    // 🔹 데이터 행
    for (const FStudentRowData& R : Rows)
    {
        CSV += FString::Printf(
            TEXT("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\r\n"),
            *EscapeCSV(R.Name),
            *EscapeCSV(R.ID),
            *EscapeCSV(R.Birth),
            *EscapeCSV(R.CrimeType),
            *EscapeCSV(R.EduCourse),
            *EscapeCSV(R.EduPeriod),
            *EscapeCSV(R.VrType),
            *EscapeCSV(R.Start),
            *EscapeCSV(R.End),
            *EscapeCSV(R.Fin),
            *EscapeCSV(R.Manager),
            *EscapeCSV(R.RegisterDate),
            *EscapeCSV(R.UpdateDate),
            *EscapeCSV(R.AVConcentration),
            R.Satisfaction,
            R.Pre1, R.Pre2, R.Pre3, R.Pre4,
            R.Post1, R.Post2, R.Post3, R.Post4
        );
    }

    // 🔹 저장 경로: Saved/StudentResultExport.csv
    const FString SaveDir  = FPaths::ProjectSavedDir();
    const FString FileName = TEXT("StudentResultExport.csv");
    const FString FullPath = SaveDir / FileName;

    //UTF-8 + BOM 으로 저장 (엑셀이 바로 한글/열 인식)
    if (FFileHelper::SaveStringToFile(
            CSV,
            *FullPath,
            FFileHelper::EEncodingOptions::ForceUTF8))
    {
        UE_LOG(LogTemp, Warning, TEXT("Exported student results to CSV: %s"), *FullPath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save CSV export: %s"), *FullPath);
    }
}

void UStudentResultListWidget::OnElseClicked()
{
    CurrentFilterMode = ECrimeFilterMode::Else;
    UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget: Filter = Else"));

    RebuildListFromGameManager();
}

void UStudentResultListWidget::OnDrugClicked()
{
    CurrentFilterMode = ECrimeFilterMode::Drug;
    UE_LOG(LogTemp, Warning, TEXT("StudentResultListWidget: Filter = Drug"));

    RebuildListFromGameManager();
}

bool UStudentResultListWidget::IsDrugCrime(const FString& CrimeType) const
{
    if (CrimeType.Contains(TEXT("마약")))
    {
        return true;
    }

    return false;
}

