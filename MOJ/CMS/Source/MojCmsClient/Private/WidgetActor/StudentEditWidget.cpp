// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetActor/StudentEditWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Styling/SlateColor.h"
#include "Manager/GameManager.h"

void UStudentEditWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
	if (Btn_Register)
	{
		Btn_Register->OnClicked.AddDynamic(this, &UStudentEditWidget::OnRegisterClicked);
	}

	if (Btn_Update)
	{
		Btn_Update->OnClicked.AddDynamic(this, &UStudentEditWidget::OnUpdateClicked);
	}

	if (Btn_Delete)
	{
		Btn_Delete->OnClicked.AddDynamic(this, &UStudentEditWidget::OnDeleteClicked);
	}

	// 콤보박스 기본 옵션 (필요하면 여기서 세팅)
	if (Cmb_Fin && Cmb_Fin->GetOptionCount() == 0)
	{
		Cmb_Fin->AddOption(TEXT("진행"));
		Cmb_Fin->AddOption(TEXT("종료"));
		Cmb_Fin->AddOption(TEXT("취소"));
		Cmb_Fin->SetSelectedIndex(0);
	}

	// 필요하면 범죄유형 / 교육과정 등도 여기서 AddOption 해주기
	 if (Cmb_CrimeType && Cmb_CrimeType->GetOptionCount() == 0)
	 {
		 Cmb_CrimeType->AddOption(TEXT("성폭력"));
	 	Cmb_CrimeType->AddOption(TEXT("가정폭력"));
	 	Cmb_CrimeType->AddOption(TEXT("아동학대"));
	 	Cmb_CrimeType->AddOption(TEXT("스토킹"));
	 	Cmb_CrimeType->AddOption(TEXT("마약"));
	 	Cmb_CrimeType->SetSelectedIndex(0);
	 }
	 if (Cmb_EduCourse && Cmb_EduCourse->GetOptionCount() == 0)
	 {
	 	Cmb_EduCourse->AddOption(TEXT("기본"));
	 	Cmb_EduCourse->AddOption(TEXT("집중"));
	 	Cmb_EduCourse->AddOption(TEXT("심화"));
	 	Cmb_EduCourse->AddOption(TEXT("특별"));
	 	Cmb_EduCourse->AddOption(TEXT("유지"));
	 	Cmb_EduCourse->AddOption(TEXT("회복이음"));
	 	Cmb_EduCourse->AddOption(TEXT("전문"));
	 	Cmb_EduCourse->SetSelectedIndex(0);
	 }
	if (Cmb_VrType && Cmb_VrType->GetOptionCount() == 0)
	{
		Cmb_VrType->AddOption(TEXT("A"));
		Cmb_VrType->AddOption(TEXT("B"));
		Cmb_VrType->AddOption(TEXT("C"));
		Cmb_VrType->AddOption(TEXT("D"));
		Cmb_VrType->AddOption(TEXT("E"));
		Cmb_VrType->AddOption(TEXT("F"));
		Cmb_VrType->SetSelectedIndex(0);
	}

	// 기본은 신규 등록 모드
	SetNewMode();
}

void UStudentEditWidget::SetNewMode()
{
	CurrentMode = EStudentEditMode::New;
	EditingData = FStudentRowData(); // 초기화

	// 입력값 초기화
	if (Edt_Name)       Edt_Name->SetText(FText::GetEmpty());
	if (Edt_ID)         Edt_ID->SetText(FText::GetEmpty());
	if (Edt_Birth)      Edt_Birth->SetText(FText::GetEmpty());
	if (Edt_EduPeriod)  Edt_EduPeriod->SetText(FText::GetEmpty());
	if (Edt_Manager)    Edt_Manager->SetText(FText::GetEmpty());

	if (Cmb_Fin)        Cmb_Fin->ClearSelection();
	if (Cmb_CrimeType)  Cmb_CrimeType->ClearSelection();
	if (Cmb_EduCourse)  Cmb_EduCourse->ClearSelection();
	if (Cmb_VrType)     Cmb_VrType->ClearSelection();

	// 신규 등록에서는 ID 수정 가능하게
	if (Edt_ID)
	{
		Edt_ID->SetIsReadOnly(false);
	}

	ApplyEditPermissions();
	RefreshButtonVisibility();

	OnEditModeChanged.Broadcast(CurrentMode, MakeHeaderText());
}

