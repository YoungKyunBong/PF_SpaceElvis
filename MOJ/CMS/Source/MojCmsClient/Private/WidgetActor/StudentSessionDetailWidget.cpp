// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetActor/StudentSessionDetailWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Manager/GameManager.h"

void UStudentSessionDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// GameManager 캐시
	if (UWorld* World = GetWorld())
	{
		GM = World->GetGameInstance<UGameManager>();
	}
	

	// ----- 이벤트 바인딩 -----
	if (Btn_Search)
	{
		Btn_Search->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSearchButtonClicked);
	}

	if (Edt_SearchId)
	{
		Edt_SearchId->OnTextCommitted.AddDynamic(this, &UStudentSessionDetailWidget::OnSearchIdCommitted);
	}

	if (Btn_Session1) Btn_Session1->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSession1Clicked);
	if (Btn_Session2) Btn_Session2->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSession2Clicked);
	if (Btn_Session3) Btn_Session3->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSession3Clicked);
	if (Btn_Session4) Btn_Session4->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSession4Clicked);
	if (Btn_Session5) Btn_Session5->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnSession5Clicked);

	if (Btn_EditOrSave)
	{
		Btn_EditOrSave->OnClicked.AddDynamic(this, &UStudentSessionDetailWidget::OnEditOrSaveClicked);
	}

	SessionButtons.Empty();
	SessionButtons.Add(Btn_Session1);
	SessionButtons.Add(Btn_Session2);
	SessionButtons.Add(Btn_Session3);
	SessionButtons.Add(Btn_Session4);
	SessionButtons.Add(Btn_Session5);
	
	// 초기 상태: 편집 불가
	bEditing = false;
	ApplyEditingMode();

	// 처음엔 아무 학생도 없음
	bHasStudent = false;
	CurrentSessionIndex = 1;

	UpdateSessionButtonVisual();
}

bool UStudentSessionDetailWidget::LoadStudentById(const FString& InId)
{
	if (!GM)
	{
		GM = GetWorld()->GetGameInstance<UGameManager>();
	}
	if (!GM)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadStudentById: GameManager is NULL"));
		return false;
	}

	FStudentRowData Found;
	if (GM->FindStudentById(InId, Found))
	{
		CurrentStudent      = Found;
		bHasStudent         = true;
		CurrentSessionIndex = 1;  // 항상 1회기부터 시작

		RefreshHeaderUI();
		RefreshSessionUI();

		UE_LOG(LogTemp, Warning, TEXT("UStudentSessionDetailWidget - Loaded student %s (%s)"),
			*CurrentStudent.Name, *CurrentStudent.ID);

		return true;   // ✅ 찾았으니까 true
	}
	else
	{
		bHasStudent = false;
		UE_LOG(LogTemp, Warning, TEXT("UStudentSessionDetailWidget - Student ID not found: %s"), *InId);

		// 못 찾았으면 UI 비우기
		if (Txt_TitleNameAndId)
		{
			Txt_TitleNameAndId->SetText(FText::FromString(TEXT("검색 결과 없음")));
		}
		if (Edt_SessionNote)
		{
			Edt_SessionNote->SetText(FText::GetEmpty());
		}
		if (Edt_Manager)
		{
			Edt_Manager->SetText(FText::GetEmpty());
		}

		return false;  // ✅ 못 찾았으니 false
	}
}


// ---------------- 검색 이벤트 ----------------

void UStudentSessionDetailWidget::OnSearchButtonClicked()
{
	if (!SearchSwitcher)
	{
		return;
	}

	if (!Edt_SearchId)
	{
		SearchSwitcher->SetActiveWidgetIndex(0);  // 초기 화면
		return;		
	}

	const FString Id = Edt_SearchId->GetText().ToString().TrimStartAndEnd();

	// 입력 없음 → "검색어 입력해 주세요" 패널
	if (Id.IsEmpty())
	{
		SearchSwitcher->SetActiveWidgetIndex(1);
		return;
	}

	// 실제 검색
	const bool bFound = LoadStudentById(Id);

	if (bFound)
	{
		SearchSwitcher->SetActiveWidgetIndex(2);   // 학생 정보/회기표 패널
	}
	else
	{
		SearchSwitcher->SetActiveWidgetIndex(1);   // "결과 없음" 패널 (혹은 경고용)
	}
}


