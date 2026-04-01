// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor/SurveyQuestionRowWidget.h"

void USurveyQuestionRowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Check_1->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On1);
    Check_2->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On2);
    Check_3->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On3);
    Check_4->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On4);
    Check_5->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On5);
    if (Check_6) Check_6->OnCheckStateChanged.AddDynamic(this, &USurveyQuestionRowWidget::On6);


    SetMaxChoice(5);
}

void USurveyQuestionRowWidget::SetMaxChoice(int32 InMaxChoice)
{
    MaxChoice = (InMaxChoice >= 6) ? 6 : 5;

    // 6번 체크박스 표시/숨김
    if (Check_6)
    {
        Check_6->SetVisibility(MaxChoice == 6 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

        // 5점 모드에서 이미 6이 선택돼있으면 해제
        if (MaxChoice == 5 && SelectedIndex == 6)
        {
            bSyncing = true;
            Check_6->SetIsChecked(false);
            bSyncing = false;
            SelectedIndex = 0;
        }
    }
}


void USurveyQuestionRowWidget::On1(bool b){ HandleCheck(b, 1); }
void USurveyQuestionRowWidget::On2(bool b){ HandleCheck(b, 2); }
void USurveyQuestionRowWidget::On3(bool b){ HandleCheck(b, 3); }
void USurveyQuestionRowWidget::On4(bool b){ HandleCheck(b, 4); }
void USurveyQuestionRowWidget::On5(bool b){ HandleCheck(b, 5); }
void USurveyQuestionRowWidget::On6(bool b) { HandleCheck(b, 6); }


void USurveyQuestionRowWidget::HandleCheck(bool bIsChecked, int32 Index)
{
    if (bSyncing) return;

    if (Index == 6 && MaxChoice == 5)
    {
        if (Check_6)
        {
            bSyncing = true;
            Check_6->SetIsChecked(false);
            bSyncing = false;
        }
        return;
    }

    
    // 해제 방지 → 항상 하나만 유지
    if (!bIsChecked)
    {
        if (SelectedIndex == Index)
        {
            bSyncing = true;
            SetOnly(Index);
            bSyncing = false;
        }
        return;
    }

    bSyncing = true;
    SetOnly(Index);
    bSyncing = false;

    SelectedIndex = Index;
}

void USurveyQuestionRowWidget::SetOnly(int32 Index)
{
    bSyncing = true;

    SelectedIndex = Index;

    if (Check_1) Check_1->SetIsChecked(Index == 1);
    if (Check_2) Check_2->SetIsChecked(Index == 2);
    if (Check_3) Check_3->SetIsChecked(Index == 3);
    if (Check_4) Check_4->SetIsChecked(Index == 4);
    if (Check_5) Check_5->SetIsChecked(Index == 5);

    if (Check_6)
    {
        // 5점 모드면 6은 항상 false 유지
        Check_6->SetIsChecked(MaxChoice == 6 && Index == 6);
    }

    bSyncing = false;
}

int32 USurveyQuestionRowWidget::GetScore() const
{
    return SelectedIndex; // 1~5, 선택 안 됐으면 0
}

int32 USurveyQuestionRowWidget::GetReverseScore() const
{
    if (SelectedIndex <= 0)
        return 0; // 미선택

    // 5점 척도
    if (MaxChoice == 5)
    {
        return 6 - SelectedIndex;
    }

    // 6점 척도
    if (MaxChoice == 6)
    {
        return 7 - SelectedIndex;
    }

    return 0;
}