#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.h"      // FStudentRowData 사용
#include "StudentEditWidget.generated.h"

class UEditableTextBox;
class UComboBoxString;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStudentSubmit, const FStudentRowData&, Data, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStudentDeleted, const FString&, DeletedID);

UENUM(BlueprintType)
enum class EStudentEditMode : uint8
{
    New,
    Edit
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEditModeChanged, EStudentEditMode, Mode, FText, HeaderText);

UCLASS()
class MOJCMSCLIENT_API UStudentEditWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    /** 신규 등록 모드로 전환 (입력 초기화 + 등록버튼만 표시) */
    UFUNCTION(BlueprintCallable)
    void SetNewMode();

    /** 수정 모드로 전환 (기존 데이터 채워넣기 + 수정버튼만 표시) */
    UFUNCTION(BlueprintCallable)
    void SetEditMode(const FStudentRowData& InData);

    UFUNCTION(BlueprintCallable)
    void SetTextBoxCommitted(UEditableTextBox* TempEditTextBox);

    UFUNCTION(BlueprintCallable)
    void SetComboBoxCommitted(UComboBoxString* TempComboBox);


    UPROPERTY(BlueprintAssignable, Category="StudentEdit")
    FOnEditModeChanged OnEditModeChanged;
    
    /** 바깥에서 등록/수정 결과 받는 델리게이트 */
    UPROPERTY(BlueprintAssignable, Category="StudentEdit")
    FOnStudentSubmit OnSubmitNew;   // 등록하기
    UPROPERTY(BlueprintAssignable, Category="StudentEdit")
    FOnStudentSubmit OnSubmitEdit;  // 수정완료

protected:
    /** 입력 필드들 (UMG에서 BindWidget로 연결) */
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UEditableTextBox* Edt_Name;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UEditableTextBox* Edt_ID;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UEditableTextBox* Edt_Birth;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UComboBoxString* Cmb_Fin;  
    
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UComboBoxString* Cmb_CrimeType;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UComboBoxString* Cmb_EduCourse;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UEditableTextBox* Edt_EduPeriod;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UComboBoxString* Cmb_VrType;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UEditableTextBox* Edt_Manager;

    // 버튼 2개
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton* Btn_Register;         // "등록하기"

    UPROPERTY(meta=(BindWidget))
    UButton* Btn_Update;           // "수정완료"

    UPROPERTY(meta=(BindWidget))
    UButton* Btn_Delete;           // 수용자 삭제  
    
protected:
    UFUNCTION()
    void OnRegisterClicked();

    UFUNCTION()
    void OnUpdateClicked();

    UFUNCTION()
    void OnDeleteClicked();

    
    /** 현재 모드 */
    EStudentEditMode CurrentMode = EStudentEditMode::New;

    /** 수정 모드일 때, 어떤 학생을 수정 중인지 (ID 등 키로 활용 가능) */
    FStudentRowData EditingData;

    /** UI → FStudentRowData 로 변환 */
    FStudentRowData CollectDataFromUI() const;

    /** 내부에서 버튼 가시성 토글 */
    void RefreshButtonVisibility();


    void ApplyEditPermissions();

private:
    FText MakeHeaderText() const;

};
