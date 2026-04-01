// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GameManager.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendThread.h"
#include "../../Public/Server/RecvThread.h"
#include "../../Public/Server/ProcessThread.h"
#include "../UDP/HrUDPManager.h"
#include "Misc/FileHelper.h"
#include "WidgetActor/StudentRowWidget.h"
#include "GenericPlatform/GenericPlatformHttp.h"

//깃 병합 테스트 주석 입력

void UGameManager::FileLoadIP()
{
	FString SaveDirectory = *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString FileName = FString("ServerIP") + FString(".txt");
	FString FolderName = FString("LoadFile");
	FString AbsoluteFilePath_2 = SaveDirectory + FolderName;

	TArray<FString> TempArrayName;
	TempArrayName.Empty();
	TArray<FString> TempTextName;
	TempTextName.Empty();

	FString AbsoluteFilePath = AbsoluteFilePath_2 + "/" + FileName;

	FString TempTypeName = "";

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsoluteFilePath))
	{
		FFileHelper::LoadFileToStringArray(TempArrayName, *AbsoluteFilePath);

		TempTextName = TArray<FString>(TempArrayName);

		if (TempArrayName.Num() != 0)
		{
			ServerIP = TempArrayName[0];
			TempTypeName = TempArrayName[1];

			if(TempTypeName == "CmsClientA")
				DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::CmsClinetA;
			else
				DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::CmsClinetB;

			TempWatchIP = TempArrayName[2];
		}
	}
}


void UGameManager::Init()
{
	Super::Init();

//#if PLATFORM_WINDOWS
	FileLoadIP();
//#else
	//ServerIP = SERVERIP;
//#endif

	SocketManager::GetInst()->Init(ServerIP);

	RecvThread::GetInst()->MakeThread();
	SendThread::GetInst()->MakeThread();
	ProcessThread::GetInst()->MakeThread();

#pragma region DefaultSettingBindingDatas

	ProcessThread::GetInst()->GetFDefaultSearch()->AddUFunction(this, FName("Fuc_RecvDefaultSearch"));
	ProcessThread::GetInst()->GetFDefaultSetting()->AddUFunction(this, FName("Fuc_RecvDefaultDataSetting"));

#pragma endregion

#pragma region LoginSettingBindingDatas

	ProcessThread::GetInst()->GetFManageChangePW()->AddUFunction(this, FName("Fuc_RecvLoginChangePW"));
	ProcessThread::GetInst()->GetFManageCheckPW()->AddUFunction(this, FName("Fuc_RecvLoginCheckPW"));
	ProcessThread::GetInst()->GetFInmateLogin()->AddUFunction(this, FName("Fuc_RecvInmateLogin"));

#pragma endregion

#pragma region InmateSettingBindingDatas

	ProcessThread::GetInst()->GetFInmateADD()->AddUFunction(this, FName("Fuc_RecvInmateADD"));
	ProcessThread::GetInst()->GetFInmateUpdate()->AddUFunction(this, FName("Fuc_RecvInmateUpdate"));
	ProcessThread::GetInst()->GetFInmateSearch()->AddUFunction(this, FName("Fuc_RecvInmateSearch"));

#pragma endregion

#pragma region ProgramSettingBindingDatas

	ProcessThread::GetInst()->GetFProgramUpdate()->AddUFunction(this, FName("Fuc_RecvProgramUpdate"));

#pragma endregion

#pragma region CmsBindingDatas
	ProcessThread::GetInst()->GetFTrackingNumber()->AddUFunction(this, FName("Fuc_RecvTrackingNum"));
	ProcessThread::GetInst()->GetFCmsNextRound()->AddUFunction(this, FName("Fuc_RecvCmsControllerNextRound"));
	ProcessThread::GetInst()->GetFTutoEnd()->AddUFunction(this, FName("Fuc_RecvTutorialEnd"));
	ProcessThread::GetInst()->GetFRoundEnd()->AddUFunction(this, FName("Fuc_RecvSessionCompleted"));
#pragma endregion

	ProcessThread::GetInst()->GetFLogSearch()->AddUFunction(this, FName("Fuc_RecvLogSearch"));

	//TODO
	//ProcessThread::GetInst()->GetFHeartRateMark()->AddUFunction(this, FName("Fuc_RecvHeartRateMark"));
	
	
	// GameManager::Init() 안에 델리게이트 바인딩 추가 (DefaultSearch처럼)
	//ProcessThread::GetInst()->GetFSessionHeartRateSchedule()->AddUFunction(this, FName("Fuc_RecvSessionHeartRateSchedule"));


	
	Send_DeviceType();

	//FPlatformProcess::Sleep(1.0f);

	Send_DefaultSearch();

	//FPlatformProcess::Sleep(1.0f);

	AddSimpleLog(TEXT("로그인"), DEVICE_TYPE == PROTOCOLSUB_DEVICE_TYPE::CmsClinetA ? TEXT("관리자A") : TEXT("관리자B"));

	FPlatformProcess::Sleep(1.0f);

	Send_LogSearch();

	//TArray<FHeartRateLog> tempLogs;

	//for (int i = 0; i < 5; i++)
	//{
	//	FHeartRateLog tempLog;

	//	tempLog.Bpm += i * 10;
	//	tempLog.TimestampMs += i * 20;

	//	tempLogs.Add(tempLog);
	//}

	//Send_SessionHeartRateSchedule("2222", 1, tempLogs);
}

void UGameManager::UdpBinding()
{
#pragma region UdpBindingDatas
	udpManager->OnHeartRateReceived.AddUniqueDynamic(this, &UGameManager::Fuc_RecvHeartRate);

	udpManager->WatchIP = TempWatchIP;
#pragma endregion
}

void UGameManager::Shutdown()
{
	Super::Shutdown();

	//FPlatformProcess::Sleep(0.05f);

	//Send_SetSceneType(true);

	SocketManager::GetInst()->QuitConnection();

	if (SendThread::GetInst() != nullptr)
	{
		SendThread::GetInst()->StopListen(false);
	}

	if (RecvThread::GetInst() != nullptr)
	{
		RecvThread::GetInst()->StopListen(false);
	}

	if (ProcessThread::GetInst() != nullptr)
	{
		ProcessThread::GetInst()->StopListen(false);
	}

}

void UGameManager::Send_DeviceType()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::ConnectClientSetting),
	                                  static_cast<uint8>(DEVICE_TYPE));
}

#pragma region DefaultSettingBindingDatas

