// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "Engine/GameInstance.h"
#include "WidgetActor/StudentRowWidget.h" 
#include "WidgetActor/StudentSessionMonitorWidget.h"
#include "GameManager.generated.h"

#define SERVERIP "192.168.1.5"

#pragma region LoginSettingBindingDatas
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecvLoginChangePW, bool, isCheck);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecvLoginCheckPW, bool, isCheck);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvInmateLogin, bool);
#pragma endregion

#pragma region InmateSettingBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvInmateADD, SEND_TEXT_TYPE);
DECLARE_MULTICAST_DELEGATE_TwoParams(FRecvInmateUpdate, SEND_TEXT_TYPE, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvInmateSearch, FString);
#pragma endregion

#pragma region CmsBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvTrackingNum, int);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecvTrackingNumBP, int32,Num);
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerNextRound);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecvStop, bool, isCheck);
#pragma endregion

#pragma region UdpBindingDatas
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvHeartRate, FString);
#pragma endregion


#pragma region StudentDataDelegates
DECLARE_MULTICAST_DELEGATE(FOnStudentRowsUpdated);
#pragma endregion

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnServerHeartRateMarkReceived,
	const FString&, InmateId,
	int32, SessionIndex,
	int32, ServerMark
);
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLogItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;        // "신규 등록", "로그인", "세션 종료"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Time;        // "2024-11-10 12:50"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Actor;       // "관리자A", "시스템"
};
#pragma region LogSendDelegates
DECLARE_MULTICAST_DELEGATE(FOnLogUpdated);
#pragma endregion


UCLASS()
class MOJCMSCLIENT_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
private:
	FString ServerIP;
	FString TempWatchIP;

	TArray<TArray<FString>> Values;

	PROTOCOLSUB_DEVICE_TYPE DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::CmsClinetA;

	void FileLoadIP();

protected:
	virtual void Init() override;
	virtual void Shutdown();

protected:
	UPROPERTY(BlueprintReadWrite)
	class AHrUDPManager* udpManager;

protected:
	UFUNCTION(BlueprintCallable)
	void UdpBinding();

public:
	void Send_DeviceType();

#pragma region DefaultSettingBindingDatas

	UFUNCTION()
	void Fuc_RecvDefaultSearch(FString data);

	UFUNCTION()
	void Fuc_RecvDefaultDataSetting();

	void Send_DefaultSearch();

	void Send_DefaultDataSetting();
#pragma endregion

#pragma region LoginSettingBindingDatas

	UPROPERTY(BlueprintAssignable)
	FRecvLoginChangePW RecvLoginChangePW;
	UPROPERTY(BlueprintAssignable)
	FRecvLoginCheckPW RecvLoginCheckPW;
	FRecvInmateLogin RecvInmateLogin;

	UFUNCTION()
	void Fuc_RecvLoginChangePW(bool isSuccess);
	UFUNCTION()
	void Fuc_RecvLoginCheckPW(bool isSuccess);
	UFUNCTION()
	void Fuc_RecvInmateLogin(bool isSuccess);

	UFUNCTION(BlueprintCallable)
	void Send_LoginCheckPW(FString pinNum);
	UFUNCTION(BlueprintCallable)
	void Send_ChangePW(FString currPW, FString newPW);
	UFUNCTION(BlueprintCallable)
	void Send_InmateLogin(FString inmateNum);

#pragma endregion

#pragma region InmateSettingBindingDatas

	FRecvInmateADD RecvInmateADD;
	FRecvInmateUpdate RecvInmateUpdate;
	FRecvInmateSearch RecvInmateSearch;

	UFUNCTION()
	void Fuc_RecvInmateADD(SEND_TEXT_TYPE printType);
	UFUNCTION()
	void Fuc_RecvInmateUpdate(SEND_TEXT_TYPE type, FString data);
	UFUNCTION()
	void Fuc_RecvInmateSearch(FString data);

	void Send_InmateADD(const FString& data);
	void Send_InmateSearch();
	void Send_InmateUpdate(const FString& data);

#pragma endregion

#pragma region ProgramSettingBindingDatas
	
	UFUNCTION()
	void Fuc_RecvProgramUpdate(FString _data);

	void Send_ProgramUpdate(const FString& data);
	void Send_ProgramUpdate_RoundHeartRate_MovieNum(const FString& data);

#pragma endregion

#pragma region LogSettingBindingDatas

	//void Send_LogSearch();

#pragma endregion

