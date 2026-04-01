// StudentSessionMonitorWidget.cpp

#include "WidgetActor/StudentSessionMonitorWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "EngineUtils.h"
#include "Components/Image.h"

#include "MojCmsClient/UDP/HrUDPManager.h"
#include "Manager/GameManager.h"
#include "WidgetActor/HeartRateGraphWidget.h"
#include "WidgetActor/HeartRateRowWidget.h"

void UStudentSessionMonitorWidget::NativeConstruct()
{
	Super::NativeConstruct();


	if (Btn_Pause)
		Btn_Pause->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnPauseClicked);

	if (Btn_Resume)
		Btn_Resume->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnResumeClicked);

	if (Btn_Stop)
		Btn_Stop->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnStopClicked);

	
	
	// 회기별 로그 저장공간 5개 확보
	SessionScheduleLogs.SetNum(5);

	// GameManager 캐시 + UDP 매니저 찾기 + 더미 타이머
	if (UWorld* World = GetWorld())
	{
		GM = World->GetGameInstance<UGameManager>();

		for (TActorIterator<AHrUDPManager> It(World); It; ++It)
		{
			HrManager = *It;
			break;
		}

		if (HrManager)
		{
			HrManager->OnHeartRateReceived.AddDynamic(
				this, &UStudentSessionMonitorWidget::OnHeartRateReceived);

		}

		if (GM)
		{
			GM->OnTutorialEnd.AddUObject(
				this,&UStudentSessionMonitorWidget::HandleTutorialEnd);
		}
		if (GM)
		{
			GM->OnSessionCompleted.AddUObject(
				this, &UStudentSessionMonitorWidget::HandleSessionCompleted);
		}

		if (GM)
		{
			GM->OnServerHeartRateMarkReceived.AddDynamic(
				this, &UStudentSessionMonitorWidget::HandleServerHeartRateMarkReceived);
		}

		if (Btn_RunContent)
		{
			Btn_RunContent->SetIsEnabled(false);
			Btn_RunContent->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnRunContentClicked);
		}

		if (bUseDummyHeartRate)
		{
			World->GetTimerManager().SetTimer(
				DummyHeartRateTimerHandle,
				this,
				&UStudentSessionMonitorWidget::GenerateDummyHeartRate,
				1.0f,
				true
			);
		}
	}

	// 검색 버튼 / 엔터 입력 바인딩
	if (Btn_Search)
	{
		Btn_Search->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSearchButtonClicked);
	}
	if (Edt_SearchId)
	{
		Edt_SearchId->OnTextCommitted.AddDynamic(this, &UStudentSessionMonitorWidget::OnSearchIdCommitted);
	}

	// 회기 탭 버튼 바인딩
	SessionButtons.Empty();
	if (Btn_Session1) SessionButtons.Add(Btn_Session1);
	if (Btn_Session2) SessionButtons.Add(Btn_Session2);
	if (Btn_Session3) SessionButtons.Add(Btn_Session3);
	if (Btn_Session4) SessionButtons.Add(Btn_Session4);
	if (Btn_Session5) SessionButtons.Add(Btn_Session5);

	if (Btn_Session1) Btn_Session1->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSession1Clicked);
	if (Btn_Session2) Btn_Session2->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSession2Clicked);
	if (Btn_Session3) Btn_Session3->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSession3Clicked);
	if (Btn_Session4) Btn_Session4->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSession4Clicked);
	if (Btn_Session5) Btn_Session5->OnClicked.AddDynamic(this, &UStudentSessionMonitorWidget::OnSession5Clicked);

	//구간이동 버튼 바인딩
	MovieButtons.Empty();
	if(Btn_MovieNum1) MovieButtons.Add(Btn_MovieNum1);
	if(Btn_MovieNum2) MovieButtons.Add(Btn_MovieNum2);
	if(Btn_MovieNum3) MovieButtons.Add(Btn_MovieNum3);
	if(Btn_MovieNum4) MovieButtons.Add(Btn_MovieNum4);
	if(Btn_MovieNum5) MovieButtons.Add(Btn_MovieNum5);
	if(MovieText1) MovieTexts.Add(MovieText1);
	if(MovieText2) MovieTexts.Add(MovieText2);
	if(MovieText3) MovieTexts.Add(MovieText3);
	if(MovieText4) MovieTexts.Add(MovieText4);
	if(MovieText5) MovieTexts.Add(MovieText5);

	
	if(Btn_MovieNum1) Btn_MovieNum1->OnClicked.AddDynamic(this,&UStudentSessionMonitorWidget::OnMovie1Clicked);
	if(Btn_MovieNum2) Btn_MovieNum2->OnClicked.AddDynamic(this,&UStudentSessionMonitorWidget::OnMovie2Clicked);
	if(Btn_MovieNum3) Btn_MovieNum3->OnClicked.AddDynamic(this,&UStudentSessionMonitorWidget::OnMovie3Clicked);
	if(Btn_MovieNum4) Btn_MovieNum4->OnClicked.AddDynamic(this,&UStudentSessionMonitorWidget::OnMovie4Clicked);
	if(Btn_MovieNum5) Btn_MovieNum5->OnClicked.AddDynamic(this,&UStudentSessionMonitorWidget::OnMovie5Clicked);
	
	
	// 초기 상태
	bHasStudent = false;
	CurrentSessionIndex = 1;
	CurrentMovieIndex = 1;
	UpdateMovieButtonVisual();
	UpdateSessionButtonVisual();
	UpdateSessionButtonEnabled();
	ClearSchedule();

	// 심박 UI 초기화
	bRecordingHeartRate = false;
	HeartRateLogs.Empty();

	bHasHeartStats = false;
	LastAvgBpm = 0.f;
	LastStdDev = 0.f;

	HrSum = 0;
	HrSumSquares = 0;
	HrCount = 0;
	DummyReceiveCount = 0;

	if (Txt_AvgBpm)
	{
		Txt_AvgBpm->SetText(FText::FromString(TEXT("평균HR -")));
	}
	if (Txt_CurrentBpm)
	{
		Txt_CurrentBpm->SetText(FText::FromString(TEXT("실시간HR -")));
	}

	UpdateRunContentButtonEnabled();
}

void UStudentSessionMonitorWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(DummyHeartRateTimerHandle);
	}
	Super::NativeDestruct();
}

bool UStudentSessionMonitorWidget::LoadStudentById(const FString& InId)
{
	if (!GM)
	{
		if (UWorld* World = GetWorld())
		{
			GM = World->GetGameInstance<UGameManager>();
		}
	}
	if (!GM)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadStudentById - GameManager is NULL"));
		return false;
	}

	FStudentRowData Found;
	if (GM->FindStudentById(InId, Found))
	{
		CurrentStudent = Found;
		bHasStudent = true;
		CurrentSessionIndex = 1;
		CurrentMovieIndex=1;
		BuildSessionScheduleFromStudent(CurrentStudent);
		//HandleSessionCompleted();
		RefreshHeaderUI();
		RefreshStatusCards();
		RefreshSessionUI();
		UpdateSessionButtonEnabled();
		UpdateRunContentButtonEnabled();
		

		if (SearchSwitcher)
		{
			SearchSwitcher->SetActiveWidgetIndex(2);
		}
		return true;
	}

	// 실패
	bHasStudent = false;
	UpdateRunContentButtonEnabled();

	if (Txt_TitleNameAndId)
	{
		Txt_TitleNameAndId->SetText(FText::FromString(TEXT("검색 결과 없음")));
	}
	if (Edt_SessionNote)
	{
		Edt_SessionNote->SetText(FText::GetEmpty());
	}

	ClearSchedule();

	if (SearchSwitcher)
	{
		SearchSwitcher->SetActiveWidgetIndex(1);
	}
	return false;
}

/* ---------------- 검색 이벤트 ---------------- */

void UStudentSessionMonitorWidget::OnSearchButtonClicked()
{
	if (!Edt_SearchId)
	{
		if (SearchSwitcher) SearchSwitcher->SetActiveWidgetIndex(0);
		return;
	}

	const FString Id = Edt_SearchId->GetText().ToString().TrimStartAndEnd();
	if (Id.IsEmpty())
	{
		if (SearchSwitcher) SearchSwitcher->SetActiveWidgetIndex(1);
		return;
	}

	LoadStudentById(Id);
}

void UStudentSessionMonitorWidget::OnSearchIdCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	if (CommitType != ETextCommit::OnEnter)
		return;

	const FString Id = Text.ToString().TrimStartAndEnd();
	if (Id.IsEmpty())
	{
		if (SearchSwitcher) SearchSwitcher->SetActiveWidgetIndex(1);
		return;
	}

	LoadStudentById(Id);
}

/* ---------------- 회기 탭 ---------------- */

void UStudentSessionMonitorWidget::SetSessionIndex(int32 NewIndex)
{
	if (NewIndex < 1 || NewIndex > 5)
		return;
	if (CurrentSessionIndex == NewIndex)
		return;

	CurrentSessionIndex = NewIndex;
	UpdateSessionButtonVisual();
	RefreshSessionUI();
}

void UStudentSessionMonitorWidget::SetMovieIndex(int32 NewIndex)
{
	if (NewIndex < 1 || NewIndex > 5) return;
	if (CurrentMovieIndex == NewIndex) return;

	CurrentMovieIndex = NewIndex;
	UpdateMovieButtonVisual();

	// TODO: 여기서 영상 구간 이동 요청
	GM->Send_SectionMove(CurrentMovieIndex - 1);
}

void UStudentSessionMonitorWidget::UpdateMovieButtonVisual()
{
	for (int32 i = 0; i < MovieButtons.Num(); ++i)
	{
		UButton* Btn = MovieButtons[i];
		if (!Btn) continue;

		const bool bSelected = (i == CurrentMovieIndex - 1);
		const FLinearColor Color = bSelected ? MovieSelectedColor : MovieNormalColor;

		FButtonStyle Style = Btn->WidgetStyle;
		Style.Normal.TintColor   = FSlateColor(Color);
		Style.Hovered.TintColor  = FSlateColor(Color);
		Style.Pressed.TintColor  = FSlateColor(Color);
		Btn->SetStyle(Style);
	}
	for (int32 i = 0; i < MovieTexts.Num(); ++i)
	{
		UTextBlock* Txt = MovieTexts[i];
		if (!Txt) continue;

		const bool bSelected = (i == CurrentMovieIndex - 1);

		Txt->SetColorAndOpacity(bSelected
			? FSlateColor(MovieNormalColor)
			: FSlateColor(MovieSelectedColor));
	}
}