void UStudentSessionDetailWidget::OnSearchIdCommitted(
	const FText& Text, ETextCommit::Type CommitType)
{
	if (!SearchSwitcher)
	{
		return;
	}

	// 엔터 입력 시만 검색
	if (CommitType == ETextCommit::OnEnter)
	{
		const FString Id = Text.ToString().TrimStartAndEnd();

		if (Id.IsEmpty())
		{
			SearchSwitcher->SetActiveWidgetIndex(1);   // "ID를 입력하세요" 같은 패널
			return;
		}

		const bool bFound = LoadStudentById(Id);

		if (bFound)
		{
			SearchSwitcher->SetActiveWidgetIndex(2);    // 결과 패널
		}
		else
		{
			SearchSwitcher->SetActiveWidgetIndex(1);    // 결과 없음
		}
	}
}


// ---------------- 회기 탭 ----------------

void UStudentSessionDetailWidget::SetSessionIndex(int32 NewIndex)
{
	if (NewIndex < 1 || NewIndex > 5) return;
	CurrentSessionIndex = NewIndex;
	UpdateSessionButtonVisual();
	RefreshSessionUI();
}

void UStudentSessionDetailWidget::OnSession1Clicked() { SetSessionIndex(1); }
void UStudentSessionDetailWidget::OnSession2Clicked() { SetSessionIndex(2); }
void UStudentSessionDetailWidget::OnSession3Clicked() { SetSessionIndex(3); }
void UStudentSessionDetailWidget::OnSession4Clicked() { SetSessionIndex(4); }
void UStudentSessionDetailWidget::OnSession5Clicked() { SetSessionIndex(5); }

// ---------------- 수정 / 저장 ----------------

void UStudentSessionDetailWidget::OnEditOrSaveClicked()
{
	if (!bHasStudent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnEditOrSaveClicked: No student loaded."));
		return;
	}

	// 1) 현재 편집 모드가 아니면 -> 편집 모드 진입
	if (!bEditing)
	{
		bEditing = true;
		ApplyEditingMode();
		return;
	}

	if (Edt_Manager)
	{
		FString NewManager = Edt_Manager->GetText().ToString().TrimStartAndEnd();
		CurrentStudent.Manager = NewManager;
	}
	
	// 2) 편집 모드였다면 -> 저장 로직
	if (Edt_SessionNote)
	{
		FString NewNote = Edt_SessionNote->GetText().ToString();

		// 안전하게 5개가 있는지 체크
		if (CurrentStudent.SessionNotes.Num() < 5)
		{
			CurrentStudent.SessionNotes.SetNum(5);
			for (int32 i = 0; i < 5; ++i)
			{
				CurrentStudent.SessionNotes[i].SessionIndex = i + 1;
			}
		}

		const int32 ArrayIndex = CurrentSessionIndex - 1;
		CurrentStudent.SessionNotes[ArrayIndex].Note = NewNote;

		// GameManager 쪽에 저장 (UPSERT)
		if (GM)
		{
			GM->UpsertStudentRow(CurrentStudent);

			if (Edt_SessionNote)
			{
				const FString NoteForServer =
					Edt_SessionNote->GetText().ToString();
				GM->Send_SessionNoteUpdate(CurrentStudent.ID, CurrentSessionIndex, NoteForServer);

				FString Actor = CurrentStudent.Manager.IsEmpty()
					? TEXT("관리자")
					: CurrentStudent.Manager;

				FString Type = FString::Printf(TEXT("%d회기 기록 수정"), CurrentSessionIndex);
				GM->AddSimpleLog(Type, Actor);
			}
		}
	}

	// 저장 후 편집 모드 종료
	bEditing = false;
	ApplyEditingMode();
}

