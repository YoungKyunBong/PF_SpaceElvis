#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"
#include "StudentListWidget.generated.h"

class UScrollBox;



// Row에서 클릭된 학생 정보를 위로 올리는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStudentSelected, const FStudentRowData&, Data);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestEdit, const FStudentRowData&, Data);


UENUM(BlueprintType)
enum class EFilterType : uint8
{
	Name,
	CrimeType,
	EduPeriod,
	Fin
};

UCLASS()
class MOJCMSCLIENT_API UStudentListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// 콤보박스 선택 시 호출
	UFUNCTION(BlueprintCallable)
	void OnFilterTypeChanged(const FString& Selected);

	// 검색창 텍스트 변경 시 호출
	UFUNCTION(BlueprintCallable)
	void OnSearchTextChanged(const FString& Text);

	UPROPERTY(BlueprintAssignable)
	FOnRequestEdit OnRequestEdit;

	
protected:
	UPROPERTY(meta=(BindWidget))
	UScrollBox* SB_List;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StudentList")
	TSubclassOf<UStudentRowWidget> RowWidgetClass;

	UPROPERTY()
	TArray<FStudentRowData> OriginalRows;

	EFilterType CurrentFilterType = EFilterType::Name;
	FString     CurrentSearchKeyword;

	UPROPERTY(BlueprintReadOnly)
	FString SearchHintText;

	// GameManager에서 호출되는 콜백
	UFUNCTION()
	void OnStudentRowsUpdated();

	UFUNCTION(BlueprintCallable)
	void ModifyRow(const FStudentRowData& Data, int updateIndex);
	
	UFUNCTION()
	void OnRowEditRequested(const FStudentRowData& Data);
	void BuildList(const TArray<FStudentRowData>& Rows);
	void ApplyFilters();


	
	UPROPERTY(BlueprintAssignable, Category="StudentList")
	FOnStudentSelected OnStudentSelected;

protected:
	UFUNCTION()
	void HandleRowInfoClicked(const FStudentRowData& Data);
};