void UStudentSessionMonitorWidget::OnSession1Clicked() { SetSessionIndex(1); }
void UStudentSessionMonitorWidget::OnSession2Clicked() { SetSessionIndex(2); }
void UStudentSessionMonitorWidget::OnSession3Clicked() { SetSessionIndex(3); }
void UStudentSessionMonitorWidget::OnSession4Clicked() { SetSessionIndex(4); }
void UStudentSessionMonitorWidget::OnSession5Clicked() { SetSessionIndex(5); }

void UStudentSessionMonitorWidget::OnMovie1Clicked() {SetMovieIndex(1);}
void UStudentSessionMonitorWidget::OnMovie2Clicked() {SetMovieIndex(2);}
void UStudentSessionMonitorWidget::OnMovie3Clicked() {SetMovieIndex(3);}
void UStudentSessionMonitorWidget::OnMovie4Clicked() {SetMovieIndex(4);}
void UStudentSessionMonitorWidget::OnMovie5Clicked() {SetMovieIndex(5);}





void UStudentSessionMonitorWidget::UpdateSessionButtonVisual()
{
	for (int32 i = 0; i < SessionButtons.Num(); ++i)
	{
		if (!SessionButtons[i]) continue;

		const bool bSelected = (i == CurrentSessionIndex - 1);
		const FLinearColor Color = bSelected ? SessionSelectedColor : SessionNormalColor;

		FButtonStyle Style = SessionButtons[i]->WidgetStyle;
		Style.Normal.TintColor   = FSlateColor(Color);
		Style.Hovered.TintColor  = FSlateColor(Color);
		Style.Pressed.TintColor  = FSlateColor(Color);
		SessionButtons[i]->SetStyle(Style);
	}
}

/* ---------------- 콘텐츠 실행 ---------------- */

void UStudentSessionMonitorWidget::OnRunContentClicked()
{
	UpperOverStreak = 0;
	bUpperTriggered = false;
	PeakBpmAfterTrigger = 0;
	PendingPeakBpm = 0;
	Edt_SearchId->SetVisibility(ESlateVisibility::Collapsed);
	SearchImage->SetVisibility(ESlateVisibility::Collapsed);
	SearchSwitcher->SetActiveWidgetIndex(3);
	RunState = ESessionRunState::Running;
	// 콘텐츠 시작
	bRecordingHeartRate = true;

	// 그래프 초기화
	HeartRateLogs.Empty();
	if (HeartRateGraph)
	{
		HeartRateGraph->SetLogs(HeartRateLogs);
	}

	// 누적 초기화 (평균/표준편차용)
	HrSum = 0;
	HrSumSquares = 0;
	HrCount = 0;

	// TutorialEnd 전까지 스케줄 기록 막기
	bHasHeartStats = false;
	LastAvgBpm = 0.f;
	LastStdDev = 0.f;
	

	// 더미 카운트 초기화
	DummyReceiveCount = 0;

	SessionScheduleLogs[CurrentSessionIndex - 1].Logs.Empty();
	ClearSchedule();

	if (GM && bHasStudent)
	{
		GM->Send_RunContentStart(CurrentStudent, CurrentSessionIndex);
	}

	
	OnRunContentRequested.Broadcast();
}

