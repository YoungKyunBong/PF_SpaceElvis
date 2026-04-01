// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"// FStudentRowData 사용
#include "StudentDataSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStudentDataChanged);

/**
 * 교육생 Row 데이터를 전역으로 관리하는 싱글톤(SubSystem)
 * - 서버에서 받아온 전체 리스트 보관
 * - 위젯/액터 어디서든 접근 가능
 */
UCLASS()
class MOJCMSCLIENT_API UStudentDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** 현재 전체 학생 리스트 가져오기 */
	UFUNCTION(BlueprintCallable, Category="StudentData")
	const TArray<FStudentRowData>& GetAllStudents() const { return Students; }

	/** 서버에서 데이터를 받았을 때 전체 교체 */
	UFUNCTION(BlueprintCallable, Category="StudentData")
	void SetAllStudents(const TArray<FStudentRowData>& InRows);

	/** 한 명 추가 or 수정 (ID 기준 업서트) */
	UFUNCTION(BlueprintCallable, Category="StudentData")
	void UpsertStudent(const FStudentRowData& NewRow);

	/** ID로 학생 찾기 */
	UFUNCTION(BlueprintCallable, Category="StudentData")
	bool FindByID(const FString& InID, FStudentRowData& OutRow) const;

	/** 데이터 변경 알림 (UI가 바인딩해서 자동 리프레시 가능) */
	UPROPERTY(BlueprintAssignable, Category="StudentData")
	FOnStudentDataChanged OnStudentDataChanged;

private:
	/** 서버에서 받은 학생 데이터 전부 */
	UPROPERTY()
	TArray<FStudentRowData> Students;
};

