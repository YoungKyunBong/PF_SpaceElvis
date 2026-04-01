// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
//테스트

void UGameManager::SetNation(ENationType nation)
{
	switch (nation)
	{
	case ENationType::EN_Korea:
		m_eNationType = ENationType::EN_Korea;
		break;
	case ENationType::EN_English:
		m_eNationType = ENationType::EN_English;
		break;
	case ENationType::EN_Japan:
		m_eNationType = ENationType::EN_Japan;
		break;
	default:
		m_eNationType = ENationType::EN_Korea;
		break;
	}
}

ENationType UGameManager::GetNation()
{
	return m_eNationType;
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

	SoundArray.Empty();
	for (int i = 0; i < OutArray.Num(); ++i)
	{
		TextureArray.Add(*OutArray[i]);
	}
}

USoundBase* UGameManager::GetSound(FString _SoundID)
{
	_SoundID = _SoundID.RightChop(2);
	int Index = FCString::Atoi(*_SoundID);

	if (Index > SoundArray.Num())
		return nullptr;

	switch (m_eNationType)
	{
	case ENationType::EN_Korea:
		return SoundArray[Index].KOR_SD;
		break;

	case ENationType::EN_English:
		return SoundArray[Index].ENG_SD;
		break;
	default:
		return SoundArray[Index].KOR_SD;
	}
	USoundBase* SoundData = nullptr;
}

FString UGameManager::GetNaText(FString _TextID)
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

	switch (m_eNationType)
	{
	case ENationType::EN_Korea:
		return NaTextArray[Index].KOR_Text;

	case ENationType::EN_English:
		return NaTextArray[Index].ENG_Text;
	}

	return NaTextArray[Index].KOR_Text;
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
	case ENationType::EN_Korea:
		return NtTextArray[Index].KOR_Text;

	case ENationType::EN_English:
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
			case ENationType::EN_Korea:
				TextureData = TextureArray[i].Korea;
				break;

			case ENationType::EN_Japan:
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

void UGameManager::FileSaveString(FString SaveTextB, FString FileNameB)
{
	IsFirst = SaveTextB.ToBool();
	FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectDir() + FileNameB));
}

void UGameManager::OpenApp(FString FilePath)
{
	if (FilePath.IsEmpty())
	{
		FString SaveDirectory = *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		FString FileName = FString("Path") + FString(".txt");
		FString FolderName = FString("LoadFile");
		FString AbsoluteFilePath_2 = SaveDirectory + FolderName;

		bool AllowOverwriting = true;
		TArray<FString> TempArrayName;
		TempArrayName.Empty();
		TArray<FString> TempTextName;
		TempTextName.Empty();
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
		{
			FString AbsoluteFilePath = AbsoluteFilePath_2 + "/" + FileName;

			if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
			{
				FFileHelper::LoadFileToStringArray(TempArrayName, *AbsoluteFilePath);

				TempTextName = TArray<FString>(TempArrayName);

				if (TempArrayName.Num() != 0)
				{
					FPlatformProcess::CreateProc(*TempTextName[0], nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
				}
			}
		}
	}
	else
	{
		FPlatformProcess::CreateProc(*FilePath, nullptr, true, false, false, nullptr, 0, nullptr, nullptr);
	}
}

void UGameManager::FileLoadString(FString FileNameA)
{
	FString SaveTextA;
	FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectDir() + FileNameA));

	IsFirst = SaveTextA.ToBool();
}

void UGameManager::C_Init()
{
	HttpModule = &FHttpModule::Get();
	HttpRequest = HttpModule->CreateRequest();

	C_EntryName = "Windows";

	GetDownLoadURL();
}

void UGameManager::UnZipComplete()
{
	Percent = 0;
	UnZipEndState.Broadcast();
}

void UGameManager::SetHttpData(FString _Path, FString _Name)
{
	if (HttpRequest->GetStatus() == EHttpRequestStatus::Processing)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlaySound!")));
	}
	else
	{
		Path = _Path;
		Name = _Name;

		C_ArchivePath = _Path + _Name;

		FString tempText;
		tempText = _Name.Replace(TEXT(".zip"), TEXT(" "));
		tempText.RemoveSpacesInline();
		C_DirectoryPath = _Path + tempText;

		tempText.RemoveAt(0);
		SourceURL = LevelsURL[tempText];

		IsDownLoadCancel = false;

		HttpRequest->SetURL(SourceURL);

		HttpRequest->ProcessRequest();
	}
}

void UGameManager::ExecuteDownload()
{
	HttpRequest->OnRequestProgress().BindUObject(this, &UGameManager::HttpRequestProgressDelegate);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UGameManager::HttpRequestFinishedDelegate);
}

void UGameManager::CancelDownLoad()
{
	IsDownLoadCancel = true;
	HttpRequest->CancelRequest();
}

void UGameManager::HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RecvBytes)
{
	int32 TotalSize = RequestPtr->GetResponse()->GetContentLength();
	Percent = (float)RecvBytes / TotalSize;
	HttpDownloadCheck.Broadcast(Percent);
}

void UGameManager::HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//FString BasePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + Path;
	//FString FileSavePath = Path + Name;		// 경로를 지정 한다.
	FString FileSavePath = Path + "/Temp.zip";		// 경로를 지정 한다.

	// Save File.
	if (Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode())) {
		// 해당 플렛폼에 맞는 File 클래스 만들기.
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		// Dir tree 를 만든다.
		PlatformFile.CreateDirectoryTree(*Path);
		IFileHandle* FileHandler = PlatformFile.OpenWrite(*FileSavePath);

		if (FileHandler) {
			// 파일을 새로 쓴다.
			FileHandler->Write(Response->GetContent().GetData(), Response->GetContentLength());
			FileHandler->Flush();		// 저장.

			delete FileHandler;
			bWasSuccessful = true;
		}
		else {
			bWasSuccessful = false;
		}
	}
	else {
		bWasSuccessful = false;
	}

	
	HttpDownloadEnd.Broadcast(IsDownLoadCancel);
	if (!IsDownLoadCancel)
		UnZip();
	
	//OnDownloadFinishedCallback.Broadcast(bWasSuccessful, FileSavePath);
}

void UGameManager::GetDownLoadURL()
{
	FString SaveDirectory = *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString FileName = FString("DownLoadURLPath") + FString(".txt");
	FString FolderName = FString("LoadFile");
	FString AbsoluteFilePath_2 = SaveDirectory + FolderName;

	TArray<FString> TempArrayName;
	TempArrayName.Empty();
	TArray<FString> TempTextName;
	TempTextName.Empty();

	FString AbsoluteFilePath = AbsoluteFilePath_2 + "/" + FileName;

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*AbsoluteFilePath))
	{
		FFileHelper::LoadFileToStringArray(TempArrayName, *AbsoluteFilePath);

		TempTextName = TArray<FString>(TempArrayName);

		if (TempArrayName.Num() != 0)
		{
			for (int i = 0; i < TempTextName.Num(); i++)
			{
				FString key;
				FString value;
				TempTextName[i].Split(",", &key, &value);
				LevelsURL.Add(key, value);
			}
		}
	}
}