#pragma region CmsBindingDatas

	FRecvTrackingNum RecvTrackingNum;

	UPROPERTY(BlueprintAssignable)
	FRecvTrackingNumBP RecvTrackinNumBP;

	
	FRecvCmsControllerNextRound RecvCmsControllerNextRound;

	//UFUNCTION()
	//void Fuc_RecvCmsControllerStart();
	//UFUNCTION()
	//void Fuc_RecvCmsControllerPlay();
	UFUNCTION()
	void Fuc_RecvTrackingNum(int num);
	UFUNCTION()
	void Fuc_RecvCmsControllerNextRound();

	void Send_CmsControllerStart();
	void Send_CmsControllerPlay();
	void Send_CmsControllerStop();

#pragma endregion

#pragma region UdpBindingDatas
	FRecvHeartRate RecvHeartRate;

	UFUNCTION()
	void Fuc_RecvHeartRate(int32 bpm, int64 timeStamp);
#pragma endregion

#pragma region StudentData

	// 서버에서 받은 학생 전체 데이터
	UPROPERTY()
	TArray<FStudentRowData> StudentRows;

	// UI에서 구독할 수 있는 델리게이트
	FOnStudentRowsUpdated OnStudentRowsUpdated;

	// 외부(UI)에서 사용 가능하도록 Getter 제공
	UFUNCTION(BlueprintCallable)
	const TArray<FStudentRowData>& GetStudentRows() const { return StudentRows; }

	// 한 명을 ID로 찾기 (없으면 false)
	UFUNCTION(BlueprintCallable)
	bool FindStudentById(const FString& Id, FStudentRowData& OutData) const;
	
	// 전체 데이터 교체 (서버 목록 받을 때)
	void SetStudentRows(const TArray<FStudentRowData>& InRows);

	bool AddStudentRow(const FStudentRowData& Row);

	// 추가 또는 수정 (ID 기준 UPSERT)
	int UpsertStudentRow(const FStudentRowData& Row);

	// 지금은 더미 데이터 생성
	UFUNCTION(BlueprintCallable)
	void CreateDummyStudentData();

	// 회기별 기록(특이사항) 서버 전송용 껍데기
	void Send_SessionNoteUpdate(
		const FString& InmateId,
		int32 SessionIndex,
		const FString& NoteText
	);
	
	// 회기 심박 스케줄 로그 전송
	void Send_SessionHeartRateSchedule(
		const FString& InmateId,
		int32 SessionIndex,
		const TArray<FHeartRateLog>& Logs
	);

	
	void Send_SessionHeartRateLogOnce(
		const FString& InmateId,
		int32 SessionIndex,
		int32 Bpm,
		int32 ServerMark
	);


#pragma endregion

#pragma region StudentNetworkSend

	FString SerializeStudentRow(const uint8& main, const uint8& sub, const FStudentRowData& R);

	// 교육생 신규 등록 / 수정 서버 전송용
	void Send_StudentRegister(const FStudentRowData& Data);
	void Send_StudentUpdate(const FStudentRowData& Data, int updateIndex);

#pragma endregion

#pragma region LogData
	UPROPERTY()
	TArray<FLogItem> LogItems;

	DECLARE_MULTICAST_DELEGATE(FOnLogUpdated);
	FOnLogUpdated OnLogUpdated;

	UFUNCTION(BlueprintCallable)
	const TArray<FLogItem>& GetLogItems() const { return LogItems; }

	void AddLog(const FLogItem& Item);
	void AddSimpleLog(const FString& Type, const FString& Actor = TEXT("시스템"));
	void CreateDummyLogs();

	
	void Send_LogSearch();
	UFUNCTION()
	void Fuc_RecvLogSearch(FString data);

	void Send_Log(const FLogItem& Item);
	void Request_LogList();

	// 서버에서 온 로그 문자열 처리
	UFUNCTION()
	void Fuc_RecvLogList(const FString& Data);

#pragma endregion

	
#pragma region HeartRateData
	
	DECLARE_MULTICAST_DELEGATE(FTutorialEnd);
	FTutorialEnd OnTutorialEnd;

	UFUNCTION()
	void Fuc_RecvTutorialEnd();

#pragma endregion
	
#pragma region HeartRateSchedule
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSessionHeartRateScheduleReceived, FString /*InmateId*/, int32 /*SessionIndex*/, TArray<FHeartRateLog> /*Logs*/);
	FOnSessionHeartRateScheduleReceived OnSessionHeartRateScheduleReceived;

	void Send_SessionHeartRateScheduleRequest(const FString& InmateId, int32 SessionIndex);

	UFUNCTION()
	void Fuc_RecvSessionHeartRateSchedule(FString data); // 서버에서 온 문자열
