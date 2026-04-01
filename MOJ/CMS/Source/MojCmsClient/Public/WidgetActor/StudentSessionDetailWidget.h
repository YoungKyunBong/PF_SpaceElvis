#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "WidgetActor/StudentRowWidget.h"   // FStudentRowData / FSessionNoteRow
#include "StudentSessionDetailWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UButton;
class UMultiLineEditableTextBox;
class UGameManager;

/**
 * 회기별 반응 페이지
 * - 상단: 검색 ID 입력
 * - 중간: 기본 정보 카드
 * - 하단: 회기별 기록 (탭 1~5 + 멀티라인 메모)
 */
UCLASS()
class MOJCMSCLIENT_API UStudentSessionDetailWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	/** 외부에서 ID로 바로 로드하고 싶을 때 사용 가능 */
	UFUNCTION(BlueprintCallable)
	bool LoadStudentById(const FString& InId);

protected:
	// ---------- 검색 영역 ----------
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* Edt_SearchId;      // 상단 검색 텍스트박스

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Search;                // 돋보기 버튼 등

	// ---------- 기본 정보 카드 ----------
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TitleNameAndId;     // "홍길동 (202301)" 같은 타이틀

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Birth;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CrimeType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_EduCourse;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_VRType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_VRSession;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_EduPeriod;

	// ---------- 회기 탭 ----------
	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Session1;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Session2;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Session3;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Session4;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Session5;

	TArray<UButton*> SessionButtons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Session Tabs")
	FLinearColor SessionNormalColor = FLinearColor(0.796f, 0.835f, 0.890f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Session Tabs")
	FLinearColor SessionSelectedColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.f);
	
	// ---------- 회기별 기록 ----------
	UPROPERTY(meta=(BindWidget))
	UMultiLineEditableTextBox* Edt_SessionNote;   // 회기별 특이사항



	// 담당자
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* Edt_Manager;

	// 수정 / 저장 버튼
	UPROPERTY(meta=(BindWidget))
	UButton* Btn_EditOrSave;        // "수정하기" ↔ "저장하기" 토글

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* SearchSwitcher;
	
protected:
	// 내부 상태
	UPROPERTY()
	UGameManager* GM;

	// 현재 선택된 학생
	FStudentRowData CurrentStudent;

	bool bHasStudent = false;
	bool bEditing    = false;
	int32 CurrentSessionIndex = 1;   // 1~5

protected:
	// ---------- UI 이벤트 ----------
	UFUNCTION()
	void OnSearchButtonClicked();

	UFUNCTION()
	void OnSearchIdCommitted(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnSession1Clicked();
	UFUNCTION()
	void OnSession2Clicked();
	UFUNCTION()
	void OnSession3Clicked();
	UFUNCTION()
	void OnSession4Clicked();
	UFUNCTION()
	void OnSession5Clicked();

	UFUNCTION()
	void OnEditOrSaveClicked();

	// ---------- 내부 헬퍼 ----------
	void RefreshHeaderUI();          // 상단 카드
	void RefreshSessionUI();         // 하단 회기 기록 영역
	void SetSessionIndex(int32 NewIndex);
	void ApplyEditingMode();         // 읽기전용 / 편집가능 토글

	void UpdateSessionButtonVisual();
};