void UStudentSessionMonitorWidget::OnResumeClicked()
{
	if (RunState != ESessionRunState::Paused)
		return;

	RunState = ESessionRunState::Running;
	bRecordingHeartRate = true;

	if (GM && bHasStudent)
	{
		GM->Send_SessionResume();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Session Resumed"));
}

void UStudentSessionMonitorWidget::BP_StopSession()
{
	OnStopClicked();
	GM->RecvStopSignal.Broadcast(true);


	RunState = ESessionRunState::Finished;
	bRecordingHeartRate = false;
	if (Edt_SearchId) Edt_SearchId->SetText(FText::GetEmpty());
	if (SearchSwitcher) SearchSwitcher->SetActiveWidgetIndex(0);
	bHasStudent = false;
	ClearSchedule();
}


void UStudentSessionMonitorWidget::OnStopClicked()
{
	if (RunState == ESessionRunState::Finished)
		return;
	
	RunState = ESessionRunState::Finished;
	bRecordingHeartRate = false;

	HandleTutorialEnd();

	if (GM && bHasStudent)
	{
		GM->Send_SessionStop();
	}

	Edt_SearchId->SetVisibility(ESlateVisibility::Visible);
	SearchImage->SetVisibility(ESlateVisibility::Visible);
	if (Edt_SearchId) Edt_SearchId->SetText(FText::GetEmpty());
	if (SearchSwitcher) SearchSwitcher->SetActiveWidgetIndex(0);

	bHasStudent = false;
	ClearSchedule();

	UE_LOG(LogTemp, Warning, TEXT("Session Finished"));
}


void UStudentSessionMonitorWidget::OnPauseClicked()
{
	if (RunState != ESessionRunState::Running)
		return;

	RunState = ESessionRunState::Paused;
	bRecordingHeartRate = false;

	if (GM && bHasStudent)
	{
		GM->Send_SessionPause();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Session Paused"));
}

/* ---------------- UI 갱신 ---------------- */

void UStudentSessionMonitorWidget::RefreshHeaderUI()
{
	if (!bHasStudent)
		return;

	if (Txt_TitleNameAndId)
	{
		const FString Title = FString::Printf(TEXT("%s (%s)"), *CurrentStudent.Name, *CurrentStudent.ID);
		Txt_TitleNameAndId->SetText(FText::FromString(Title));
		Txt_TitleNameAndId_D->SetText(FText::FromString(Title));
	}

	if(Txt_Birth_D)
	{
		Txt_Birth_D->SetText(FText::FromString(FString::Printf(TEXT("생년월일: %s"), *CurrentStudent.Birth)));
	}

	if (Txt_CrimeType)
	{
		Txt_CrimeType->SetText(FText::FromString(FString::Printf(TEXT("범죄유형: %s"), *CurrentStudent.CrimeType)));
		Txt_CrimeType_D->SetText(FText::FromString(FString::Printf(TEXT("범죄유형: %s"), *CurrentStudent.CrimeType)));
	}

	if (Txt_VRType)
	{
		Txt_VRType->SetText(FText::FromString(FString::Printf(TEXT("VR유형: %s"), *CurrentStudent.VrType)));
		Txt_VRType_D->SetText(FText::FromString(FString::Printf(TEXT("VR유형: %s"), *CurrentStudent.VrType)));
	}

	if(Txt_EduCourse_D)
	{
		Txt_EduCourse_D->SetText(FText::FromString(FString::Printf(TEXT("교육과정: %s"), *CurrentStudent.EduCourse)));
	}
	if(Txt_EduPeriod_D)
	{
		Txt_EduPeriod_D->SetText(FText::FromString(FString::Printf(TEXT("교육시기: %s"), *CurrentStudent.EduPeriod)));
	}

	if (Txt_CurrentSession)
	{
		Txt_CurrentSession->SetText(FText::FromString(FString::Printf(TEXT("현재 회기: %s회기"), *CurrentStudent.VrSession)));
		Txt_CurrentSession_D->SetText(FText::FromString(FString::Printf(TEXT("현재 회기: %s회기"), *CurrentStudent.VrSession)));
	}
}

void UStudentSessionMonitorWidget::SetStatusText(UTextBlock* Target, bool bDone,
	const FString& DoneText, const FString& PendingText)
{
	if (!Target) return;

	Target->SetText(FText::FromString(bDone ? DoneText : PendingText));
	const FSlateColor Col = bDone ? FSlateColor(StatusDoneColor) : FSlateColor(StatusPendingColor);
	Target->SetColorAndOpacity(Col);
}

void UStudentSessionMonitorWidget::RefreshStatusCards()
{
	if (!bHasStudent) return;

	const bool bConsentDone = (CurrentStudent.Consent_Test != TEXT("-"));
	const bool bPreDone     = (CurrentStudent.Pre_Test != TEXT("-"));
	const bool bPostDone    = (CurrentStudent.Post_Test != TEXT("-"));
	const bool bSatDone     = (CurrentStudent.Satisfaction != 0);

	
	const bool bPostUnlocked = CurrentStudent.bAllSessionsCompleted;
	
	if (Txt_ConsentStatus)      SetStatusText(Txt_ConsentStatus,      bConsentDone);
	if (Txt_PreTestStatus)      SetStatusText(Txt_PreTestStatus,      bPreDone);
	if (Txt_PostTestStatus)     SetStatusText(Txt_PostTestStatus,     bPostDone);
	if (Txt_SatisfactionStatus) SetStatusText(Txt_SatisfactionStatus, bSatDone, TEXT("완료"), TEXT("미완료"));

	// 버튼 활성화 규칙
	if (Btn_Consent)
		Btn_Consent->SetIsEnabled(!bConsentDone);

	//동의서 완료되어야 사전검사 가능
	if (Btn_PreTest)
		Btn_PreTest->SetIsEnabled(bConsentDone && !bPreDone);
	
	//사전 완료되어야 사후 가능 + 5회기까지 끝나야함
	if (Btn_PostTest)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[PostTest Enable Check] PreDone=%s, PostDone=%s, PostUnlocked=%s"),
			bPreDone ? TEXT("true") : TEXT("false"),
			bPostDone ? TEXT("true") : TEXT("false"),
			bPostUnlocked ? TEXT("true") : TEXT("false")
		);

		Btn_PostTest->SetIsEnabled(bPreDone && !bPostDone && bPostUnlocked);
	}



	// 사후 완료되어야 만족도 가능
	if (Btn_Satisfaction)
		Btn_Satisfaction->SetIsEnabled(bPostDone && !bSatDone);

	UpdateRunContentButtonEnabled();
}



void UStudentSessionMonitorWidget::RefreshSessionUI()
{
	if (!bHasStudent)
	{
		if (Edt_SessionNote) Edt_SessionNote->SetText(FText::GetEmpty());
		ClearSchedule();
		return;
	}

	// 특이사항 표시 (서버에서 온 Note)
	if (Edt_SessionNote)
	{
		const int32 Index = CurrentSessionIndex - 1;
		if (CurrentStudent.SessionNotes.IsValidIndex(Index))
		{
			Edt_SessionNote->SetText(FText::FromString(CurrentStudent.SessionNotes[Index].Note));
		}
		else
		{
			Edt_SessionNote->SetText(FText::GetEmpty());
		}
	}

	//  회기별 스케줄 로그 표시
	ClearSchedule();
	
	const int32 SessionIdx = CurrentSessionIndex - 1;
	if (SessionScheduleLogs.IsValidIndex(SessionIdx))
	{
		for (const FHeartRateLog& Log : SessionScheduleLogs[SessionIdx].Logs)
		{
			AddScheduleLineFromLog(Log);
		}
	}
}

/* ---------------- 스케줄 UI ---------------- */

