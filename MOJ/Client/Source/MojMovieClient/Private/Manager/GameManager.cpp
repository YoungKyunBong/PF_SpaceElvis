// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GameManager.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendThread.h"
#include "../../Public/Server/RecvThread.h"
#include "../../Public/Server/ProcessThread.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Kismet/GameplayStatics.h"

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

			if (TempTypeName == "MovieClientA")
				DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::MovieClientA;
			else
				DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::MovieClientB;
		}
	}
}

void UGameManager::Init()
{
	Super::Init();

	if (IsLocalGame)return;
	FileLoadIP();

	SocketManager::GetInst()->Init(ServerIP);

	RecvThread::GetInst()->MakeThread();
	SendThread::GetInst()->MakeThread();
	ProcessThread::GetInst()->MakeThread();

	ProcessThread::GetInst()->GetFRequestMovieNum()->AddUFunction(this, FName("Fuc_RecvRequestMovieNum"));

#pragma region CmsBindingDatas
	ProcessThread::GetInst()->GetFCmsControllerStart()->AddUFunction(this, FName("Fuc_RecvCmsControllerStart"));
	ProcessThread::GetInst()->GetFCmsControllerPlay()->AddUFunction(this, FName("Fuc_RecvCmsControllerPlay"));
	ProcessThread::GetInst()->GetFCmsControllerStop()->AddUFunction(this, FName("Fuc_RecvCmsControllerStop"));
	ProcessThread::GetInst()->GetFCmsControllerPause()->AddUFunction(this, FName("Fuc_RecvCmsControllerPause"));

	ProcessThread::GetInst()->GetFCmsMovieNum()->AddUFunction(this, FName("Fuc_RecvCmsMovieNum"));
#pragma endregion
	Send_DeviceType();
}

void UGameManager::Shutdown()
{
	Super::Shutdown();

	//FPlatformProcess::Sleep(0.05f);

	//Send_SetSceneType(true);

	if (SocketManager::GetInst()->QuitConnection())
	{
		if (SendThread::GetInst() != nullptr)
			SendThread::GetInst()->StopListen(false);

		if (RecvThread::GetInst() != nullptr)
			RecvThread::GetInst()->StopListen(false);

		if (ProcessThread::GetInst() != nullptr)
			ProcessThread::GetInst()->StopListen(false);
	}
}

void UGameManager::SetSoundData()
{
	//빌드 테스트
	TArray<FMTSoundTable*> OutArray;
	OutArray.Empty();

	//현대 TArray<FTexTable> UDataTableComponent::GetLevelData(int LevelIndex) 함수 참고
	InsideSoundData->GetAllRows<FMTSoundTable>(TEXT("SoundID"), OutArray);

	SoundArray.Empty();
	for (int i = 0; i < OutArray.Num(); ++i)
	{
		SoundArray.Add(*OutArray[i]);
	}
}

void UGameManager::SetNaTextData()
{
	TArray<FMTNATEXTTable*>OutArray;
	OutArray.Empty();

	InsideNaTextData->GetAllRows<FMTNATEXTTable>(TEXT("TextID"), OutArray);

	NaTextArray.Empty();
	for (int i = 0; i < OutArray.Num(); ++i)
	{
		NaTextArray.Add(*OutArray[i]);
	}
}

void UGameManager::SetNtTextData()
{
	TArray<FMTNAMETAGTEXTTable*>OutArray;
	OutArray.Empty();

	InsideNtTextData->GetAllRows<FMTNAMETAGTEXTTable>(TEXT("TextID"), OutArray);

	NtTextArray.Empty();
	for (int i = 0; i < OutArray.Num(); ++i)
	{
		NtTextArray.Add(*OutArray[i]);
	}
}

void UGameManager::SetTextureData()
{
	TArray<FMTTextureTable*> OutArray;
	OutArray.Empty();

	//현대 TArray<FTexTable> UDataTableComponent::GetLevelData(int LevelIndex) 함수 참고
	InsideTextureData->GetAllRows<FMTTextureTable>(TEXT("Alias"), OutArray);

	TextureArray.Empty();
	for (int i = 0; i < OutArray.Num(); ++i)
	{
		TextureArray.Add(*OutArray[i]);
	}
}

USoundBase* UGameManager::GetSound(FString _SoundID, ENationType _type)
{
	_SoundID = _SoundID.RightChop(2);
	int Index = FCString::Atoi(*_SoundID);

	if (Index > SoundArray.Num())
		return nullptr;

	switch (_type)
	{
	case ENationType::Sexual_SituationOne:
		return SoundArray[Index].KOR_SD;
		break;

	case ENationType::Sexual_SituationTwo:
		return SoundArray[Index].ENG_SD;
		break;
	default:
		return SoundArray[Index].KOR_SD;
	}
}

