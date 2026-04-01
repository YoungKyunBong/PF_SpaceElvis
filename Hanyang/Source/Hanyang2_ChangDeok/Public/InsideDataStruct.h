// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InsideDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FMTNATEXTTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	FMTNATEXTTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KOR_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ENG_Text;
};

USTRUCT(BlueprintType)
struct FMTNAMETAGTEXTTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTNAMETAGTEXTTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KOR_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ENG_Text;
};

USTRUCT(BlueprintType)
struct FMTSoundTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTSoundTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* KOR_SD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ENG_SD;
};

USTRUCT(BlueprintType)
struct FMTTextureTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTTextureTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Korea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Usa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Japan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* CN;
};