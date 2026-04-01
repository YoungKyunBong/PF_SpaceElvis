// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Protocols.h"
#include "../InsideDataStruct.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

#pragma region CmsBindingDatas
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecvCmsControllerStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecvCmsControllerPlayInBP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecvCmsControllerStopInBP);

DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerPlay);
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerStop);
DECLARE_MULTICAST_DELEGATE(FRecvCmsControllerPause);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecvCmsMovieClose);
DECLARE_MULTICAST_DELEGATE_OneParam(FRecvCmsMovieNum, int);
#pragma endregion

/**
 * 
 */

//UENUM(BlueprintType)
//enum class ENationType : uint8
//{
//	EN_Korea			UMETA(DisplayName = "Korea"),
//	EN_English		UMETA(DisplayName = "English"),
//	EN_Japan			UMETA(DisplayName = "Japan")
//};

UCLASS()
class MOJMOVIECLIENT_API UGameManager : public UGameInstance
{
	GENERATED_BODY()
private:
	FString ServerIP;

	void FileLoadIP();

	PROTOCOLSUB_DEVICE_TYPE DEVICE_TYPE = PROTOCOLSUB_DEVICE_TYPE::MovieClientA;

	FString inmateNumber;

	FString roundNum;

	FString movieNum = "0";

	float eyeFocusTotalCount = 0;

	float eyeFocusCorrectCount = 0;

	float averEyeFocus = 0;

	FString tutoLevel = "TutoLevel";
protected:
	UPROPERTY(EditAnyWhere)
	bool IsLocalGame;

	virtual void Init() override;
	virtual void Shutdown();

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
	USoundBase* GetSound(FString _SoundID, ENationType _type);
	UFUNCTION(BlueprintCallable)
	FString GetNaText(FString _TextID, ENationType _type);
	UFUNCTION(BlueprintCallable)
	FString GetNtText(FString _TextID);
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetTexture(FString _TextureID);

	UPROPERTY(BlueprintReadOnly)
	FString LevelName;

	void SetMovieNum(MovieSceneType _movieNum);

public:
	void Send_DeviceType();

#pragma region ProgramBindingDatas
	UFUNCTION()
	void Fuc_RecvRequestMovieNum(FString _data);
#pragma endregion

#pragma region CmsBindingDatas

	UPROPERTY(BlueprintAssignable)
	FRecvCmsControllerStart RecvCmsControllerStart;
	UPROPERTY(BlueprintAssignable)
	FRecvCmsControllerPlayInBP RecvCmsControllerPlayInBP;
	UPROPERTY(BlueprintAssignable)
	FRecvCmsControllerStopInBP RecvCmsControllerStopInBP;

	FRecvCmsControllerPlay RecvCmsControllerPlay;
	FRecvCmsControllerStop RecvCmsControllerStop;
	FRecvCmsControllerPause RecvCmsControllerPause;

	UPROPERTY(BlueprintAssignable)
	FRecvCmsMovieClose RecvCmsMovieClose;
	FRecvCmsMovieNum RecvCmsMovieNum;

	UFUNCTION()
	void Fuc_RecvCmsControllerStart(FString _data);
	UFUNCTION()
	void Fuc_RecvCmsControllerPlay();
	UFUNCTION()
	void Fuc_RecvCmsControllerStop();
	UFUNCTION()
	void Fuc_RecvCmsControllerPause();
	UFUNCTION()
	void Fuc_RecvCmsMovieNum(int num);
	
	void Send_HeadTrackingNum(int Num);
	void Send_TempNextRound();

	UFUNCTION(BlueprintCallable)
	void Send_TutoEnd();

	UFUNCTION(BlueprintCallable)
	void Send_RoundEnd();

#pragma endregion
};