// ---------------- UI 갱신 ----------------

void UStudentSessionDetailWidget::RefreshHeaderUI()
{
	if (!bHasStudent) return;

	if (Txt_TitleNameAndId)
	{
		FString Title = FString::Printf(TEXT("%s (%s)"),
			*CurrentStudent.Name, *CurrentStudent.ID);
		Txt_TitleNameAndId->SetText(FText::FromString(Title));
	}

	if (Txt_Birth)      Txt_Birth->SetText(FText::FromString(CurrentStudent.Birth));
	if (Txt_CrimeType)  Txt_CrimeType->SetText(FText::FromString(CurrentStudent.CrimeType));
	if (Txt_EduCourse)  Txt_EduCourse->SetText(FText::FromString(CurrentStudent.EduCourse));
	if (Txt_VRType)     Txt_VRType->SetText(FText::FromString(CurrentStudent.VrType));
	if(Txt_VRSession)	Txt_VRSession->SetText(FText::FromString(CurrentStudent.VrSession));
	if (Txt_EduPeriod)  Txt_EduPeriod->SetText(FText::FromString(CurrentStudent.EduPeriod));

	if (Edt_Manager)
	{
		Edt_Manager->SetText(FText::FromString(CurrentStudent.Manager));
	}
}

void UStudentSessionDetailWidget::RefreshSessionUI()
{
	if (!bHasStudent)
	{
		if (Edt_SessionNote)  Edt_SessionNote->SetText(FText::GetEmpty());
		
		return;
	}
	

	// 배열 인덱스 안전 체크
	if (CurrentStudent.SessionNotes.Num() >= CurrentSessionIndex)
	{
		const int32 ArrayIndex = CurrentSessionIndex - 1;
		const FSessionNoteRow& NoteRow = CurrentStudent.SessionNotes[ArrayIndex];

		if (Edt_SessionNote)
		{
			Edt_SessionNote->SetText(FText::FromString(NoteRow.Note));
		}
		
	}
	else
	{
		if (Edt_SessionNote)  Edt_SessionNote->SetText(FText::GetEmpty());
		
	}

	// 담당자도 동기화
	if (Edt_Manager)
	{
		Edt_Manager->SetText(FText::FromString(CurrentStudent.Manager));
	}
}

void UStudentSessionDetailWidget::ApplyEditingMode()
{
	// 회기 메모는 수정 모드에서만 편집 가능
	if (Edt_SessionNote)
	{
		Edt_SessionNote->SetIsReadOnly(!bEditing);
	}

	// 담당자도 같이 수정하고 싶으면 여기서 IsReadOnly 토글
	if (Edt_Manager)
	{
		Edt_Manager->SetIsReadOnly(!bEditing);
	}

	// 버튼 텍스트 변경 (Blueprint에서 바인딩해도 됨)
	if (Btn_EditOrSave)
	{
		if (UTextBlock* Txt = Cast<UTextBlock>(Btn_EditOrSave->GetChildAt(0)))
		{
			Txt->SetText(bEditing
				? FText::FromString(TEXT("저장하기"))
				: FText::FromString(TEXT("수정하기")));
		}
	}
}

void UStudentSessionDetailWidget::UpdateSessionButtonVisual()
{
	for (int32 i = 0; i < SessionButtons.Num(); ++i)
	{
		UButton* Btn = SessionButtons[i];
		if (!Btn) continue;

		const bool bSelected = (i == CurrentSessionIndex - 1);

		//  색만 변경
		if (bSelected)
		{
			Btn->SetBackgroundColor(SessionSelectedColor);
		}
		else
		{
			Btn->SetBackgroundColor(SessionNormalColor);
		}
	}
}