FString UGameManager::GetNaText(FString _TextID, ENationType _type)
{
	FString TempID = _TextID;
	_TextID = _TextID.RightChop(2);
	int Index = FCString::Atoi(*_TextID);
	if (NaTextArray.Num() <= Index)
	{
		bool isnullindex = true;
		for (int i = 0; i < NaTextArray.Num(); i++)
		{
			if (NaTextArray[i].TextID.Equals(TempID))
			{
				Index = i;
				isnullindex = false;
				break;
			}
		}
		if (isnullindex)
			return FString(TEXT("SoundMgr_Wrong Text Index"));
	}

	switch (_type)
	{
	case ENationType::Sexual_SituationOne:
		return NaTextArray[Index].Sexual_SituationOne_Text;
	case ENationType::Sexual_SituationTwo:
		return NaTextArray[Index].Sexual_SituationTwo_Text;
	case ENationType::Sexual_SituationThree:
		return NaTextArray[Index].Sexual_SituationThree_Text;
	case ENationType::Sexual_SituationFour:
		return NaTextArray[Index].Sexual_SituationFour_Text;
	case ENationType::Sexual_SituationFive:
		return NaTextArray[Index].Sexual_SituationFive_Text;
	case ENationType::Sexual_SituationSix:
		return NaTextArray[Index].Sexual_SituationSix_Text;

	case ENationType::Homy_SituationOne:
		return NaTextArray[Index].Homy_SituationOne_Text;
	case ENationType::Homy_SituationTwo:
		return NaTextArray[Index].Homy_SituationTwo_Text;
	case ENationType::Homy_SituationThree:
		return NaTextArray[Index].Homy_SituationThree_Text;
	case ENationType::Homy_SituationFour:
		return NaTextArray[Index].Homy_SituationFour_Text;

	case ENationType::Stoking_SituationOne:
		return NaTextArray[Index].Stoking_SituationOne_Text;
	case ENationType::Stoking_SituationTwo:
		return NaTextArray[Index].Stoking_SituationTwo_Text;
	case ENationType::Stoking_SituationThree:
		return NaTextArray[Index].Stoking_SituationThree_Text;
	case ENationType::Stoking_SituationFour:
		return NaTextArray[Index].Stoking_SituationFour_Text;

	case ENationType::Child_SituationOne:
		return NaTextArray[Index].Child_SituationOne_Text;
	case ENationType::Child_SituationTwo:
		return NaTextArray[Index].Child_SituationTwo_Text;
	case ENationType::Child_SituationThree:
		return NaTextArray[Index].Child_SituationThree_Text;
	case ENationType::Child_SituationFour:
		return NaTextArray[Index].Child_SituationFour_Text; 

	case ENationType::Drug_SituationOne:
		return NaTextArray[Index].Drug_SituationOne_Text;
	case ENationType::Drug_SituationTwo:
		return NaTextArray[Index].Drug_SituationTwo_Text;
	case ENationType::Drug_SituationThree:
		return NaTextArray[Index].Drug_SituationThree_Text;
	case ENationType::Drug_SituationFour:
		return NaTextArray[Index].Drug_SituationFour_Text;
	}

	return NaTextArray[Index].Sexual_SituationOne_Text;
}

FString UGameManager::GetNtText(FString _TextID)
{
	FString TempID = _TextID;
	_TextID = _TextID.RightChop(2);
	int Index = FCString::Atoi(*_TextID);
	if (NtTextArray.Num() <= Index)
	{
		bool isnullindex = true;
		for (int i = 0; i < NtTextArray.Num(); i++)
		{
			if (NtTextArray[i].TextID.Equals(TempID))
			{
				Index = i;
				isnullindex = false;
				break;
			}
		}
		if (isnullindex)
			return FString(TEXT("SoundMgr_Wrong Text Index"));
	}

	switch (m_eNationType)
	{
	case ENationType::Sexual_SituationOne:
		return NtTextArray[Index].KOR_Text;

	case ENationType::Sexual_SituationTwo:
		return NtTextArray[Index].ENG_Text;
	}

	return NtTextArray[Index].KOR_Text;
}