void UStudentSessionMonitorWidget::ClearSchedule()
{
	if (SB_Schedule)
	{
		SB_Schedule->ClearChildren();
	}
}

void UStudentSessionMonitorWidget::AddScheduleLine(const FString& TimeText, const FString& BpmText)
{
	UE_LOG(LogTemp, Warning, TEXT("AddScheduleLine called: %s %s"), *TimeText, *BpmText);

	if (!SB_Schedule) return;
	if (!ScheduleRowWidgetClass) return;

	UHeartRateRowWidget* RowW = CreateWidget<UHeartRateRowWidget>(GetWorld(), ScheduleRowWidgetClass);
	if (!RowW) return;

	RowW->Setup(TimeText, BpmText);
	SB_Schedule->AddChild(RowW);
}

void UStudentSessionMonitorWidget::AddScheduleLineFromLog(const FHeartRateLog& Log)
{
	const FString MovieStr = FString::Printf(TEXT("[영상번호:%d]"), Log.ServerMark);
	const FString BpmStr  = FString::Printf(TEXT("심박수 %d bpm"), Log.Bpm);
	AddScheduleLine(MovieStr, BpmStr);
}

/* ---------------- 심박 수신 ---------------- */

static FString MakeKstTimeHms(int64 TimestampMs)
{
	// UTC 기준
	FDateTime UtcTime = FDateTime::FromUnixTimestamp(TimestampMs / 1000);
	UtcTime += FTimespan::FromMilliseconds(TimestampMs % 1000);

	// KST = UTC + 9h
	const FDateTime KstTime = UtcTime + FTimespan::FromHours(9);

	return FString::Printf(
		TEXT("%02d:%02d:%02d"),
		KstTime.GetHour(),
		KstTime.GetMinute(),
		KstTime.GetSecond()
	);
}



void UStudentSessionMonitorWidget::OnHeartRateReceived(int32 BPM, int64 TimestampMs)
{
	if (RunState != ESessionRunState::Running)
		return;

	if (!bRecordingHeartRate)
		return;

	// ===== 1) 그래프용 항상 기록 =====
	const FHeartRateLog NewGraphLog{ BPM, TimestampMs, 0 };
	HeartRateLogs.Add(NewGraphLog);
	if (HeartRateLogs.Num() > MaxHeartRatePoints)
	{
		HeartRateLogs.RemoveAt(0, HeartRateLogs.Num() - MaxHeartRatePoints, false);
	}

	if (HeartRateGraph)
		HeartRateGraph->SetLogs(HeartRateLogs);

	if (Txt_CurrentBpm)
		Txt_CurrentBpm->SetText(FText::FromString(FString::Printf(TEXT("실시간HR %d bpm"), BPM)));

	// ===== 2) 통계 누적 =====
	HrSum += BPM;
	HrSumSquares += (int64)BPM * (int64)BPM;
	HrCount++;

	if (!bHasHeartStats)
		return;
	
	if (bWaitingServerMark)
		return;

	const float Upper = LastAvgBpm + 2.f * LastStdDev;
	UE_LOG(LogTemp, Log, TEXT("Upper : %f"), Upper);
	// ===== 
	if ((float)BPM >= Upper)
	{
		UE_LOG(LogTemp, Log, TEXT("BPM : %f"), (float)BPM);
		// 피크 갱신
		if (BPM > PeakBpmAfterTrigger)
		{
			PeakBpmAfterTrigger = BPM;
			UE_LOG(LogTemp, Log, TEXT("PeakBpmAfterTrigger"));
		}

		
		if (!bUpperTriggered)
		{
			UE_LOG(LogTemp, Log, TEXT("UpperOverStreak"));
			UpperOverStreak++;
			if (UpperOverStreak >= 3)
			{
				UE_LOG(LogTemp, Log, TEXT("CheckUpperOverStreak"));
				bUpperTriggered = true;
			}
		}

		return;
	}

	// =====
	if (bUpperTriggered)
	{
		UE_LOG(LogTemp, Log, TEXT("PendingPeakBpm"));
		PendingPeakBpm = PeakBpmAfterTrigger;
		bWaitingServerMark = true;

		if (GM && bHasStudent)
		{
			UE_LOG(LogTemp, Log, TEXT("Send_RequestMovieNum"));
			GM->Send_RequestMovieNum(CurrentStudent.ID, CurrentSessionIndex);
		}

		// 다음 이벤트 대비 리셋
		bUpperTriggered = false;
		UpperOverStreak = 0;
		PeakBpmAfterTrigger = 0;
	}
}




/* ---------------- TutorialEnd 처리(위젯에서 Avg/StdDev 계산) ---------------- */

void UStudentSessionMonitorWidget::HandleTutorialEnd()
{
	if (HrCount <= 0)
	{
		LastAvgBpm = 0.f;
		LastStdDev = 0.f;
		bHasHeartStats = true;
		return;
	}

	LastAvgBpm = (float)HrSum / (float)HrCount;

	const float MeanSq = (float)HrSumSquares / (float)HrCount;
	float Variance = MeanSq - (LastAvgBpm * LastAvgBpm);
	Variance = FMath::Max(0.f, Variance);
	LastStdDev = FMath::Sqrt(Variance);

	bHasHeartStats = true;

	UE_LOG(LogTemp, Warning, TEXT("[TutorialEnd] Avg=%.2f StdDev=%.2f Count=%d"), LastAvgBpm, LastStdDev, HrCount);

	if (Txt_AvgBpm)
	{
		Txt_AvgBpm->SetText(
			FText::FromString(
				FString::Printf(TEXT("초기HR %.1f bpm"), LastAvgBpm)
			)
		);
	}
	
	if (HeartRateGraph)
	{
		HeartRateGraph->SetLogs(HeartRateLogs);
	}

}


