// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InsideDataStruct.h"
#include "Engine/GameInstance.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "GameManager.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ENationType : uint8
{
	EN_Korea			UMETA(DisplayName = "Korea"),
	EN_English		UMETA(DisplayName = "English"),
	EN_Japan			UMETA(DisplayName = "Japan")
};

DECLARE_MULTICAST_DELEGATE_OneParam(FHttpDownloadCheck, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FHttpDownloadEnd, bool);
DECLARE_MULTICAST_DELEGATE(FUnZipEndState);

UCLASS()
class HANYANG2_CHANGDEOK_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Instance")
	void SetNation(ENationType nation);

	UFUNCTION(BlueprintCallable, Category = "Instance")
	ENationType GetNation();

	ENationType m_eNationType;

	TArray<UTexture2D*> LoadInvenTexture;

	TArray<int> LoadIvenIndex;
	//inside DataTable
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* InsideNaTextData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* InsideNtTextData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* InsideSoundData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		class UDataTable* InsideTextureData;


	TArray<FMTNATEXTTable> NaTextArray;
	TArray<FMTNAMETAGTEXTTable> NtTextArray;
	TArray<FMTSoundTable> SoundArray;
	TArray<FMTTextureTable> TextureArray;

public:
	UFUNCTION(BlueprintCallable)
		void SetSoundData();
	UFUNCTION(BlueprintCallable)
		void SetNaTextData();
	UFUNCTION(BlueprintCallable)
		void SetNtTextData();
	UFUNCTION(BlueprintCallable)
		void SetTextureData();

	UFUNCTION(BlueprintCallable)
		USoundBase* GetSound(FString _SoundID);
	UFUNCTION(BlueprintCallable)
		FString GetNaText(FString _TextID);
	UFUNCTION(BlueprintCallable)
		FString GetNtText(FString _TextID);
	UFUNCTION(BlueprintCallable)
		UTexture2D* GetTexture(FString _TextureID);

public:
	UFUNCTION(BlueprintCallable, Category = "save")
	void FileSaveString(FString SaveTextB, FString FileNameB);

	UFUNCTION(BlueprintCallable)
	void OpenApp(FString FilePath = "");

	UPROPERTY(BlueprintReadOnly)
	bool IsFirst;

protected:
	UFUNCTION(BlueprintCallable, Category = "save")
	void FileLoadString(FString FileNameA);
//http
public:
	UFUNCTION(BlueprintCallable)
	void C_Init();

	UFUNCTION(BlueprintNativeEvent)
	void UnZip();
	UFUNCTION(BlueprintCallable)
	virtual void UnZip_Implementation() {};

	UFUNCTION(BlueprintCallable)
	void UnZipComplete();

	UPROPERTY(BlueprintReadOnly)
	FString C_ArchivePath;

	UPROPERTY(BlueprintReadOnly)
	FString C_EntryName;

	UPROPERTY(BlueprintReadOnly)
	FString C_DirectoryPath;

	float Percent;

	void SetHttpData(FString _Path, FString _Name);

	UFUNCTION(BlueprintCallable, DisplayName = "ExecuteDownload", Category = "HttpDownloader")
	void ExecuteDownload();

	TSharedPtr<IHttpRequest> HttpRequest;

	FHttpDownloadCheck HttpDownloadCheck;

	FHttpDownloadEnd HttpDownloadEnd;

	FUnZipEndState UnZipEndState;

	void CancelDownLoad();
private:
	FHttpModule* HttpModule;

	void HttpRequestProgressDelegate(FHttpRequestPtr RequestPtr, int32 SendBytes, int32 RecvBytes);

	void HttpRequestFinishedDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void GetDownLoadURL();

private:
	UPROPERTY()
	FString SourceURL;

	UPROPERTY()
	FString Path;

	UPROPERTY()
	FString Name;

	bool IsDownLoadCancel;

	TMap<FString, FString> LevelsURL;
};