void UGameManager::Fuc_RecvDefaultSearch(FString data)
{
	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch"));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" Fuc_RecvDefaultSearch")); // 화면출력

	//FString decodeData = FGenericPlatformHttp::UrlDecode(data);

	TArray<FString> Columns;
	data.ParseIntoArray(Columns, TEXT("$"));

	TArray<TArray<FString>> tempValues;
	for (int i = 0; i < Columns.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FGenericPlatformHttp::UrlDecode(Columns[i]));
		TArray<FString> temp;
		Columns[i].ParseIntoArray(temp, TEXT("#"));
		for (int j = 0; j < temp.Num(); j++)
		{
			temp[j] = FGenericPlatformHttp::UrlDecode(temp[j]);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *temp[j]);
		}
		Values.Add(temp);
	}

	//Values = tempValues;

	StudentRows.Empty();
	TArray<FStudentRowData> ParsedRows;

	//UE_LOG(LogTemp, Warning, TEXT("MakeData"));

	//UE_LOG(LogTemp, Warning, TEXT("Total Value Size %d"), Values.Num());

	for (int i = 0; i < Values.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Each Value Array Size %d"), Values[i].Num());

		const int32 FieldCount = Values[i].Num();

		//UE_LOG(LogTemp, Warning, TEXT("TestLog2"));

		if (FieldCount < 25)
		{
			// 어떤 row가 깨졌는지 원문을 남겨야 원인이 잡힘
			UE_LOG(LogTemp, Error, TEXT("Row %d invalid. FieldCount=%d. RowRaw=[%s]"),
				i, FieldCount, *FString::Join(Values[i], TEXT("|")));

			continue; // 🔥 크래시 대신 스킵
		}

		//UE_LOG(LogTemp, Warning, TEXT("TestLog3"));

		FStudentRowData Row;
		int index = 0;


		//UE_LOG(LogTemp, Warning, TEXT("TestLog4"));
		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Name;          // 성명 0
		Row.Name = Values[i][index++];

		//UE_LOG(LogTemp, Warning, TEXT("TestLog5"));

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString ID;        // 수용번호 1
		Row.ID = Values[i][index++];

		UE_LOG(LogTemp, Error, TEXT("%s"), *Row.ID);

		//UE_LOG(LogTemp, Warning, TEXT("TestLog6"));

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Birth;      // 생년월일 2
		Row.Birth = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString CrimeType;     // 범죄유형 3
		Row.CrimeType = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString EduCourse;     // 교육과정 4
		Row.EduCourse = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString EduPeriod;     // 교육시기 5
		Row.EduPeriod = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString VrType;        // VR유형 6
		Row.VrType = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString VrSession;    //VR 회기 7
		if (Values[i][index] != "6")
			Row.VrSession = Values[i][index];
		else
		{
			Row.VrSession = "5";
			Row.bAllSessionsCompleted = true;
		}
		index++;

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Start;          // 시작일 8
		Row.Start = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString End;          // 종료일 9
		Row.End = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Fin;      // 수료여부 10
		Row.Fin = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Manager;        // 담당자 11
		Row.Manager = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString RegisterDate;   // 등록일 12
		Row.RegisterDate = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString UpdateDate;   //수정일 13
		Row.UpdateDate = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString AVConcentration;  //평균집중도 14
		Row.AVConcentration = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//int32 Satisfaction;  //만족도 15
		Row.Satisfaction = FCString::Atoi(*Values[i][index++]);

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Consent_Test; //동의서 16
		Row.Consent_Test = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Pre_Test; //사전검사 17
		Row.Pre_Test = Values[i][index++];
		//UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %s"), *Row.Pre_Test);

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Post_Test; //사후검사 18
		Row.Post_Test = Values[i][index++];

		int tempCount = 0;

		if (Row.Pre_Test == "-")
		{
			Row.Pre1 = Row.Pre2 = Row.Pre3 = Row.Pre4 = 0;
			Row.Pre5 = Row.Pre6 = Row.Pre7 = Row.Pre8 = 0;
		}
		else
		{
			TArray<FString> PreTestData;
			Row.Pre_Test.ParseIntoArray(PreTestData, TEXT(","));
			////사전검사 점수
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre1;
			Row.Pre1 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre2;
			Row.Pre2 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre3;
			Row.Pre3 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre4;
			Row.Pre4 = FCString::Atoi(*PreTestData[tempCount++]);

			//if (Row.CrimeType == TEXT("마약"))
			{
				//UE_LOG(LogTemp, Error, TEXT("Pre Check Drug"));
				Row.Pre5 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre6 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre7 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre8 = FCString::Atoi(*PreTestData[tempCount++]);
			}
			//else
			//{
			//	Row.Pre5 = Row.Pre6 = Row.Pre7 = Row.Pre8 = 0;
			//}
		}
		//UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %d, %d, %d, %d, %d, %d, %d, %d"), Row.Pre1, Row.Pre2, Row.Pre3, Row.Pre4, Row.Pre5, Row.Pre6, Row.Pre7, Row.Pre8);

		tempCount = 0;
		if (Row.Post_Test == "-")
		{
			Row.Post1 = Row.Post2 = Row.Post3 = Row.Post4 = 0;
			Row.Post5 = Row.Post6 = Row.Post7 = Row.Post8 = 0;
		}
		else
		{
			TArray<FString> PostTestData;
			Row.Post_Test.ParseIntoArray(PostTestData, TEXT(","));

			////사후검사 점수
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post1;`
			Row.Post1 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post2;
			Row.Post2 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post3;
			Row.Post3 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post4;
			Row.Post4 = FCString::Atoi(*PostTestData[tempCount++]);

			//if (Row.CrimeType == TEXT("마약"))
			{
				//UE_LOG(LogTemp, Error, TEXT("Post Check Drug"));
				Row.Post5 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post6 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post7 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post8 = FCString::Atoi(*PostTestData[tempCount++]);
			}
			//else
			//{
			//	Row.Post5 = Row.Post6 = Row.Post7 = Row.Post8 = 0;
			//}
		}

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TArray<FSessionNoteRow> SessionNotes; 19 20 21 22 23

		Row.SessionNotes.Empty();
		for (int32 s = 0; s < 5; ++s)
		{
			FSessionNoteRow NoteRow;

			int rowCount = 0;

			TArray<FString> sessionRowData;
			Values[i][index++].ParseIntoArray(sessionRowData, TEXT(","));

			NoteRow.SessionIndex = s + 1;

			if (sessionRowData[rowCount] != "-1")
			{
				NoteRow.Score = sessionRowData[rowCount++];
			}
			else
			{
				NoteRow.Score = "0";
				rowCount++;
			}

			// 특이사항 텍스트
			NoteRow.Note = sessionRowData[rowCount++];

			Row.SessionNotes.Add(NoteRow);
		}

		Row.SessionHeartRateSchedules.Empty();
		for (int32 s = 0; s < 5; ++s)
		{
			FSessionHeartRateLogs HeartRateLogs;

			HeartRateLogs.SessionIndex = s + 1;

			if (Values[i][index] != "-")
			{
				TArray<FString> tempLog;
				Values[i][index++].ParseIntoArray(tempLog, TEXT("@"));

				for (int j = 0; j < tempLog.Num(); j++)
				{
					FHeartRateLog log;
					int logIndex = 0;

					TArray<FString> tempData;
					tempLog[j].ParseIntoArray(tempData, TEXT(","));

					log.ServerMark = FCString::Atoi(*tempData[logIndex++]);
					log.Bpm = FCString::Atoi(*tempData[logIndex++]);

					HeartRateLogs.Logs.Add(log);
				}
				Row.SessionHeartRateSchedules.Add(HeartRateLogs);
			}
		}

		ParsedRows.Add(Row);
	}

	SetStudentRows(ParsedRows);

	//FPlatformProcess::Sleep(1.0f);

	//Send_DefaultDataSetting();
}

void UGameManager::Fuc_RecvDefaultDataSetting()
{
	StudentRows.Empty();
	TArray<FStudentRowData> ParsedRows;

	UE_LOG(LogTemp, Warning, TEXT("MakeData"));

	for (int i = 0; i < Values.Num(); i++)
	{
		const int32 FieldCount = Values[i].Num();

		if (FieldCount < 25)
		{
			// 어떤 row가 깨졌는지 원문을 남겨야 원인이 잡힘
			UE_LOG(LogTemp, Error, TEXT("Row %d invalid. FieldCount=%d. RowRaw=[%s]"),
				i, FieldCount, *FString::Join(Values[i], TEXT("|")));

			continue; // 🔥 크래시 대신 스킵
		}

		FStudentRowData Row;
		int index = 0;

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Name;          // 성명 0
		Row.Name = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString ID;        // 수용번호 1
		Row.ID = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Birth;      // 생년월일 2
		Row.Birth = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString CrimeType;     // 범죄유형 3
		Row.CrimeType = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString EduCourse;     // 교육과정 4
		Row.EduCourse = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString EduPeriod;     // 교육시기 5
		Row.EduPeriod = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString VrType;        // VR유형 6
		Row.VrType = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString VrSession;    //VR 회기 7
		if(Values[i][index] != "6")
			Row.VrSession = Values[i][index];
		else
		{
			Row.VrSession = "5";
			Row.bAllSessionsCompleted = true;
		}
		index++;

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Start;          // 시작일 8
		Row.Start = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString End;          // 종료일 9
		Row.End = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Fin;      // 수료여부 10
		Row.Fin = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Manager;        // 담당자 11
		Row.Manager = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString RegisterDate;   // 등록일 12
		Row.RegisterDate = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString UpdateDate;   //수정일 13
		Row.UpdateDate = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString AVConcentration;  //평균집중도 14
		Row.AVConcentration = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//int32 Satisfaction;  //만족도 15
		Row.Satisfaction = FCString::Atoi(*Values[i][index++]);

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Consent_Test; //동의서 16
		Row.Consent_Test = Values[i][index++];

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Pre_Test; //사전검사 17
		Row.Pre_Test = Values[i][index++];
		//UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %s"), *Row.Pre_Test);

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FString Post_Test; //사후검사 18
		Row.Post_Test = Values[i][index++];

		int tempCount = 0;

		if (Row.Pre_Test == "-")
		{
			Row.Pre1 = Row.Pre2 = Row.Pre3 = Row.Pre4 = 0;
			Row.Pre5 = Row.Pre6 = Row.Pre7 = Row.Pre8 = 0;
		}
		else
		{
			TArray<FString> PreTestData;
			Row.Pre_Test.ParseIntoArray(PreTestData, TEXT(","));
			////사전검사 점수
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre1;
			Row.Pre1 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre2;
			Row.Pre2 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre3;
			Row.Pre3 = FCString::Atoi(*PreTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Pre4;
			Row.Pre4 = FCString::Atoi(*PreTestData[tempCount++]);

			if (Row.CrimeType == TEXT("마약"))
			{
				//UE_LOG(LogTemp, Error, TEXT("Pre Check Drug"));
				Row.Pre5 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre6 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre7 = FCString::Atoi(*PreTestData[tempCount++]);
				Row.Pre8 = FCString::Atoi(*PreTestData[tempCount++]);
			}
			else
			{
				Row.Pre5 = Row.Pre6 = Row.Pre7 = Row.Pre8 = 0;
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %d, %d, %d, %d, %d, %d, %d, %d"), Row.Pre1, Row.Pre2, Row.Pre3, Row.Pre4, Row.Pre5, Row.Pre6, Row.Pre7, Row.Pre8);

		tempCount = 0;
		if (Row.Post_Test == "-")
		{
			Row.Post1 = Row.Post2 = Row.Post3 = Row.Post4 = 0;
			Row.Post5 = Row.Post6 = Row.Post7 = Row.Post8 = 0;
		}
		else
		{
			TArray<FString> PostTestData;
			Row.Post_Test.ParseIntoArray(PostTestData, TEXT(","));

			////사후검사 점수
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post1;`
			Row.Post1 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post2;
			Row.Post2 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post3;
			Row.Post3 = FCString::Atoi(*PostTestData[tempCount++]);
			//UPROPERTY(EditAnywhere, BlueprintReadWrite)
			//int32 Post4;
			Row.Post4 = FCString::Atoi(*PostTestData[tempCount++]);

			if (Row.CrimeType == TEXT("마약"))
			{
				//UE_LOG(LogTemp, Error, TEXT("Post Check Drug"));
				Row.Post5 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post6 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post7 = FCString::Atoi(*PostTestData[tempCount++]);
				Row.Post8 = FCString::Atoi(*PostTestData[tempCount++]);
			}
			else
			{
				Row.Post5 = Row.Post6 = Row.Post7 = Row.Post8 = 0;
			}
		}

		//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TArray<FSessionNoteRow> SessionNotes; 19 20 21 22 23

		Row.SessionNotes.Empty();
		for (int32 s = 0; s < 5; ++s)
		{
			FSessionNoteRow NoteRow;

			int rowCount = 0;

			TArray<FString> sessionRowData;
			Values[i][index++].ParseIntoArray(sessionRowData, TEXT(","));

			NoteRow.SessionIndex = s + 1;

			if (sessionRowData[rowCount] != "-1")
			{
				NoteRow.Score = sessionRowData[rowCount++];
			}
			else
			{
				NoteRow.Score = "0";
				rowCount++;
			}

			// 특이사항 텍스트
			NoteRow.Note = sessionRowData[rowCount++];

			Row.SessionNotes.Add(NoteRow);
		}

		Row.SessionHeartRateSchedules.Empty();
		for (int32 s = 0; s < 5; ++s)
		{
			FSessionHeartRateLogs HeartRateLogs;

			HeartRateLogs.SessionIndex = s + 1;

			if (Values[i][index] != "-")
			{
				TArray<FString> tempLog;
				Values[i][index++].ParseIntoArray(tempLog, TEXT("@"));

				for (int j = 0; j < tempLog.Num(); j++)
				{
					FHeartRateLog log;
					int logIndex = 0;

					TArray<FString> tempData;
					tempLog[j].ParseIntoArray(tempData, TEXT(","));

					log.ServerMark = FCString::Atoi(*tempData[logIndex++]);
					log.Bpm = FCString::Atoi(*tempData[logIndex++]);

					HeartRateLogs.Logs.Add(log);
				}
				Row.SessionHeartRateSchedules.Add(HeartRateLogs);
			}
		}

		ParsedRows.Add(Row);
	}

	//for (int i = 0; i < StudentRows.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %s"), *StudentRows[i].Name);
	//	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvDefaultSearch recv data : %s"), *StudentRows[i].SessionNotes[4].Note);
	//}

	SetStudentRows(ParsedRows);
	////OnStudentRowsUpdated.Broadcast();
}

