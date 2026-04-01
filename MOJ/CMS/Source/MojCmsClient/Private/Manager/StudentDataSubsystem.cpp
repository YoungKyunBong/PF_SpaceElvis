// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/StudentDataSubsystem.h"

#include "WidgetActor/StudentRowWidget.h"

void UStudentDataSubsystem::SetAllStudents(const TArray<FStudentRowData>& InRows)
{
	Students = InRows;
	OnStudentDataChanged.Broadcast();
}

void UStudentDataSubsystem::UpsertStudent(const FStudentRowData& NewRow)
{
	// ID 기준으로 있으면 수정, 없으면 추가
	for (FStudentRowData& Row : Students)
	{
		if (Row.ID == NewRow.ID)
		{
			Row = NewRow;
			OnStudentDataChanged.Broadcast();
			return;
		}
	}

	Students.Add(NewRow);
	OnStudentDataChanged.Broadcast();
}

bool UStudentDataSubsystem::FindByID(const FString& InID, FStudentRowData& OutRow) const
{
	for (const FStudentRowData& Row : Students)
	{
		if (Row.ID == InID)
		{
			OutRow = Row;
			return true;
		}
	}
	return false;
}
