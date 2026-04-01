// StudentSessionMonitorWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "WidgetActor/StudentRowWidget.h"   // FStudentRowData / FSessionNoteRow
#include "StudentSessionMonitorWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UButton;
class UMultiLineEditableTextBox;
class UScrollBox;
class UGameManager;
class AHrUDPManager;
class UHeartRateGraphWidget;
class UHeartRateRowWidget;
class UConsentWidget;

UENUM(BlueprintType)
enum class ESessionRunState : uint8
{
	Idle,        // 시작 전
	Running,     // 심박 수신 중
	Paused,      // 일시정지
	Finished     // 종료됨
};


/**
 * 교육생 조회 + 회기별 모니터링 페이지
 */

// UE 컨테이너 안정성 위해 "회기별 로그"는 한 겹 감싸서 저장
USTRUCT(BlueprintType)
struct FHeartRateLogArray
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FHeartRateLog> Logs;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRunContentRequested);

UCLASS()
class MOJCMSCLIENT_API UStudentSessionMonitorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	bool LoadStudentById(const FString& InId);

	UPROPERTY(BlueprintAssignable, Category = "Session")
	FOnRunContentRequested OnRunContentRequested;

	
protected:

	UPROPERTY(meta=(BindWidget))
	UImage* SearchImage;
	// ---------- 검색 ----------
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* Edt_SearchId;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Search;

	UPROPERTY(meta=(BindWidgetOptional))
	UWidgetSwitcher* SearchSwitcher;

	// ---------- 기본 정보 ----------
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TitleNameAndId;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CrimeType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_VRType;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CurrentSession;


	//-----------Detail------------
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_TitleNameAndId_D;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Birth_D;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CrimeType_D;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_EduCourse_D;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_EduPeriod_D;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_VRType_D;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CurrentSession_D;
	

	
	// ---------- 상태 ----------
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_ConsentStatus;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Consent;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_PreTest;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_PostTest;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Satisfaction;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_PreTestStatus;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_PostTestStatus;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_SatisfactionStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	FLinearColor StatusDoneColor = FLinearColor(0.137f, 0.549f, 0.349f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	FLinearColor StatusPendingColor = FLinearColor(0.862f, 0.231f, 0.231f, 1.f);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movie Tabs")
	FLinearColor MovieNormalColor = FLinearColor().White;

	FLinearColor MovieSelectedColor = FLinearColor(0.051268f,0.068478f,0.130136f,1	);
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
	FLinearColor SessionNormalColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Session Tabs")
	FLinearColor SessionSelectedColor = FLinearColor(0.796f, 0.835f, 0.890f, 1.f);

	// ---------- 회기별 일정/특이사항 ----------
	UPROPERTY(meta=(BindWidget))
	UScrollBox* SB_Schedule;

	UPROPERTY(meta=(BindWidget))
	UMultiLineEditableTextBox* Edt_SessionNote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HeartRate|UI")
	TSubclassOf<UHeartRateRowWidget> ScheduleRowWidgetClass;

	// ---------- 콘텐츠 실행 ----------
	UPROPERTY(meta=(BindWidget))
	UButton* Btn_RunContent;

	// ----------구간이동 --------------
	
	UPROPERTY(meta=(BindWidget))
	UButton* Btn_MovieNum1;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_MovieNum2;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_MovieNum3;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_MovieNum4;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_MovieNum5;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* MovieText1;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MovieText2;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MovieText3;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MovieText4;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MovieText5;

	TArray<UTextBlock*> MovieTexts;
	TArray<UButton*> MovieButtons;
	//-----------일시정지,재시작,정지 -----
	UPROPERTY()
	ESessionRunState RunState = ESessionRunState::Idle;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Pause;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Resume;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Stop;

	UFUNCTION()
	void OnPauseClicked();

	UFUNCTION()
	void OnResumeClicked();


	UFUNCTION(BlueprintCallable, Category="Session")
	void BP_StopSession();
	
	UFUNCTION()
	void OnStopClicked();

	
	
protected:
	// ---------- 내부 상태 ----------
	UPROPERTY()
	UGameManager* GM = nullptr;

public:
	UPROPERTY(BlueprintReadOnly, Category="Student")
	FStudentRowData CurrentStudent;
	
	bool bHasStudent = false;

	int32 CurrentSessionIndex = 1;
	int32 CurrentMovieIndex = 1;
	// ================== 심박 ==================
	UPROPERTY(meta=(BindWidgetOptional), BlueprintReadWrite)
	UHeartRateGraphWidget* HeartRateGraph;

	UPROPERTY()
	AHrUDPManager* HrManager = nullptr;

	UPROPERTY()
	bool bRecordingHeartRate = false;

	UPROPERTY()
	TArray<FHeartRateLog> HeartRateLogs; // 그래프용 (항상 30개 유지)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HeartRate")
	int32 MaxHeartRatePoints = 30;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_AvgBpm;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_CurrentBpm;

	//  회기별 스케줄 로그(1~5)
	UPROPERTY()
	TArray<FHeartRateLogArray> SessionScheduleLogs;

	//  TutorialEnd 이후에만 스케줄 기록 허용
	UPROPERTY()
	bool bHasHeartStats = false;

	UPROPERTY()
	float LastAvgBpm = 0.f;

	UPROPERTY()
	float LastStdDev = 0.f;

	//  TutorialEnd 계산용 누적
	UPROPERTY()
	int64 HrSum = 0;

	UPROPERTY()
	int64 HrSumSquares = 0;

	UPROPERTY()
	int32 HrCount = 0;

	// HrUDPManager 델리게이트 콜백
	UFUNCTION()
	void OnHeartRateReceived(int32 BPM, int64 TimestampMs);

	// TutorialEnd(위젯에서 계산)
	void HandleTutorialEnd();

	// ================== 더미 ==================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HeartRate|Dummy")
	bool bUseDummyHeartRate = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HeartRate|Dummy")
	bool bAutoTutorialEndAfter30Dummy = true;

	FTimerHandle DummyHeartRateTimerHandle;

	UPROPERTY()
	int32 DummyReceiveCount = 0;

	UFUNCTION()
	void GenerateDummyHeartRate();

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
	void OnMovie1Clicked();
	UFUNCTION()
	void OnMovie2Clicked();
	UFUNCTION()
	void OnMovie3Clicked();
	UFUNCTION()
	void OnMovie4Clicked();
	UFUNCTION()
	void OnMovie5Clicked();

	void SetMovieIndex(int32 NewIndex);
	void UpdateMovieButtonVisual();
	
	
	UFUNCTION()
	void OnRunContentClicked();

	// ---------- 내부 헬퍼 ----------
	void RefreshHeaderUI();
	void RefreshStatusCards();
	void RefreshSessionUI();

	void SetSessionIndex(int32 NewIndex);
	void UpdateSessionButtonVisual();

	void SetStatusText(UTextBlock* Target, bool bDone,
		const FString& DoneText = TEXT("완료"),
		const FString& PendingText = TEXT("미완료"));

	void ClearSchedule();
	void AddScheduleLine(const FString& TimeText, const FString& BpmText);
	void AddScheduleLineFromLog(const FHeartRateLog& Log);


	// SessionScheduleLogs[0..4]에 서버에서 받은 로그를 채워넣기
	void BuildSessionScheduleFromStudent(const FStudentRowData& Student);

	// 특정 회기 로그 찾기(안전하게)
	const FSessionHeartRateLogs* FindServerSchedule(int32 SessionIndex) const;



	UFUNCTION(BlueprintCallable, Category="Consent")
	void ApplyConsentAgreedAndSend();

	UFUNCTION(BlueprintCallable)
	void ApplyPreTestScoreAndSend(int32 InPre1, int32 InPre2, int32 InPre3, int32 InPre4);

	UFUNCTION(BlueprintCallable)
	void ApplyPreTestDrugScoreAndSend(int32 InPre1, int32 InPre2, int32 InPre3, int32 InPre4
		,int32 InPre5, int32 InPre6, int32 InPre7, int32 InPre8);

	
	UFUNCTION(BlueprintCallable)
	void ApplyPostTestScoreAndSend(int32 InPost1, int32 InPost2, int32 InPost3, int32 InPost4);

	UFUNCTION(BlueprintCallable)
	void ApplyPostTestDrugScoreAndSend(int32 InPost1, int32 InPost2, int32 InPost3, int32 InPost4
		,int32 InPost5, int32 InPost6, int32 InPost7, int32 InPost8);

	UFUNCTION(BlueprintCallable)
	void ApplySatisfactionAndSend(int32 InSatisfaction);


protected:
	UFUNCTION()
	void HandleSessionCompleted();

	void UpdateSessionButtonEnabled();//버튼 비활성화
	
	UFUNCTION()
	void UpdateRunContentButtonEnabled();//컨텐츠버튼


	UFUNCTION(BlueprintCallable)
	void ResetToInitialState();
	
	void ClearHeartRateRuntime();


	// 연속 감지
	UPROPERTY()
	int32 UpperOverStreak = 0;      // Upper 이상 연속 횟수

	UPROPERTY()
	bool bUpperTriggered = false;

	UPROPERTY()
	int32 PeakBpmAfterTrigger = 0;

	// 서버 마크 응답
	UPROPERTY()
	bool bWaitingServerMark = false;

	UPROPERTY()
	int32 PendingPeakBpm = 0;

	UFUNCTION()
	void HandleServerHeartRateMarkReceived(const FString& InmateId, int32 SessionIndex, int32 ServerMark);
};