void UGameManager::Send_DefaultSearch()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::DefaultSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_DEFAULT::DEFAULT_SEARCH));
}

void UGameManager::Send_DefaultDataSetting()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::DefaultSetting),
		static_cast<uint8>(PROTOCOLSUB_DEFAULT::DEFAULT_SETDATA));
}

#pragma endregion


#pragma region LoginSettingBindingDatas

void UGameManager::Fuc_RecvLoginChangePW(bool isSuccess)
{
	RecvLoginChangePW.Broadcast(isSuccess);
}

void UGameManager::Fuc_RecvLoginCheckPW(bool isSuccess)
{
	RecvLoginCheckPW.Broadcast(isSuccess);
}

void UGameManager::Fuc_RecvInmateLogin(bool isSuccess)
{
	RecvInmateLogin.Broadcast(isSuccess);
}

void UGameManager::Send_LoginCheckPW(FString pinNum)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::LoginSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_LOGIN::MANAGE_CHECK_PW), pinNum);
}

void UGameManager::Send_ChangePW(FString currPW, FString newPW)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::LoginSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_LOGIN::MANAGE_CHANGE_PW), currPW, newPW);
}

void UGameManager::Send_InmateLogin(FString inmateNum)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::LoginSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_LOGIN::INMATE_LOGIN_CHECK), inmateNum);
}