UTexture2D* UGameManager::GetTexture(FString _TextureID)
{
	UTexture2D* TextureData = nullptr;

	for (int i = 0; i < TextureArray.Num(); i++)
	{
		if (TextureData != nullptr)
			break;

		if (_TextureID == TextureArray[i].Alias)
		{
			switch (m_eNationType)
			{
			case ENationType::Sexual_SituationOne:
				TextureData = TextureArray[i].Korea;
				break;

			case ENationType::Sexual_SituationTwo:
				TextureData = TextureArray[i].Japan;
				break;

			default:
				TextureData = TextureArray[i].Korea;
				break;
			}
		}
	}
	return TextureData;
}

void UGameManager::SetMovieNum(MovieSceneType _movieNum)
{
	movieNum = FString::FromInt((int)_movieNum);
}

void UGameManager::Send_DeviceType()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::ConnectClientSetting, (uint8)DEVICE_TYPE);
}

void UGameManager::Fuc_RecvRequestMovieNum(FString _data)
{
	UE_LOG(LogTemp, Log, TEXT("Fuc_RecvRequestMovieNum"));

	FString tempData = FString::FromInt((int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MARK);

	tempData.Append("#" + _data + "#" + movieNum);

	SendThread::GetInst()->SetMessage(static_cast<uint8>(PROTOCOL_MAIN::ProgramSetting),
		static_cast<uint8>(PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE),
		tempData);
}

void UGameManager::Fuc_RecvCmsControllerStart(FString _data)
{
	LevelName = "LV_";

	eyeFocusTotalCount = 0;
	eyeFocusCorrectCount = 0;

	TArray<FString> Columns;
	_data.ParseIntoArray(Columns, TEXT("#"));

	FString tempCrimeType = FGenericPlatformHttp::UrlDecode(Columns[1]);

	if (tempCrimeType == TEXT("성폭력"))
		LevelName += "Sexual_";
	else if (tempCrimeType == TEXT("가정폭력"))
		LevelName += "Homy_";
	else if (tempCrimeType == TEXT("아동학대"))
		LevelName += "Child_";
	else if (tempCrimeType == TEXT("스토킹"))
		LevelName += "Stoking_";
	else if (tempCrimeType == TEXT("마약"))
		LevelName += "Drug_";

	FString tempVrType = Columns[2];
	
	if (tempVrType == "B")
		LevelName += "Two_";
	else if (tempVrType == "C")
		LevelName += "Three_";
	else if (tempVrType == "D")
		LevelName += "Four_";
	else if (tempVrType == "E")
		LevelName += "Five_";
	else if (tempVrType == "F")
		LevelName += "Six_";

	roundNum = Columns[3];

	LevelName += "Round" + Columns[3];

	inmateNumber = Columns[0];

	RecvCmsControllerStart.Broadcast();
}

void UGameManager::Fuc_RecvCmsControllerPlay()
{
	RecvCmsControllerPlay.Broadcast();

	RecvCmsControllerPlayInBP.Broadcast();
}

void UGameManager::Fuc_RecvCmsControllerStop()
{
	const UWorld* World = GetWorld();
	check(World);
	UGameplayStatics::OpenLevel(World, *tutoLevel);
}

void UGameManager::Fuc_RecvCmsControllerPause()
{
	RecvCmsControllerPause.Broadcast();

	RecvCmsControllerStopInBP.Broadcast();
}

void UGameManager::Fuc_RecvCmsMovieNum(int num)
{
	RecvCmsMovieClose.Broadcast();

	RecvCmsMovieNum.Broadcast(num);
}

void UGameManager::Send_HeadTrackingNum(int Num)
{
	eyeFocusTotalCount++;

	if ((8 <= Num && Num <= 9) || (13 <= Num && Num <= 16) || (19 <= Num && Num <= 22) || (26 <= Num && Num <= 27))
	{
		eyeFocusCorrectCount++;
	}

	averEyeFocus = (eyeFocusCorrectCount / eyeFocusTotalCount) * 100.0f;

	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::HeadTracking, Num);
}

void UGameManager::Send_TempNextRound()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::Temp_NextRound);
}

void UGameManager::Send_TutoEnd()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::TutoEnd);
}

void UGameManager::Send_RoundEnd()
{
	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::CMS_Controller, (uint8)PROTOCOLSUB_CMS::RoundEnd);

	FPlatformProcess::Sleep(0.05f);

	FString result = FString::Printf(
		TEXT("%s#%s#%s#%d"),
		*FString::FromInt((int)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_DEFAULT),
		*inmateNumber,
		*roundNum,
		(int)averEyeFocus
	);

	SendThread::GetInst()->SetMessage((uint8)PROTOCOL_MAIN::ProgramSetting, (uint8)PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE, result);
}
