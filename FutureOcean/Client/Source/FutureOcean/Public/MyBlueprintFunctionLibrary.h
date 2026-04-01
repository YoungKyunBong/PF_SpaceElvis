

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	
	//파이썬 스크립트 실행
	UFUNCTION(BlueprintCallable)
	static void RunPythonScript(const FString& ScriptName, const FString& FolderPath, FString& OutResult, const FString& DestinationCopyFolder = "");

	UFUNCTION(BlueprintCallable)
	static void ExecuteCopyFirstJPGScript(const FString& FolderPath);
	UFUNCTION(BlueprintCallable)
	static FString ExecuteQRCodeScript(const FString& FolderPath);
	UFUNCTION(BlueprintCallable)
	static void ExecuteJPGtoPNGScript(const FString& FolderPath);
	UFUNCTION(BlueprintCallable)
	static void LoadLiveLinkPreset(const FString& PresetPath);


};