#pragma endregion

#pragma region InmateSettingBindingDatas

void UGameManager::Fuc_RecvInmateADD(SEND_TEXT_TYPE printType)
{
	RecvInmateADD.Broadcast(printType);
}

void UGameManager::Fuc_RecvInmateUpdate(SEND_TEXT_TYPE type, FString data)
{
	RecvInmateUpdate.Broadcast(type, data);
}

void UGameManager::Fuc_RecvInmateSearch(FString data)
{
	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvInmateSearch recv data: %s"), *data);

	// 1) data 를 파싱해서 TArray<FStudentRowData> 생성
	TArray<FStudentRowData> ParsedRows;

	// 예시: "홍길동|ID001|1990-01-01|성폭력|기본|1차|VR A|2025-01-10|2025-01-20|수료\n..."
	TArray<FString> Lines;
	data.ParseIntoArray(Lines, TEXT("\n"));

	for (FString& Line : Lines)
	{
		TArray<FString> Cols;
		Line.ParseIntoArray(Cols, TEXT("|"));

		if (Cols.Num() < 10)
		{
			continue;
		}

		FStudentRowData Row;
		Row.Name = Cols[0];
		Row.ID = Cols[1];
		Row.Birth = Cols[2];
		Row.CrimeType = Cols[3];
		Row.EduCourse = Cols[4];
		Row.EduPeriod = Cols[5];
		Row.VrType = Cols[6];
		Row.Start = Cols[7];
		Row.End = Cols[8];
		Row.Fin = Cols[9];
		Row.Manager = Cols[10];
		Row.RegisterDate = Cols[11];
		Row.UpdateDate = Cols[12];

		ParsedRows.Add(Row);
	}

	// 2) 싱글톤에 저장
	SetStudentRows(ParsedRows);
}

void UGameManager::Send_InmateADD(const FString& data)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_ADD), data);
}

void UGameManager::Send_InmateSearch()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_SEARCH));
}

void UGameManager::Send_InmateUpdate(const FString& data)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
	                                  static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_UPDATE),
	                                  data);
}

#pragma endregion

#pragma region ProgramSettingBindingDatas

void UGameManager::Fuc_RecvProgramUpdate(FString _data)
{
	UE_LOG(LogTemp, Log, TEXT("Fuc_RecvProgramUpdate"));

	TArray<FString> tempSplit;
	_data.ParseIntoArray(tempSplit, TEXT("#"));

	int type = FCString::Atoi(*tempSplit[0]);

	switch (type)
	{
	case (uint8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MARK:
	{
		tempSplit.RemoveAt(0);
		Fuc_RecvHeartRateMark(tempSplit);
	}
	break;
	default:
		break;
	}
}

void UGameManager::Send_ProgramUpdate(const FString& data)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::ProgramSetting),
									  static_cast<uint8>(PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE),
									  data);
}

void UGameManager::Send_ProgramUpdate_RoundHeartRate_MovieNum(const FString& data)
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::ProgramSetting),
									  static_cast<uint8>(PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE),
									  data);
}

#pragma endregion

#pragma region CmsBindingDatas

void UGameManager::Fuc_RecvTrackingNum(int num)
{
	RecvTrackingNum.Broadcast(num);

	RecvTrackinNumBP.Broadcast(num);
}

void UGameManager::Fuc_RecvCmsControllerNextRound()
{
	RecvCmsControllerNextRound.Broadcast();
	udpManager->SendCommandToWatch("stop");
}

void UGameManager::Send_CmsControllerStart()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
	                                  static_cast<uint8>(PROTOCOLSUB_CMS::Start));
	udpManager->SendCommandToWatch("start");
}

void UGameManager::Send_CmsControllerPlay()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
	                                  static_cast<uint8>(PROTOCOLSUB_CMS::Play));
	udpManager->SendCommandToWatch("start");
}

void UGameManager::Send_CmsControllerStop()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
	                                  static_cast<uint8>(PROTOCOLSUB_CMS::Stop));
	udpManager->SendCommandToWatch("stop");
}

#pragma endregion

#pragma region UdpBindingDatas

void UGameManager::Fuc_RecvHeartRate(int32 bpm, int64 timeStamp)
{
	RecvHeartRate.Broadcast(FString::FromInt(bpm));
}

#pragma endregion


#pragma region StudentData