const FSessionHeartRateLogs* UStudentSessionMonitorWidget::FindServerSchedule(int32 SessionIndex) const
{
	// CurrentStudent.SessionHeartRateSchedules 에서 SessionIndex 같은 회기 찾기
	for (const FSessionHeartRateLogs& S : CurrentStudent.SessionHeartRateSchedules)
	{
		if (S.SessionIndex == SessionIndex)
			return &S;
	}
	return nullptr;
}

void UStudentSessionMonitorWidget::BuildSessionScheduleFromStudent(const FStudentRowData& Student)
{
	// 5회기 공간 보장
	SessionScheduleLogs.SetNum(5);

	// 초기화
	for (int32 i = 0; i < 5; ++i)
	{
		SessionScheduleLogs[i].Logs.Empty();
	}

	// 서버 데이터(Student.SessionHeartRateSchedules) -> 위젯 캐시(SessionScheduleLogs)로 복사
	for (const FSessionHeartRateLogs& Src : Student.SessionHeartRateSchedules)
	{
		const int32 Idx = Src.SessionIndex - 1;
		if (Idx >= 0 && Idx < 5)
		{
			SessionScheduleLogs[Idx].Logs = Src.Logs; // 로그만 복사
		}
	}
}




/* ---------------- 더미 심박 ---------------- */

void UStudentSessionMonitorWidget::GenerateDummyHeartRate()
{
	if (!bRecordingHeartRate)
		return;

	const int32 DummyBpm = FMath::RandRange(50, 200);

	const FDateTime NowUtc = FDateTime::UtcNow();
	const int64 TimestampMs = NowUtc.ToUnixTimestamp() * 1000 + NowUtc.GetMillisecond();

	// 실제 수신과 동일 경로
	OnHeartRateReceived(DummyBpm, TimestampMs);
}



// ---------------------동의서-----------------------

void UStudentSessionMonitorWidget::ApplyConsentAgreedAndSend()
{
	if (!bHasStudent) return;

	// 이미 동의면 스킵
	if (CurrentStudent.Consent_Test != TEXT("-"))
	{
		RefreshStatusCards();
		return;
	}
	
	const FString ConsentText = TEXT("완료"); 
	CurrentStudent.Consent_Test = ConsentText;
	
	if (GM)
	{
		GM->UpdateStudentConsentLocal(CurrentStudent.ID, ConsentText);
	}
	
	RefreshStatusCards();
	
	if (GM)
	{
		GM->Send_ConsentAgreed(CurrentStudent.ID);
	}
}


void UStudentSessionMonitorWidget::ApplyPreTestScoreAndSend(
	int32 InPre1, int32 InPre2, int32 InPre3, int32 InPre4)
{
	if (!bHasStudent) return;

	if (CurrentStudent.Consent_Test == TEXT("-"))
	{
		UE_LOG(LogTemp, Warning, TEXT("PreTest blocked: Consent not completed."));
		RefreshStatusCards();
		return;
	}

	if (CurrentStudent.Pre_Test != TEXT("-"))
	{
		RefreshStatusCards();
		return;
	}
	
	
	CurrentStudent.Pre_Test = "완료";

	CurrentStudent.Pre1 = InPre1;
	CurrentStudent.Pre2 = InPre2;
	CurrentStudent.Pre3 = InPre3;
	CurrentStudent.Pre4 = InPre4;

	// 로컬 StudentRows 동기화 
	if (GM)
	{
		GM->UpdateStudentPreTestLocal(
			CurrentStudent.ID,"완료",
			InPre1, InPre2, InPre3, InPre4
		);
	}

	// UI 상태 카드 갱신
	RefreshStatusCards();

	//서버 전송
	if (GM)
	{
		GM->Send_PreTestUpdate(
			CurrentStudent.ID,
			InPre1, InPre2, InPre3, InPre4
		);
	}
}

void UStudentSessionMonitorWidget::ApplyPreTestDrugScoreAndSend(int32 InPre1, int32 InPre2, int32 InPre3, int32 InPre4
		,int32 InPre5, int32 InPre6, int32 InPre7, int32 InPre8)
{
	if (!bHasStudent) return;

	if (CurrentStudent.Consent_Test == TEXT("-"))
	{
		UE_LOG(LogTemp, Warning, TEXT("PreTest blocked: Consent not completed."));
		RefreshStatusCards();
		return;
	}

	if (CurrentStudent.Pre_Test != TEXT("-"))
	{
		RefreshStatusCards();
		return;
	}
	
	
	CurrentStudent.Pre_Test = "완료";

	CurrentStudent.Pre1 = InPre1;
	CurrentStudent.Pre2 = InPre2;
	CurrentStudent.Pre3 = InPre3;
	CurrentStudent.Pre4 = InPre4;
	CurrentStudent.Pre5 = InPre5;
	CurrentStudent.Pre6 = InPre6;
	CurrentStudent.Pre7 = InPre7;
	CurrentStudent.Pre8 = InPre8;

	// 로컬 StudentRows 동기화 
	if (GM)
	{
		GM->UpdateStudentPreTestDrugLocal(
			CurrentStudent.ID,"완료",
			InPre1, InPre2, InPre3, InPre4,InPre5,InPre6,InPre7,InPre8
		);
	}

	// UI 상태 카드 갱신
	RefreshStatusCards();

	//서버 전송
	if (GM)
	{
		GM->Send_PreTestDrugUpdate(
			CurrentStudent.ID,
			InPre1, InPre2, InPre3, InPre4,InPre5,InPre6,InPre7,InPre8
		);
	}
}


