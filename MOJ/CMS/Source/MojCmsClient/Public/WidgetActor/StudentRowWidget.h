#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StudentRowWidget.generated.h"

class UTextBlock;
class UButton;


USTRUCT(BlueprintType)
struct FHeartRateLog
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Bpm = 0;

    UPROPERTY(BlueprintReadWrite)
    int64 TimestampMs = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 ServerMark  = 0; //인트값
};

USTRUCT(BlueprintType)
struct FSessionHeartRateLogs
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SessionIndex = 0; // 1~5
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FHeartRateLog> Logs;
};



USTRUCT(BlueprintType)
struct FSessionNoteRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SessionIndex = 0;   // 1~5 회기 번호

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Score;            // "50%", "55.4%" 같은 집중도

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Note;             // 회기별 특이사항 (멀티라인 텍스트)
};


// 한 행에 들어갈 데이터 구조
USTRUCT(BlueprintType)
struct FStudentRowData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;          // 성명
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ID;        // 수용번호

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Birth;      // 생년월일
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CrimeType;     // 범죄유형

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EduCourse;     // 교육과정

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EduPeriod;     // 교육시기

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString VrType;        // VR유형

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString VrSession;    //VR 회기

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Start;          // 시작일

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString End;          // 종료일

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Fin;      // 수료여부
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Manager;        // 담당자

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RegisterDate;   // 등록일

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UpdateDate;   //수정일

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AVConcentration;  //평균집중도

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Satisfaction;  //만족도

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Consent_Test; //동의서
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Pre_Test; //사전검사

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Post_Test; //사후검사 19

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAllSessionsCompleted = false;//5회기 끝났는지
    
    //사전검사 점수
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre4;
    //마약용 점수
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre6;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre7;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pre8;

    //사후검사 점수
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post4; //마약 빼면 27
    //마약용 점수
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post6;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post7;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Post8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSessionNoteRow> SessionNotes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSessionHeartRateLogs> SessionHeartRateSchedules;

    bool operator==(const FStudentRowData& rhs) const
    {
        if ((ID == rhs.ID) && (CrimeType == rhs.CrimeType) && (EduCourse == rhs.EduCourse) && (VrType == rhs.VrType) && (Start == rhs.Start) && (End == rhs.End) && (RegisterDate == rhs.RegisterDate) 
            && (AVConcentration == rhs.AVConcentration) && (Satisfaction == rhs.Satisfaction) && (Consent_Test == rhs.Consent_Test) && (Pre_Test == rhs.Pre_Test) && (Post_Test == rhs.Post_Test) && (EduPeriod == rhs.EduPeriod))
            return true;

        return false;
    }
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRowInfoClicked, const FStudentRowData&, Data);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEditClicked, const FStudentRowData&, Data);


UCLASS()
class MOJCMSCLIENT_API UStudentRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    UFUNCTION(BlueprintCallable)
    void SetRowData(const FStudentRowData& InData);

    UPROPERTY(BlueprintAssignable)
    FOnEditClicked OnEditClicked;

    UPROPERTY(BlueprintAssignable, Category="StudentRow")
    FOnRowInfoClicked OnRowInfoClicked;
    
protected:
    // UMG에서 BindWidget로 연결
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Name;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_ID;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Birth;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_CrimeType;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_EduCourse;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_EduPeriod;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_VrType;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_VrSession;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Start;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_End;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Fin;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Manager;        // 담당자

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_RegisterDate;   // 등록일

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_UpdateDate;   //수정일
    
    UPROPERTY(meta=(BindWidget))
    UButton* Btn_Info;

    UPROPERTY(meta=(BindWidget))
    UButton* Btn_Edit;


    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_AVConcentration;  //집중도

    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Satisfaction;  //만족도
    
    //사전검사 점수
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Pre1;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Pre2;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Pre3;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Pre4;

    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Pre5;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Pre6;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Pre7;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Pre8;

    //사후검사 점수
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Post1;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Post2;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Post3;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* Txt_Post4;

    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Post5;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Post6;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Post7;
    UPROPERTY(meta=(BindWidgetOptional))
    UTextBlock* Txt_Post8;


    // 회기별 집중도 / 특이사항 (1~5행)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSessionNoteRow> SessionNotes;
    
    
    UFUNCTION()
    void HandleInfoClicked();

    UFUNCTION()
    void OnEditButtonClicked();

    // Info 버튼에서 사용할 데이터 저장
    FStudentRowData CachedData;

};