bool UGameManager::FindStudentById(const FString& Id, FStudentRowData& OutData) const
{
	bool IsFind = false;
	for (const FStudentRowData& Row : StudentRows)
	{
		//if (Row.ID == Id)
		if (Row.ID == Id && Row.Fin == TEXT("진행"))
		{
			OutData = Row;
			IsFind = true;
		}
	}
	return IsFind;
}

void UGameManager::SetStudentRows(const TArray<FStudentRowData>& InRows)
{
	StudentRows = InRows;
	UE_LOG(LogTemp, Warning, TEXT("UGameManager::SetStudentRows - Count: %d"), StudentRows.Num());
	OnStudentRowsUpdated.Broadcast();
}

bool UGameManager::AddStudentRow(const FStudentRowData& Row)
{
	int checkIndex = 0;

	for (int32 i = 0; i < StudentRows.Num(); ++i)
	{
		if (StudentRows[i].ID == Row.ID)
		{
			if(StudentRows[i].Fin == TEXT("진행"))
				checkIndex++;
		}
	}

	if (checkIndex == 0)
	{
		StudentRows.Add(Row);
		UE_LOG(LogTemp, Warning, TEXT("UGameManager::AddStudentRow - Added ID: %s"), *Row.ID);

		OnStudentRowsUpdated.Broadcast();
	}

	return checkIndex == 0 ? true : false;
}

int UGameManager::UpsertStudentRow(const FStudentRowData& Row)
{
	TArray<int32> CheckType;
	int32 updateIndex = INDEX_NONE;
	int32 checkCount = 0;

	for (int32 i = 0; i < StudentRows.Num(); ++i)
	{
		if (StudentRows[i].ID == Row.ID)
		{
			// 총 3가지 분류
			// 1. 같은 번호의 재소자 중에 진행이 존재할 경우 다른 종료 재소자의 상태 코드를 변경 못하도록 만들기 (수정 안됨)
			// 2. 같은 번호의 재소자 중에 진행이 없을 경우 다른 종료 재소자의 상태 코드를 바꿀 수 있도록 만들기 (수정 가능)
			// 3. 같은 번호의 재소자 중에 진행인 재소자의 정보를 찾아서 수정 (수정 가능)

			checkCount++;
			if(StudentRows[i].Fin == TEXT("종료"))
				CheckType.Add(i);
			if (StudentRows[i].Fin == TEXT("진행"))
				updateIndex = i;
		}
	}

	if(updateIndex != INDEX_NONE)
		if (checkCount > 1 && checkCount != INDEX_NONE && StudentRows[updateIndex] != Row)
			return INDEX_NONE;
	
	if (CheckType.Num() > 1 && updateIndex == INDEX_NONE)
		return INDEX_NONE;

	if (updateIndex != INDEX_NONE)
	{
		StudentRows[updateIndex] = Row;
		UE_LOG(LogTemp, Warning, TEXT("UGameManager::UpsertStudentRow - Updated ID: %s"), *Row.ID);

		OnStudentRowsUpdated.Broadcast();
	}

	return updateIndex;
}

void UGameManager::CreateDummyStudentData()
{
	UE_LOG(LogTemp, Warning, TEXT("UGameManager::CreateDummyStudentData"));

	StudentRows.Empty();

	for (int32 i = 0; i < 20; i++)
	{
		FStudentRowData Row;

		Row.Name = FString::Printf(TEXT("홍길동%d"), i);
		Row.ID = FString::Printf(TEXT("ID%04d"), i);
		Row.Birth = TEXT("900101");
		Row.CrimeType = (i % 2 == 0) ? TEXT("성폭력") : TEXT("마약");
		Row.EduCourse = TEXT("기본");
		Row.EduPeriod = FString::Printf(TEXT("25-%d"), i + 1);
		Row.VrType = TEXT("C");
		Row.VrSession = (i % 2 == 0) ? TEXT("2") : TEXT("3");
		Row.Start = TEXT("2025-01-10");
		Row.End = TEXT("2025-01-20");
		Row.Fin = (i % 2 == 0) ? TEXT("진행") : TEXT("종료");

		Row.Manager = FString::Printf(TEXT("담당자_%d"), i % 3);
		Row.RegisterDate = TEXT("25-01-01");
		Row.UpdateDate = FString::Printf(TEXT("25-01-%02d"), 5 + i);

		//  평균 집중도 (예: "72.3%")
		// i에 따라 약간씩 바뀌게
		float BaseCon = 70.0f + static_cast<float>(i % 5) * 2.5f; // 70 ~ 80 근처
		Row.AVConcentration = FString::Printf(TEXT("%.1f%%"), BaseCon);

		//  만족도
		Row.Satisfaction = 0;

		// 사전검사 점수 (대략 20~35)
		Row.Pre1 = 20 + (i % 5);
		Row.Pre2 = 22 + (i % 5);
		Row.Pre3 = 24 + (i % 5);
		Row.Pre4 = 26 + (i % 5);
		Row.Pre5 = 20 + (i % 5);
		Row.Pre6 = 22 + (i % 5);
		Row.Pre7 = 24 + (i % 5);
		Row.Pre8 = 26 + (i % 5);

		// 사후검사 점수 (사전보다 조금 높은 값으로)
		Row.Post1 = Row.Pre1 + 5;
		Row.Post2 = Row.Pre2 + 6;

		Row.Post3 = Row.Pre3 + 7;
		Row.Post4 = Row.Pre4 + 8;
		Row.Post5= Row.Pre1 + 5;
		Row.Post6 = Row.Pre2 + 6;

		Row.Post7 = Row.Pre3 + 7;
		Row.Post8 = Row.Pre4 + 8;

		Row.Consent_Test = TEXT("1");
		Row.Pre_Test = TEXT("2");
		Row.Post_Test = TEXT("-");


		//회기 데이터
		Row.SessionNotes.Empty();
		for (int32 s = 0; s < 5; ++s)
		{
			FSessionNoteRow NoteRow;
			NoteRow.SessionIndex = s + 1;

			// 회기별 집중도 살짝 다르게
			float SessionCon = BaseCon + s * 1.5f; // 예: 70.0, 71.5, 73.0 ...
			NoteRow.Score = FString::Printf(TEXT("%.1f%%"), SessionCon);

			// 특이사항 텍스트
			NoteRow.Note = FString::Printf(TEXT("%d회기: 특이사항 없음"), s + 1);

			Row.SessionNotes.Add(NoteRow);
		}


		StudentRows.Add(Row);
	}

	UE_LOG(LogTemp, Warning, TEXT("UGameManager::CreateDummyStudentData - Count: %d"), StudentRows.Num());
	OnStudentRowsUpdated.Broadcast();
}