void UStudentEditWidget::SetEditMode(const FStudentRowData& InData)
{
	CurrentMode = EStudentEditMode::Edit;
	EditingData = InData;

	Edt_Name->SetText(FText::FromString(InData.Name));
	Edt_ID->SetText(FText::FromString(InData.ID));
	Edt_Birth->SetText(FText::FromString(InData.Birth));

	Cmb_Fin->SetSelectedOption(InData.Fin);
	Cmb_CrimeType->SetSelectedOption(InData.CrimeType);
	Cmb_EduCourse->SetSelectedOption(InData.EduCourse);
	Edt_EduPeriod->SetText(FText::FromString(InData.EduPeriod));
	Cmb_VrType->SetSelectedOption(InData.VrType);
	Edt_Manager->SetText(FText::FromString(InData.Manager));

	Edt_Name->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;
	Edt_ID->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;
	Edt_Birth->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;
	Edt_EduPeriod->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;
	Edt_Manager->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;

	Cmb_Fin->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::White;
	Cmb_CrimeType->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::White;
	Cmb_EduCourse->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::White;
	Cmb_VrType->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::White;

	ApplyEditPermissions();
	RefreshButtonVisibility();

	OnEditModeChanged.Broadcast(CurrentMode, MakeHeaderText());
}

void UStudentEditWidget::SetTextBoxCommitted(UEditableTextBox* TempEditTextBox)
{
	TempEditTextBox->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::White;
}

void UStudentEditWidget::SetComboBoxCommitted(UComboBoxString* TempComboBox)
{
	TempComboBox->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::White;
}

void UStudentEditWidget::RefreshButtonVisibility()
{
	if (CurrentMode == EStudentEditMode::New)
	{
		if (Btn_Register) Btn_Register->SetVisibility(ESlateVisibility::Visible);
		if (Btn_Update)   Btn_Update->SetVisibility(ESlateVisibility::Collapsed);
		//if (Btn_Delete)   Btn_Delete->SetVisibility(ESlateVisibility::Collapsed);
	}
	else // Edit
	{
		if (Btn_Register) Btn_Register->SetVisibility(ESlateVisibility::Collapsed);
		if (Btn_Update)   Btn_Update->SetVisibility(ESlateVisibility::Visible);
		//if (Btn_Delete)   Btn_Delete->SetVisibility(ESlateVisibility::Visible);
	}
}

FStudentRowData UStudentEditWidget::CollectDataFromUI() const
{
	FStudentRowData Data;

	if (Edt_Name)       Data.Name       = Edt_Name->GetText().ToString().Replace(TEXT(" "), TEXT(""));
	if (Edt_ID)         Data.ID         = Edt_ID->GetText().ToString().Replace(TEXT(" "), TEXT(""));
	if (Edt_Birth)      Data.Birth      = Edt_Birth->GetText().ToString().Replace(TEXT(" "), TEXT(""));
	if (Edt_EduPeriod)  Data.EduPeriod  = Edt_EduPeriod->GetText().ToString().Replace(TEXT(" "), TEXT(""));
	if (Edt_Manager)    Data.Manager    = Edt_Manager->GetText().ToString().Replace(TEXT(" "), TEXT(""));

	if (Cmb_Fin)        Data.Fin        = Cmb_Fin->GetSelectedOption();
	if (Cmb_CrimeType)  Data.CrimeType  = Cmb_CrimeType->GetSelectedOption();
	if (Cmb_EduCourse)  Data.EduCourse  = Cmb_EduCourse->GetSelectedOption();
	if (Cmb_VrType)     Data.VrType     = Cmb_VrType->GetSelectedOption();

	// 시작일/종료일/등록일/수정일은 지금 UI에 필드가 없으면 빈 값 or 나중에 서버에서 세팅
	// Data.Start       = ...;
	// Data.End         = ...;
	// Data.RegisterDate= ...;
	// Data.UpdateDate  = ...;

	return Data;
}

