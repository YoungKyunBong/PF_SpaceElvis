#include "MyBlueprintFunctionLibrary.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "Logging/LogMacros.h"
#include "Engine/Texture2D.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"
#include "ImageUtils.h"
#include "LiveLinkPreset.h"

/*
*   QR 코드 읽기*
*   .jpg to Texture2D
*/

void UMyBlueprintFunctionLibrary::RunPythonScript(const FString& ScriptName, const FString& FolderPath, FString& OutResult, const FString& DestinationCopyFolder)
{
	/* Set script paths
		C: / Users / SE_PC_005 / AppData / Local / Programs / Python / Python313 / -> 현장 pc경로 변경해야 함.
	*/
	//봉 TEXT("C:/Users/Kja_0070/AppData/Local/Programs/Python/Python313/");
	//박 TEXT("C:/Users/SE_PC_005/AppData/Local/Programs/Python/Python313/");
	//C:/UnrealProject/FutureOcean/pythonscript
	//107 TEXT("C:/Users/admin/AppData/Local/Programs/Python/Python313/");

	FString ExePath = TEXT("C:/Users/SE_PC_005/AppData/Local/Programs/Python/Python313/");
	FString PythonExe = FPaths::Combine(ExePath, TEXT("python.exe"));
	FString FilePath = FPaths::ProjectDir() / TEXT("pythonscript/");
	FString ScriptPath = FPaths::Combine(FilePath, ScriptName);	

	// Check if Python executable and script exist
	if (!FPaths::FileExists(PythonExe) || !FPaths::FileExists(ScriptPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Python executable or script not found: %s"), *ScriptPath);
		OutResult = TEXT("ERROR: FILE NOT FOUND");
		return;
	}

	// Pass folder path as an argument
	FString Args = FolderPath;
	//FString::Printf(TEXT("\"%s\""), *FolderPath);

	int32 ReturnCode = 0;
	FString Output;
	FString ErrorOutput;
	FString FullCommand;
	//FString FullCommand = FString::Printf(TEXT("\"%s\" %s"), *ScriptPath, *Args);

	if (DestinationCopyFolder.IsEmpty() == true)
	{
		FullCommand = FString::Printf(TEXT("\"%s\" \"%s\""), *ScriptPath, *FolderPath);
	}
	else
	{
		FullCommand = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\""), *ScriptPath, *FolderPath, *DestinationCopyFolder);
	}
	FPlatformProcess::ExecProcess(*PythonExe, *FullCommand, &ReturnCode, &Output, &ErrorOutput);

	if (ReturnCode == 0)
	{
		Output.TrimStartAndEndInline();
		UE_LOG(LogTemp, Log, TEXT("Python script executed successfully: %s"), *Output);
		OutResult = Output;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Python execution failed: %s"), *ErrorOutput);
		OutResult = TEXT("ERROR: SCRIPT FAILED");
	}
}

void UMyBlueprintFunctionLibrary::ExecuteCopyFirstJPGScript(const FString& FolderPath)
{
	FString Result;
	/* !!공유 폴더로 수정 필수 !! */
	FString DestinationCopyFolderPath = TEXT("Z:/ScanData2");
	RunPythonScript(TEXT("copy_first_jpg.py"), FolderPath, Result, DestinationCopyFolderPath);
}

FString UMyBlueprintFunctionLibrary::ExecuteQRCodeScript(const FString& FolderPath)
{
	FString Result;
	RunPythonScript(TEXT("qr_excute.py"), FolderPath, Result);
	return Result;
}

void UMyBlueprintFunctionLibrary::ExecuteJPGtoPNGScript(const FString& FolderPath)
{
	FString Result;
	RunPythonScript(TEXT("convert_jpg_to_png.py"), FolderPath, Result);
	//RunPythonScript(TEXT("convert_and_resize_jpg.py"), FolderPath, Result);
}

void UMyBlueprintFunctionLibrary::LoadLiveLinkPreset(const FString& PresetPath)
{
	//FString path = TEXT("/Game/LiveLink_Test107.LiveLink_Test107");
	ULiveLinkPreset* Preset = LoadObject<ULiveLinkPreset>(nullptr, *PresetPath);
	
	if (Preset)
	{
		Preset->ApplyToClient();
		UE_LOG(LogTemp, Error, TEXT("ApplyLiveLinkPreset"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed::ApplyLiveLinkPreset"));
	}
}



//UTexture2D* UMyBlueprintFunctionLibrary::LoadJPGFromFile(const FString& FolderPath)
//{
//    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
//
//    // 폴더 경로가 유효한지 확인
//    if (!PlatformFile.DirectoryExists(*FolderPath))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Invalid folder path: %s"), *FolderPath);
//        return nullptr;
//    }
//
//    // 폴더 내 JPG 파일 검색
//    TArray<FString> FoundFiles;
//    PlatformFile.FindFiles(FoundFiles, *FolderPath, TEXT(".jpg"));
//
//    if (FoundFiles.Num() == 0)
//    {
//        UE_LOG(LogTemp, Error, TEXT("No JPG files found in folder: %s"), *FolderPath);
//        return nullptr;
//    }
//
//    // 첫 번째 JPG 파일 선택
//    FString ImagePath = FoundFiles[0];
//
//    TArray<uint8> ImageData;
//
//    // JPG 파일을 바이너리 배열로 읽어옴
//    if (!FFileHelper::LoadFileToArray(ImageData, *ImagePath))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to read JPG file: %s"), *ImagePath);
//        return nullptr;
//    }
//
//    // IImageWrapperModule 가져오기
//    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
//
//    // JPG 데이터를 디코딩
//    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to decode JPG. The file may be corrupted or unsupported."));
//        return nullptr;
//    }
//
//    int32 Width = ImageWrapper->GetWidth();
//    int32 Height = ImageWrapper->GetHeight();
//
//    if (Width <= 0 || Height <= 0)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Invalid JPG dimensions: %d x %d"), Width, Height);
//        return nullptr;
//    }
//
//    TArray<uint8> UncompressedRGBA;
//    ERGBFormat Format = ImageWrapper->GetFormat();  // JPG 원본 포맷 확인
//
//    if (!ImageWrapper->GetRaw(Format, 8, UncompressedRGBA))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to convert JPG to RGBA. Format: %d"), static_cast<int32>(Format));
//        return nullptr;
//    }
//
//    if (UncompressedRGBA.Num() == 0)
//    {
//        UE_LOG(LogTemp, Error, TEXT("JPG decoding resulted in empty data."));
//        return nullptr;
//    }
//
//    // UTexture2D 생성
//    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
//    if (!Texture)
//    {
//        UE_LOG(LogTemp, Error, TEXT("Failed to create texture."));
//        return nullptr;
//    }
//
//    // 텍스처 데이터 적용
//    void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
//    FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
//    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
//    Texture->UpdateResource();
//    //  변환 성공 로그
//    UE_LOG(LogTemp, Log, TEXT("Successfully converted JPG: %s (Size: %d x %d)"), *ImagePath, Width, Height);
//
//    return Texture;
//}