void UGameManager::Send_SessionNoteUpdate(
	const FString& InmateId,
	int32 SessionIndex,
	const FString& NoteText
)
{
	//
	UE_LOG(LogTemp, Warning,
	       TEXT("Send_SessionNoteUpdate: ID=%s, Session=%d, Note=%s"),
	       *InmateId, SessionIndex, *NoteText);

	FString tempText = NoteText.Replace(TEXT("\r\n"), TEXT(""));
	tempText = tempText.Replace(TEXT(","), TEXT(""));
	tempText = tempText.Replace(TEXT("-"), TEXT(""));
	tempText = tempText.Replace(TEXT("#"), TEXT(""));
	tempText = tempText.Replace(TEXT("@"), TEXT(""));
	tempText = tempText.Replace(TEXT("$"), TEXT(""));

	FString result = FString::Printf(
		TEXT("%s#%s#%s#%s"),
		*FString::FromInt((int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_REMARKS),
		*InmateId,
		*FString::FromInt(SessionIndex),
		*FGenericPlatformHttp::UrlEncode(tempText)
	);

	Send_ProgramUpdate(result);
}

#pragma endregion


#pragma region LogData

static FString SerializeLogItem(const FLogItem& Item)
{
	return FString::Printf(
		TEXT("%s#%s#%s"),
		*FGenericPlatformHttp::UrlEncode(Item.Type),
		*FGenericPlatformHttp::UrlEncode(Item.Time),
		*FGenericPlatformHttp::UrlEncode(Item.Actor)
	);
}

void UGameManager::Send_LogSearch()
{
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::LogSetting),
		static_cast<uint8>(PROTOCOLSUB_LOG::LOG_SEARCH));
}

void UGameManager::Fuc_RecvLogSearch(FString data)
{
	TArray<FString> Columns;
	data.ParseIntoArray(Columns, TEXT("$"));

	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvLogSearch"));

	for (int i = 0; i < Columns.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Log_ParseIntoArray"));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *FGenericPlatformHttp::UrlDecode(Columns[i]));
		TArray<FString> temp;
		Columns[i].ParseIntoArray(temp, TEXT("#"));

		FLogItem Item;
		Item.Type = FGenericPlatformHttp::UrlDecode(temp[0]);
		Item.Time = FGenericPlatformHttp::UrlDecode(temp[1]);
		Item.Actor = FGenericPlatformHttp::UrlDecode(temp[2]);

		//UE_LOG(LogTemp, Warning, TEXT("%s, %s, %s"), *Item.Type, *Item.Time, *Item.Actor);

		LogItems.Insert(Item, 0); // 최신 로그 위로
	}

	OnLogUpdated.Broadcast();
}

// 서버에 로그 전송
void UGameManager::Send_Log(const FLogItem& Item)
{
	const FString Body = SerializeLogItem(Item);

	UE_LOG(LogTemp, Warning, TEXT("Send_Log: %s"), *Body);


	SendThread::GetInst()->SetMessage(
		static_cast<uint8>(PROTOCOL_MAIN::LogSetting),      
		static_cast<uint8>(PROTOCOLSUB_LOG::LOG_ADD),       
		Body
	);
	
}

void UGameManager::Request_LogList()
{
	
}

void UGameManager::AddLog(const FLogItem& Item)
{
	LogItems.Insert(Item, 0); // 최신 로그 위로
	OnLogUpdated.Broadcast();
}

void UGameManager::AddSimpleLog(const FString& Type, const FString& Actor)
{
	FLogItem Item;
	Item.Type = Type;

	// 현재 시간을 "YYYY-MM-DD HH:MM" 포맷으로
	const FDateTime Now = FDateTime::Now();
	Item.Time = FString::Printf(TEXT("%04d-%02d-%02d %02d:%02d"),
								Now.GetYear(), Now.GetMonth(), Now.GetDay(),
								Now.GetHour(), Now.GetMinute());

	Item.Actor = Actor;

	//로컬 리스트 + UI 갱신
	AddLog(Item);

	//서버로도 전송
	Send_Log(Item);
}


void UGameManager::Fuc_RecvLogList(const FString& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Fuc_RecvLogList recv data: %s"), *Data);

	LogItems.Empty();

// LogItems.Add(Item);
	OnLogUpdated.Broadcast();
}

void UGameManager::CreateDummyLogs()
{
	LogItems.Empty();

	auto MakeLog = [&](FString Type, FString Time, FString Actor)
	{
		FLogItem L;
		L.Type = Type;
		L.Time = Time;
		L.Actor = Actor;
		LogItems.Add(L);
	};

	MakeLog(TEXT("신규 등록"), TEXT("2024-11-10 12:50"), TEXT("관리자A"));
	MakeLog(TEXT("로그인"), TEXT("2024-11-09 10:12"), TEXT("시스템"));
	MakeLog(TEXT("세션 종료"), TEXT("2024-11-08 17:50"), TEXT("관리자B"));

	OnLogUpdated.Broadcast();
}

#pragma endregion


// 공통: FStudentRowData → 서버로 보낼 문자열로 직렬화
FString UGameManager::SerializeStudentRow(const uint8& main, const uint8& sub, const FStudentRowData& R)
{
	//// 서버 형식에 맞게 수정해서 쓰면 됨
	//// 성명#수용번호#생년월일#상태#범죄유형#교육과정#교육시기#VR유형#담당자
	//return FString::Printf(
	//	TEXT("%s#%s#%s#%s#%s#%s#%s#%s#%s"),
	//	*R.Name,
	//	*R.ID,
	//	*R.Birth,
	//	*R.Fin,
	//	*R.CrimeType,
	//	*R.EduCourse,
	//	*R.EduPeriod,
	//	*R.VrType,
	//	*R.Manager
	//);
	FString result;

	switch (main)
	{
	case (uint8)PROTOCOL_MAIN::InmateSetting:
	{
		switch (sub)
		{
		case (uint8)PROTOCOLSUB_INMATE::INMATE_ADD:
		{
			result = FString::Printf(
				TEXT("%s#%s#%s#%s#%s#%s#%s#%s"),
				*FGenericPlatformHttp::UrlEncode(R.Name),
				*R.ID,
				*R.Birth,
				*FGenericPlatformHttp::UrlEncode(R.CrimeType),
				*FGenericPlatformHttp::UrlEncode(R.EduCourse),
				*R.EduPeriod,
				*R.VrType,
				*FGenericPlatformHttp::UrlEncode(R.Manager)
			);
		}
		break;
		case (uint8)PROTOCOLSUB_INMATE::INMATE_UPDATE:
		{
			result = FString::Printf(
				TEXT("%s$%s#%s#%s#%s$%s"),
				*R.ID,
				*FGenericPlatformHttp::UrlEncode(R.Name),
				*R.Birth,
				*R.EduPeriod,
				*FGenericPlatformHttp::UrlEncode(R.Manager),
				*FGenericPlatformHttp::UrlEncode(R.Fin)
			);
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}

	return result;
	//return FGenericPlatformHttp::UrlEncode(result);
}

void UGameManager::Send_StudentRegister(const FStudentRowData& Data)
{
	const FString Body = SerializeStudentRow(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
											static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_ADD),
											Data);
	UE_LOG(LogTemp, Warning, TEXT("Send_StudentRegister: %s"), *Body);

	//아래 쪽
	Send_InmateADD(Body);
}

void UGameManager::Send_StudentUpdate(const FStudentRowData& Data, int updateIndex)
{
	FString Body = SerializeStudentRow(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
											static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_UPDATE),
											Data);
	UE_LOG(LogTemp, Warning, TEXT("Send_StudentUpdate: %s"), *Body);

	Body.Append("$" + FString::FromInt(updateIndex));

	Send_InmateUpdate(Body);
}


void UGameManager::Fuc_RecvTutorialEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("TutorialEnd received (no avg/stddev in GameManager)"));
	OnTutorialEnd.Broadcast();

	AddSimpleLog(TEXT("튜토리얼 종료"), TEXT("시스템"));
}