void UStudentEditWidget::OnRegisterClicked()
{
	// 서버 쪽으로 데이터 전송해야함
	
	FStudentRowData NewData = CollectDataFromUI();

	if (NewData.Name.IsEmpty() || NewData.ID.IsEmpty() || NewData.Birth.IsEmpty() || NewData.EduPeriod.IsEmpty() || NewData.Manager.IsEmpty()
		|| NewData.Fin.IsEmpty() || NewData.CrimeType.IsEmpty() || NewData.EduCourse.IsEmpty() || NewData.VrType.IsEmpty())
	{
		if(NewData.Name.IsEmpty()) Edt_Name->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::Red;
		if(NewData.ID.IsEmpty()) Edt_ID->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::Red;
		if(NewData.Birth.IsEmpty()) Edt_Birth->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::Red;
		if(NewData.EduPeriod.IsEmpty()) Edt_EduPeriod->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::Red;
		if(NewData.Manager.IsEmpty()) Edt_Manager->WidgetStyle.BackgroundImageNormal.TintColor = FLinearColor::Red;

		if (NewData.Fin.IsEmpty()) Cmb_Fin->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::Red;
		if (NewData.CrimeType.IsEmpty()) Cmb_CrimeType->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::Red;
		if (NewData.EduCourse.IsEmpty()) Cmb_EduCourse->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::Red;
		if (NewData.VrType.IsEmpty()) Cmb_VrType->WidgetStyle.ComboButtonStyle.ButtonStyle.Normal.TintColor = FLinearColor::Red;

		UE_LOG(LogTemp, Warning, TEXT("OnRegisterClicked: ID is empty, ignore"));
		return;
	}
	// 나머지 필드들 기본값 세팅
	// 평균 집중도 / 만족도
	NewData.AVConcentration = TEXT("0.0%");
	NewData.Satisfaction    = 0;      // 필요하면 3 같은 기본값으로 바꿔도 됨

	// 사전 / 사후 검사 점수
	NewData.Pre1  = 0;
	NewData.Pre2  = 0;
	NewData.Pre3  = 0;
	NewData.Pre4  = 0;

	NewData.Post1 = 0;
	NewData.Post2 = 0;
	NewData.Post3 = 0;
	NewData.Post4 = 0;

	NewData.VrSession=TEXT("1");
	NewData.Consent_Test="-";
	NewData.Pre_Test="-";
	NewData.Post_Test="-";
	
	// 회기별 메모 (1~5회기 고정)
	NewData.SessionNotes.Empty();
	for (int32 i = 0; i < 5; ++i)
	{
		FSessionNoteRow NoteRow;
		NoteRow.SessionIndex = i + 1;     // 1,2,3,4,5
		NoteRow.Score        = TEXT("0%"); // 집중도 기본값
		NoteRow.Note         = TEXT("-");   // 특이사항 없음

		NewData.SessionNotes.Add(NoteRow);
	}

	//  오늘 날짜 YY-MM-DD 형식 생성
	FDateTime Now = FDateTime::Now();
	FString Year2 = FString::Printf(TEXT("%02d"), Now.GetYear() % 100);
	FString Month = FString::Printf(TEXT("%02d"), Now.GetMonth());
	FString Day   = FString::Printf(TEXT("%02d"), Now.GetDay());
	NewData.RegisterDate = FString::Printf(TEXT("%s-%s-%s"), *Year2, *Month, *Day);
	
	NewData.UpdateDate = NewData.RegisterDate;

	// GameManager에 저장
	if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	{
		//GM->UpsertStudentRow(NewData);

		//서버전송
		if (GM->AddStudentRow(NewData))
		{
			OnSubmitNew.Broadcast(NewData, 0);

			GM->Send_StudentRegister(NewData);

			GM->AddSimpleLog(TEXT("교육생 신규 등록"), NewData.Manager);
		}
	}

	SetNewMode();
}