void UStudentSessionMonitorWidget::ApplyPostTestScoreAndSend(
	int32 InPost1, int32 InPost2, int32 InPost3, int32 InPost4)
{
	if (!bHasStudent) return;
	
	if (CurrentStudent.Pre_Test == TEXT("-"))
	{
		UE_LOG(LogTemp, Warning, TEXT("PostTest blocked: PreTest not completed."));
		RefreshStatusCards();
		return;
	}
	
	if (CurrentStudent.Post_Test != TEXT("-"))
	{
		RefreshStatusCards();
		return;
	}
	
	CurrentStudent.Post_Test = "완료";
	CurrentStudent.Post1 = InPost1;
	CurrentStudent.Post2 = InPost2;
	CurrentStudent.Post3 = InPost3;
	CurrentStudent.Post4 = InPost4;

	// 2️ GameManager 로컬
	if (GM)
	{
		GM->UpdateStudentPostTestLocal(
			CurrentStudent.ID,"완료",
			InPost1, InPost2, InPost3, InPost4
		);
	}

	// UI 즉시 반영
	RefreshStatusCards();

	// 서버 전송
	if (GM)
	{
		GM->Send_PostTestUpdate(
			CurrentStudent.ID,
			InPost1, InPost2, InPost3, InPost4
		);
	}
}

void UStudentSessionMonitorWidget::ApplyPostTestDrugScoreAndSend(int32 InPost1, int32 InPost2, int32 InPost3,
	int32 InPost4, int32 InPost5, int32 InPost6, int32 InPost7, int32 InPost8)
{
	if (!bHasStudent) return;
	
	if (CurrentStudent.Pre_Test == TEXT("-"))
	{
		UE_LOG(LogTemp, Warning, TEXT("PostTest blocked: PreTest not completed."));
		RefreshStatusCards();
		return;
	}
	
	if (CurrentStudent.Post_Test != TEXT("-"))
	{
		RefreshStatusCards();
		return;
	}
	
	CurrentStudent.Post_Test = "완료";
	CurrentStudent.Post1 = InPost1;
	CurrentStudent.Post2 = InPost2;
	CurrentStudent.Post3 = InPost3;
	CurrentStudent.Post4 = InPost4;
	CurrentStudent.Post5 = InPost5;
	CurrentStudent.Post6 = InPost6;
	CurrentStudent.Post7 = InPost7;
	CurrentStudent.Post8 = InPost8;

	// 2️ GameManager 로컬
	if (GM)
	{
		GM->UpdateStudentPostTestDrugLocal(
			CurrentStudent.ID,"완료",
			InPost1, InPost2, InPost3, InPost4,InPost5,InPost6,InPost7,InPost8
		);
	}

	// UI 즉시 반영
	RefreshStatusCards();

	// 서버 전송
	if (GM)
	{
		GM->Send_PostTestDrugUpdate(
			CurrentStudent.ID,
			InPost1, InPost2, InPost3, InPost4,InPost5,InPost6,InPost7,InPost8
		);
	}
}