#pragma endregion



//--------------회기별 심박수 ---------------------

void UGameManager::Send_SessionHeartRateSchedule(const FString& InmateId, int32 SessionIndex,
	const TArray<FHeartRateLog>& Logs)
{
	FString logData = "";
	for (int i = 0; i < Logs.Num(); i++)
	{
		logData += FString::FromInt(Logs[i].Bpm) + ",";
		logData += FString::FromInt(Logs[i].TimestampMs) + "@";
	}

	if(logData != "")
		logData.RemoveAt(logData.Len() - 1);

	const FString Body = FString::Printf(TEXT("%d#%s#%d#%s"), (int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MOVIE_NUM, *InmateId, SessionIndex, *logData);
	
	Send_ProgramUpdate_RoundHeartRate_MovieNum(Body);
}

void UGameManager::Send_SessionHeartRateLogOnce(
	const FString& InmateId,
	int32 SessionIndex,
	int32 Bpm,
	int32 ServerMark
)
{
	UE_LOG(LogTemp, Log, TEXT("Send_SessionHeartRateLogOnce"));

	const FString Body = FString::Printf(TEXT("%d#%s#%d#%d#%d"), (int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MOVIE_NUM, *InmateId, SessionIndex, Bpm, ServerMark);

	Send_ProgramUpdate_RoundHeartRate_MovieNum(Body);
}






void UGameManager::Send_SessionHeartRateScheduleRequest(const FString& InmateId, int32 SessionIndex)
{
	// 예: "ID#SessionIndex"
	const FString Body = FString::Printf(TEXT("%s#%d"), *InmateId, SessionIndex);

	//SendThread::GetInst()->SetMessage(
	//	static_cast<uint8>(PROTOCOL_MAIN::ProgramSetting),
	//	static_cast<uint8>(PROTOCOLSUB_PROGRAM::PROGRAM_HR_SCHEDULE_SEARCH), // ✅ 서버에 맞는 sub로
	//	Body
	//);
}

void UGameManager::Fuc_RecvSessionHeartRateSchedule(FString data)
{
	const FString Decoded = FGenericPlatformHttp::UrlDecode(data);

	TArray<FString> Parts;
	Decoded.ParseIntoArray(Parts, TEXT("#"));
	if (Parts.Num() < 3) return;

	const FString InmateId = Parts[0];
	const int32 SessionIndex = FCString::Atoi(*Parts[1]);
	const FString LogsStr = Parts[2];

	TArray<FHeartRateLog> Logs;

	TArray<FString> Items;
	LogsStr.ParseIntoArray(Items, TEXT("|"));

	for (const FString& Item : Items)
	{
		if (Item.IsEmpty()) continue;

		TArray<FString> Fields;
		Item.ParseIntoArray(Fields, TEXT(","));
		if (Fields.Num() != 2) continue;

		FHeartRateLog L;
		L.TimestampMs = FCString::Atoi64(*Fields[0]);
		L.Bpm = FCString::Atoi(*Fields[1]);
		Logs.Add(L);
	}

	OnSessionHeartRateScheduleReceived.Broadcast(InmateId, SessionIndex, Logs);
}

void UGameManager::ParseDefaultSearchData(const FString& data, TArray<FStudentRowData>& OutRows)
{
}


void UGameManager::Send_RunContentStart(const FStudentRowData& Student, int32 SessionIndex)
{
	FString data = FString::Printf(
		TEXT("%s#%s#%s#%s"),
		*Student.ID,
		*FGenericPlatformHttp::UrlEncode(Student.CrimeType),
		*Student.VrType,
		*FString::FromInt(SessionIndex)
	);
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
		static_cast<uint8>(PROTOCOLSUB_CMS::Start), data);

	const FString Body = FString::Printf(TEXT("%d#%s"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_STARTAT, *Student.ID);
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);

	udpManager->SendCommandToWatch("start");
}
void UGameManager::Send_SessionPause()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" Send_CmsControllerStop")); // 화면출력
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
		static_cast<uint8>(PROTOCOLSUB_CMS::Pause));
	udpManager->SendCommandToWatch("stop");
}

void UGameManager::Send_SessionResume()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" Send_CmsControllerPlay")); // 화면출력
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
		static_cast<uint8>(PROTOCOLSUB_CMS::Play));
	udpManager->SendCommandToWatch("start");
}

void UGameManager::Send_SessionStop()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" Send_CmsControllerStop")); // 화면출력
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
		static_cast<uint8>(PROTOCOLSUB_CMS::Stop));
	udpManager->SendCommandToWatch("stop");

	RecvStopContentSignal.Broadcast(true);
}

void UGameManager::Send_SectionMove(int index)
{
	const FString Body = FString::Printf(TEXT("%d"), index);
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::CMS_Controller),
		static_cast<uint8>(PROTOCOLSUB_CMS::SectionMovement), Body);
}


