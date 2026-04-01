#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"          // FStudentRowData, UStudentRowWidget
#include "StudentResultListWidget.generated.h"

class UScrollBox;
class UGameManager;

/**
 *  교육 결과 관리 페이지 리스트 위젯
 *  - GameManager::StudentRows 를 그대로 표시
 *  - 필터나 검색 없이 전체를 그냥 보여주는 용도
 */

enum class ECrimeFilterMode : uint8
{
	All,
	Drug,
	Else
};

UCLASS()
class MOJCMSCLIENT_API UStudentResultListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/** GameManager의 데이터를 다시 읽어와서 리스트 재빌드 */
	UFUNCTION(BlueprintCallable)
	void RebuildListFromGameManager();

protected:
	/** 스크롤 박스 (BP에서 BindWidget) */
	UPROPERTY(meta = (BindWidget))
	UScrollBox* SB_ResultList;

	/** 한 행(Row)에 해당하는 위젯 클래스 (BP에서 지정) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ResultList")
	TSubclassOf<UStudentRowWidget> RowWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ResultList")
	TSubclassOf<UStudentRowWidget> DrugRowWidgetClass;

	/** 엑셀(CSV) 내보내기 버튼 (BP에서 BindWidget) */
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Export;

	//나머지
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Else;
	//마약
	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Drug;

	/** 버튼 클릭 핸들러 */
	UFUNCTION()
	void OnExportExcelClicked();

	UFUNCTION()
	void OnElseClicked();

	UFUNCTION()
	void OnDrugClicked();

	
	ECrimeFilterMode CurrentFilterMode = ECrimeFilterMode::Else;
	
	bool IsDrugCrime(const FString& CrimeType) const;
	
private:
	/** 캐싱용 GameManager 포인터 */
	UPROPERTY()
	UGameManager* GM = nullptr;

	/** GameManager 델리게이트 콜백 */
	void OnStudentRowsUpdated();
};
