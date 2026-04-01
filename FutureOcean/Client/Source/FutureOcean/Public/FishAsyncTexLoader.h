

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FishAsyncTexLoader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FFishTexLoaded,         /* 이름            */
	UTexture2D*, Texture,   /* 1) 로드된 텍스처 */
	FName, TagName,    /* 2) 물고기 Tag    */
	FString, Error);     /* 3) 오류 메시지   */

UCLASS()
class FUTUREOCEAN_API UFishAsyncTexLoader : public UObject
{

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static UFishAsyncTexLoader* LoadTextureAsync(
		UObject* WorldContext,
		const FString& PngPath,
		const FName& InTagName);

	UPROPERTY(BlueprintAssignable)
	FFishTexLoaded OnLoaded;
	UFUNCTION()
	void Cancel() { bCanceled = true; }
private:
	UFUNCTION()
	void Start(const FString& Path);
	UFUNCTION()
	void DecodeOnWorker();
	UFUNCTION()
	void CreateTextureOnGameThread();

	
	FString SourcePath;	
	FName TagName;	
	TArray64<uint8> RawRGBA;	
	int32 W = 0, H = 0;
	UPROPERTY()
	bool bCanceled = false;
};