void UGameManager::Send_ConsentAgreed(const FString& StudentId)
{
	const FString Body = FString::Printf(TEXT("%d#%s"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_CONSENTTEST, *StudentId);
	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}

void UGameManager::Send_PreTestUpdate(const FString& InmateId, int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d,%d,%d,%d,0,0,0,0"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_PRETEST, *InmateId, Pre1, Pre2, Pre3, Pre4);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}

void UGameManager::Send_PreTestDrugUpdate(const FString& InmateId, int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4,
	int32 Pre5, int32 Pre6, int32 Pre7, int32 Pre8)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d,%d,%d,%d,%d,%d,%d,%d"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_PRETEST, *InmateId, Pre1, Pre2, Pre3, Pre4, Pre5, Pre6, Pre7, Pre8);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}

void UGameManager::Send_PostTestUpdate(const FString& InmateId, int32 Post1, int32 Post2, int32 Post3, int32 Post4)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d,%d,%d,%d,0,0,0,0"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_POSTTEST, *InmateId, Post1, Post2, Post3, Post4);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}

void UGameManager::Send_PostTestDrugUpdate(const FString& InmateId, int32 Post1, int32 Post2, int32 Post3, int32 Post4,
	int32 Post5, int32 Post6, int32 Post7, int32 Post8)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d,%d,%d,%d,%d,%d,%d,%d"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_POSTTEST, *InmateId, Post1, Post2, Post3, Post4, Post5, Post6, Post7, Post8);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}

void UGameManager::Send_SatisfactionUpdate(const FString& InmateId, int32 InSatisfaction)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d"), (int)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_LASTCHECK, *InmateId, InSatisfaction);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::TreatmentSetting),
		static_cast<uint8>(PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE), Body);
}



bool UGameManager::UpdateStudentConsentLocal(const FString& StudentId, const FString& ConsentText)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{
			Row.Consent_Test = ConsentText;
			OnStudentRowsUpdated.Broadcast();
			return true;
		}
	}
	return false;
}
bool UGameManager::UpdateStudentPreTestLocal(
	const FString& StudentId,const FString& PreTestText,
	int32 Pre1, int32 Pre2, int32 Pre3, int32 Pre4
)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{

			Row.Pre_Test = PreTestText;
			Row.Pre1 = Pre1;
			Row.Pre2 = Pre2;
			Row.Pre3 = Pre3;
			Row.Pre4 = Pre4;

			OnStudentRowsUpdated.Broadcast();
			
			return true;
		}
	}
	return false;
}

bool UGameManager::UpdateStudentPreTestDrugLocal(const FString& StudentId, const FString& PreTestText, int32 InPre1,
	int32 InPre2, int32 InPre3, int32 InPre4, int32 InPre5, int32 InPre6, int32 InPre7, int32 InPre8)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{

			Row.Pre_Test = PreTestText;
			Row.Pre1 = InPre1;
			Row.Pre2 = InPre2;
			Row.Pre3 = InPre3;
			Row.Pre4 = InPre4;
			Row.Pre5 = InPre5;
			Row.Pre6 = InPre6;
			Row.Pre7 = InPre7;
			Row.Pre8 = InPre8;

			OnStudentRowsUpdated.Broadcast();
			
			return true;
		}
	}
	return false;
}

bool UGameManager::UpdateStudentPostTestLocal(
	const FString& StudentId,const FString& PostTestText,
	int32 Post1, int32 Post2, int32 Post3, int32 Post4
)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{
			Row.Post_Test = PostTestText;
			Row.Post1 = Post1;
			Row.Post2 = Post2;
			Row.Post3 = Post3;
			Row.Post4 = Post4;

			OnStudentRowsUpdated.Broadcast();

			UE_LOG(LogTemp, Warning,
				TEXT("UpdateStudentPostTestLocal OK: %s -> %s"),
				*StudentId, *Row.Post_Test
			);
			return true;
		}
	}
	return false;
}

bool UGameManager::UpdateStudentPostTestDrugLocal(const FString& StudentId, const FString& PostText, int32 Post1,
	int32 Post2, int32 Post3, int32 Post4, int32 Post5, int32 Post6, int32 Post7, int32 Post8)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{

			Row.Post_Test = PostText;
			Row.Post1 = Post1;
			Row.Post2 = Post2;
			Row.Post3 = Post3;
			Row.Post4 = Post4;
			Row.Post5 = Post5;
			Row.Post6 = Post6;
			Row.Post7 = Post7;
			Row.Post8 = Post8;

			OnStudentRowsUpdated.Broadcast();
			
			return true;
		}
	}
	return false;
}


void UGameManager::UpdateStudentSatisfactionLocal(const FString& StudentId, int32 InSatisfaction)
{
	for (FStudentRowData& Row : StudentRows)
	{
		if (Row.ID == StudentId)
		{
			Row.Satisfaction = InSatisfaction;
			break;
		}
	}
	OnStudentRowsUpdated.Broadcast();
}

void UGameManager::RequestStopSession()
{
	//Send_SessionStop();
	RecvStopSignal.Broadcast(true);
}


void UGameManager::Fuc_RecvSessionCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("[Server] Session Completed"));
	OnSessionCompleted.Broadcast();
}




void UGameManager::AppendSessionHeartRateLocal(
	const FString& InmateId,
	int32 SessionIndex,
	const FHeartRateLog& Log
)
{
	for (FStudentRowData& S : StudentRows)
	{
		if (S.ID != InmateId)
			continue;
		
		FSessionHeartRateLogs* Target = nullptr;
		for (FSessionHeartRateLogs& L : S.SessionHeartRateSchedules)
		{
			if (L.SessionIndex == SessionIndex)
			{
				Target = &L;
				break;
			}
		}
		
		if (!Target)
		{
			FSessionHeartRateLogs NewLogs;
			NewLogs.SessionIndex = SessionIndex;
			S.SessionHeartRateSchedules.Add(NewLogs);
			Target = &S.SessionHeartRateSchedules.Last();
		}

		Target->Logs.Add(Log);
		break;
	}
}


void UGameManager::RemoveStudentRowByID(const FString& TargetID)
{
	const int32 Removed = StudentRows.RemoveAll([&](const FStudentRowData& Row)
	{
		return Row.ID == TargetID;
	});

	if (Removed > 0)
	{
		OnStudentRowsUpdated.Broadcast();
	}
}

void UGameManager::Send_StudentDelete(const FString& TargetID)
{
	const FString Body = FString::Printf(TEXT("%s"), *TargetID);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::InmateSetting),
		static_cast<uint8>(PROTOCOLSUB_INMATE::INMATE_DELETE), Body);
}


void UGameManager::Send_RequestMovieNum(const FString& InmateId, int32 SessionIndex)
{
	const FString Body = FString::Printf(TEXT("%d#%s#%d"), (int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_REQUEST_MOVIE_NUM, *InmateId, SessionIndex);

	Send_ProgramUpdate(Body);
}

void UGameManager::Fuc_RecvHeartRateMark(TArray<FString> Data)
{
	const FString InmateId = Data[0];
	const int32 SessionIndex = FCString::Atoi(*Data[1]);;
	const int32 MovieNum = FCString::Atoi(*Data[2]);;

	OnServerHeartRateMarkReceived.Broadcast(InmateId, SessionIndex, MovieNum);

	UE_LOG(LogTemp, Log, TEXT("Fuc_RecvHeartRateMark"));
}

//임시 주석