void UStudentSessionMonitorWidget::ApplySatisfactionAndSend(int32 InSatisfaction)
{
	if (!bHasStudent) return;


	if (CurrentStudent.Post_Test == TEXT("-"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Satisfaction blocked: PostTest not completed."));
		RefreshStatusCards();
		return;
	}
	
	if (CurrentStudent.Satisfaction != 0)
	{
		RefreshStatusCards();
		return;
	}

	CurrentStudent.Satisfaction = InSatisfaction;

	
	if (GM)
	{
		GM->UpdateStudentSatisfactionLocal(CurrentStudent.ID, InSatisfaction);
	}

	RefreshStatusCards();

	
	if (GM)
	{
		GM->Send_SatisfactionUpdate(CurrentStudent.ID, InSatisfaction);
	}
}




void UStudentSessionMonitorWidget::HandleSessionCompleted()
{

	if (!bHasStudent) return;
	
	if (CurrentStudent.VrSession== TEXT("5"))
	{
		CurrentStudent.bAllSessionsCompleted = true;
	}
	else
	{
		int32 Cur = FCString::Atoi(*CurrentStudent.VrSession);
		int32 Next = FMath::Clamp(Cur + 1, 1, 5);
		CurrentStudent.VrSession = FString::FromInt(Next);
	}

	if (GM)
	{
		GM->UpsertStudentRow(CurrentStudent);	
	}

	RefreshHeaderUI();
	RefreshStatusCards();
	UpdateSessionButtonEnabled();
}

void UStudentSessionMonitorWidget::UpdateSessionButtonEnabled()
{
	if (!bHasStudent)
	{
		// 학생 없으면 전부 비활성화
		for (UButton* Btn : SessionButtons)
		{
			if (Btn) Btn->SetIsEnabled(false);
		}
		return;
	}

	int32 MaxSession = FCString::Atoi(*CurrentStudent.VrSession);
	MaxSession = FMath::Clamp(MaxSession, 1, 5);

	for (int32 i = 0; i < SessionButtons.Num(); ++i)
	{
		if (!SessionButtons[i]) continue;

		const int32 SessionNumber = i + 1;

		// 현재 회기보다 큰 버튼은 비활성화
		const bool bEnable = (SessionNumber <= MaxSession);
		SessionButtons[i]->SetIsEnabled(bEnable);
	}
}

void UStudentSessionMonitorWidget::UpdateRunContentButtonEnabled()
{
	if (!Btn_RunContent)
		return;
	
	if (!bHasStudent)
	{
		Btn_RunContent->SetIsEnabled(false);
		return;
	}

	// 동의서/사전검사 완료 여부
	const bool bConsentDone = (CurrentStudent.Consent_Test != TEXT("-"));
	const bool bPreDone     = (CurrentStudent.Pre_Test != TEXT("-"));

	// 둘 다 완료되어야 실행 가능
	Btn_RunContent->SetIsEnabled(bConsentDone && bPreDone);
}





void UStudentSessionMonitorWidget::ClearHeartRateRuntime()
{
	UpperOverStreak = 0;
	bUpperTriggered = false;
	PeakBpmAfterTrigger = 0;
	PendingPeakBpm = 0;
	// 심박 기록 중단 + 런타임 데이터 초기화
	RunState = ESessionRunState::Idle;
	bRecordingHeartRate = false;

	HeartRateLogs.Empty();
	bHasHeartStats = false;
	LastAvgBpm = 0.f;
	LastStdDev = 0.f;

	HrSum = 0;
	HrSumSquares = 0;
	HrCount = 0;
	DummyReceiveCount = 0;

	// 그래프 반영
	if (HeartRateGraph)
	{
		HeartRateGraph->SetLogs(HeartRateLogs);
	}

	// 스케줄 UI 비우기
	ClearSchedule();

	
	for (int32 i = 0; i < SessionScheduleLogs.Num(); ++i)
	{
		SessionScheduleLogs[i].Logs.Empty();
	}

	// 텍스트 초기화
	if (Txt_AvgBpm)     Txt_AvgBpm->SetText(FText::FromString(TEXT("평균HR -")));
	if (Txt_CurrentBpm) Txt_CurrentBpm->SetText(FText::FromString(TEXT("실시간HR -")));
}

void UStudentSessionMonitorWidget::ResetToInitialState()
{
	// 학생 상태 초기화
	bHasStudent = false;
	CurrentStudent = FStudentRowData();

	// 회기 UI 초기화
	CurrentSessionIndex = 1;
	UpdateSessionButtonVisual();
	UpdateSessionButtonEnabled();

	CurrentMovieIndex = 1;
	UpdateMovieButtonVisual();
	
	// 검색 UI 초기화
	if (Edt_SearchId)
	{
		Edt_SearchId->SetVisibility(ESlateVisibility::Visible);
		SearchImage->SetVisibility(ESlateVisibility::Visible);
		Edt_SearchId->SetText(FText::GetEmpty());
	}
	if (SearchSwitcher)
	{
		SearchSwitcher->SetActiveWidgetIndex(0);
	}

	// 헤더/상세 텍스트 초기화 
	if (Txt_TitleNameAndId)   Txt_TitleNameAndId->SetText(FText::FromString(TEXT("-")));
	if (Txt_TitleNameAndId_D) Txt_TitleNameAndId_D->SetText(FText::FromString(TEXT("-")));

	if (Edt_SessionNote) Edt_SessionNote->SetText(FText::GetEmpty());


	if (Btn_Consent)       Btn_Consent->SetIsEnabled(false);
	if (Btn_PreTest)       Btn_PreTest->SetIsEnabled(false);
	if (Btn_PostTest)      Btn_PostTest->SetIsEnabled(false);
	if (Btn_Satisfaction)  Btn_Satisfaction->SetIsEnabled(false);


	UpdateRunContentButtonEnabled();

	// 런타임 심박 데이터 초기화
	ClearHeartRateRuntime();
}


void UStudentSessionMonitorWidget::HandleServerHeartRateMarkReceived(
	const FString& InmateId,
	int32 SessionIndex,
	int32 ServerMark
)
{
	if (!bWaitingServerMark)
		return;

	// 혹시 다른 학생/회기 응답이 섞이면 방지
	if (!bHasStudent)
		return;

	if (InmateId != CurrentStudent.ID || SessionIndex != CurrentSessionIndex)
		return;

	//타임스탬프는 기록 안함 → 0
	FHeartRateLog MarkLog;
	MarkLog.Bpm = PendingPeakBpm;
	MarkLog.TimestampMs = 0;
	MarkLog.ServerMark = ServerMark;

	const int32 SIdx = CurrentSessionIndex - 1;
	if (SessionScheduleLogs.IsValidIndex(SIdx))
	{
		SessionScheduleLogs[SIdx].Logs.Add(MarkLog);
	}

	AddScheduleLineFromLog(MarkLog);

	// 로컬 StudentRows에도 반영
	if (GM)
	{
		GM->AppendSessionHeartRateLocal(CurrentStudent.ID, CurrentSessionIndex, MarkLog);

		//
		GM->Send_SessionHeartRateLogOnce(CurrentStudent.ID, CurrentSessionIndex, MarkLog.Bpm, MarkLog.ServerMark);
	}

	// 대기 해제
	bWaitingServerMark = false;
	PendingPeakBpm = 0;
}