void UStudentEditWidget::OnUpdateClicked()
{
	if (CurrentMode != EStudentEditMode::Edit)
		return;

	// 1) UI에서 수정된 데이터 가져오기
	FStudentRowData NewData = CollectDataFromUI();

	// 2) 기존 데이터에서 유지해야 하는 필드 복원
	NewData.ID            = EditingData.ID;
	NewData.Start         = EditingData.Start;
	NewData.End           = EditingData.End;
	NewData.RegisterDate  = EditingData.RegisterDate; // 유지됨

	//  집중도 / 만족도 / 사전·사후 검사 점수 / 회기메모 유지
	NewData.AVConcentration = EditingData.AVConcentration;
	NewData.Satisfaction    = EditingData.Satisfaction;

	NewData.Pre1 = EditingData.Pre1;
	NewData.Pre2 = EditingData.Pre2;
	NewData.Pre3 = EditingData.Pre3;
	NewData.Pre4 = EditingData.Pre4;

	NewData.Post1 = EditingData.Post1;
	NewData.Post2 = EditingData.Post2;
	NewData.Post3 = EditingData.Post3;
	NewData.Post4 = EditingData.Post4;

	NewData.Consent_Test=EditingData.Consent_Test;
	NewData.Pre_Test=EditingData.Pre_Test;
	NewData.Post_Test=EditingData.Post_Test;

	NewData.SessionNotes = EditingData.SessionNotes;    // 회기별 메모도 그대로 가져옴

	// 3) 수정일 갱신 (YY-MM-DD)
	FDateTime Now = FDateTime::Now();
	FString Year2 = FString::Printf(TEXT("%02d"), Now.GetYear() % 100);
	FString Month = FString::Printf(TEXT("%02d"), Now.GetMonth());
	FString Day   = FString::Printf(TEXT("%02d"), Now.GetDay());
	NewData.UpdateDate = FString::Printf(TEXT("%s-%s-%s"), *Year2, *Month, *Day);

	// 4) 외부에 이벤트 전달 (필요 시)

	// 5) GameManager에 반영 (UPSERT)
	if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	{
		int updateIndex = GM->UpsertStudentRow(NewData);
		if (updateIndex != INDEX_NONE)
		{
			OnSubmitEdit.Broadcast(NewData, updateIndex);

			GM->Send_StudentUpdate(NewData, updateIndex);

			GM->AddSimpleLog(TEXT("교육생 정보 수정"), NewData.Manager);
		}
	}

	// 6) 수정 후 다시 신규 등록 모드로 복귀
	SetNewMode();
}


void UStudentEditWidget::OnDeleteClicked()
{
	if (CurrentMode != EStudentEditMode::Edit)
		return;
	
	const FString TargetID = EditingData.ID;

	if (TargetID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnDeleteClicked: TargetID is empty, ignore"));
		return;
	}

	if (UGameManager* GM = GetWorld()->GetGameInstance<UGameManager>())
	{
		//  로컬 데이터 삭제
		GM->RemoveStudentRowByID(TargetID);

		// 서버 전송
		GM->Send_StudentDelete(TargetID);

		//로그
		const FString Actor = EditingData.Manager.IsEmpty()
			? TEXT("관리자")
			: EditingData.Manager;

		GM->AddSimpleLog(TEXT("교육생 삭제"), Actor);
	}

	// UI 초기화
	SetNewMode();
}


void UStudentEditWidget::ApplyEditPermissions()
{
	const bool bIsEdit = (CurrentMode == EStudentEditMode::Edit);

	
	if (Edt_Name)   Edt_Name->SetIsReadOnly(false);
	if (Edt_Birth)  Edt_Birth->SetIsReadOnly(false);
	if (Edt_Manager)Edt_Manager->SetIsReadOnly(false);
	if (Cmb_Fin)    Cmb_Fin->SetIsEnabled(true);

	if (bIsEdit)
	{
		
		if (Edt_ID)        Edt_ID->SetIsReadOnly(true);
		if (Cmb_CrimeType) Cmb_CrimeType->SetIsEnabled(false);
		if (Cmb_EduCourse) Cmb_EduCourse->SetIsEnabled(false);
		if (Edt_EduPeriod) Edt_EduPeriod->SetIsReadOnly(true);
		if (Cmb_VrType)    Cmb_VrType->SetIsEnabled(false);
	}
	else
	{
		if (Edt_ID)        Edt_ID->SetIsReadOnly(false);
		if (Cmb_CrimeType) Cmb_CrimeType->SetIsEnabled(true);
		if (Cmb_EduCourse) Cmb_EduCourse->SetIsEnabled(true);
		if (Edt_EduPeriod) Edt_EduPeriod->SetIsReadOnly(false);
		if (Cmb_VrType)    Cmb_VrType->SetIsEnabled(true);
	}
}


FText UStudentEditWidget::MakeHeaderText() const
{
	if (CurrentMode == EStudentEditMode::New)
	{
		return FText::FromString(TEXT("교육생 신규 등록"));
	}
	else
	{
		return FText::FromString(TEXT("교육생 수정"));
	}
}