#pragma endregion


private:
	void ParseDefaultSearchData(const FString& data, TArray<FStudentRowData>& OutRows);



#pragma region ContentRun

public:
	// 콘텐츠 실행 시작 알림(서버 전송)
	UFUNCTION(BlueprintCallable)
	void Send_RunContentStart(const FStudentRowData& Student, int32 SessionIndex);

	UFUNCTION(BlueprintCallable, Category="Server|Session")
	void Send_SessionPause();

	UFUNCTION(BlueprintCallable, Category="Server|Session")
	void Send_SessionResume();

	UFUNCTION(BlueprintCallable, Category="Server|Session")
	void Send_SessionStop();

	void Send_SectionMove(int index);
	
#pragma endregion


	UFUNCTION(BlueprintCallable)
	void Send_ConsentAgreed(const FString& StudentId);

	UFUNCTION(BlueprintCallable, Category="Student")
	bool UpdateStudentConsentLocal(const FString& StudentId, const FString& ConsentText);


	UFUNCTION(BlueprintCallable, Category="Server")
	void Send_PreTestUpdate(const FString& InmateId, int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4);

	UFUNCTION(BlueprintCallable, Category="Server")
	void Send_PreTestDrugUpdate(const FString& InmateId, int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4, int32 Pre5, int32 Pre6, int32 Pre7, int32 Pre8);
	
	UFUNCTION(BlueprintCallable, Category="Server")
	void Send_PostTestUpdate(
		const FString& InmateId,
		int32 Post1, int32 Post2, int32 Post3, int32 Post4
	);

	UFUNCTION(BlueprintCallable, Category="Server")
	void Send_PostTestDrugUpdate(
		const FString& InmateId,
		int32 Post1, int32 Post2, int32 Post3, int32 Post4, int32 Post5, int32 Post6, int32 Post7, int32 Post8
	);

	UFUNCTION(BlueprintCallable, Category="Server")
	void Send_SatisfactionUpdate(
		const FString& InmateId, int32 InSatisfaction
	);

	
	UFUNCTION(BlueprintCallable, Category="Student")
	bool UpdateStudentPreTestLocal(
		const FString& StudentId,const FString& ConsentText,
		int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4
	);

	UFUNCTION(BlueprintCallable, Category="Student")
	bool UpdateStudentPreTestDrugLocal(
		const FString& StudentId,const FString& ConsentText,
		int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4
		,int32 Pre5, int32 Pre6, int32 Pre7, int32 Pre8
	);

	UFUNCTION(BlueprintCallable, Category="Student")
	bool UpdateStudentPostTestLocal(
		const FString& StudentId,const FString& ConsentText,
		int32 Post1, int32 Post2, int32 Post3, int32 Post4
	);

	UFUNCTION(BlueprintCallable, Category="Student")
	bool UpdateStudentPostTestDrugLocal(
		const FString& StudentId,const FString& PostText,
		int32 Post1, int32 Post2, int32 Post3, int32 Post4
		,int32 Post5, int32 Post6, int32 Post7, int32 Post8
	);

	UFUNCTION(BlueprintCallable, Category="Student")
	void UpdateStudentSatisfactionLocal(
		const FString& StudentId, int32 InSatisfaction
	);

	void AppendSessionHeartRateLocal(
	const FString& InmateId,
	int32 SessionIndex,
	const FHeartRateLog& Log
);


	UPROPERTY(BlueprintAssignable)
	FRecvStop RecvStopSignal;

	UPROPERTY(BlueprintAssignable)
	FRecvStop RecvStopContentSignal;

	UFUNCTION(BlueprintCallable)
	void RequestStopSession();


#pragma region SessionFlow

	DECLARE_MULTICAST_DELEGATE(FOnSessionCompleted);
	FOnSessionCompleted OnSessionCompleted;
	
	UFUNCTION()
	void Fuc_RecvSessionCompleted();
#pragma endregion


	
	UFUNCTION(BlueprintCallable)
	void RemoveStudentRowByID(const FString& InID);

	void Send_StudentDelete(const FString& InID);


	

	//컨텐츠 실행중 회기별 영상번호
	UPROPERTY(BlueprintAssignable)
	FOnServerHeartRateMarkReceived OnServerHeartRateMarkReceived;
	
	void Send_RequestMovieNum(const FString& InmateId, int32 SessionIndex);
	void Fuc_RecvHeartRateMark(TArray<FString> Data);
};


