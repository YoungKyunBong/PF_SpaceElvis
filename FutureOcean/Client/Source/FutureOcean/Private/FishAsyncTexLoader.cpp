#include "FishAsyncTexLoader.h"
#include "Async/Async.h"
#include "IImageWrapperModule.h"          
#include "IImageWrapper.h" 
#include "TextureResource.h"          // FTexture2DResourceMemScoped
#include "Rendering/Texture2DResource.h" // FUpdateTextureRegion2D
#include "RenderUtils.h" 

UFishAsyncTexLoader* UFishAsyncTexLoader::LoadTextureAsync(
    UObject* WC, const FString& Png, const FName& InTag)
{
    auto* Obj = NewObject<UFishAsyncTexLoader>(WC);
    if (!Obj->IsRooted())// GC 보호
    {
        Obj->AddToRoot();
    }             
    Obj->TagName = InTag;   // 보관
    Obj->Start(Png);
    return Obj;
}

void UFishAsyncTexLoader::Start(const FString& Png)
{
    SourcePath = Png;
    Async(EAsyncExecution::ThreadPool,
        [this]()               // 캡처
        {
            if (bCanceled || !IsValid(GetOuter())) return;
            DecodeOnWorker();  // 실제 작업
        });
}

void UFishAsyncTexLoader::DecodeOnWorker()
{
    if (bCanceled || !IsValid(GetOuter())) return;

    if (!FFileHelper::LoadFileToArray(RawRGBA, *SourcePath))
    {
        OnLoaded.Broadcast(nullptr, NAME_None, TEXT("ReadFail")); return;
    }

    IImageWrapperModule& Wrp = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
    auto Wrapper = Wrp.CreateImageWrapper(EImageFormat::PNG);
    if (!Wrapper->SetCompressed(RawRGBA.GetData(), RawRGBA.Num()))
    {
        OnLoaded.Broadcast(nullptr, NAME_None,TEXT("PNGCorrupt")); return;
    }

    W = static_cast<int32>(Wrapper->GetWidth());
    H = static_cast<int32>(Wrapper->GetHeight());

    TArray64<uint8> OutPtr;
    Wrapper->GetRaw(ERGBFormat::BGRA, 8, OutPtr);
    RawRGBA = MoveTemp(OutPtr);   // move → 추가 복사 방지

    Async(EAsyncExecution::TaskGraphMainThread, [this]
        {
            if (bCanceled || !IsValid(GetOuter())) return;
            CreateTextureOnGameThread();
        });
}

void UFishAsyncTexLoader::CreateTextureOnGameThread()
{
    if (bCanceled || !IsValid(GetOuter())) return;
    /* 1) 빈 UObject 텍스처 생성(메타데이터만) */
    UTexture2D* Tex = UTexture2D::CreateTransient(W, H, PF_B8G8R8A8);

    Tex->CompressionSettings = TC_Default;
    Tex->MipGenSettings = TMGS_FromTextureGroup;   //  자동 밉    
    Tex->NeverStream = true;    
    Tex->LODBias = 5;
    Tex->SRGB = true;
    
    /* 2) BulkData 잠금  Raw 복사 */
    FTexture2DMipMap& Mip0 = Tex->GetPlatformData()->Mips[0];
    void* Dest = Mip0.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(Dest, RawRGBA.GetData(), RawRGBA.Num());
    Mip0.BulkData.Unlock();          //  여기서 BulkData 메모리는 UE 소유   

    /* 3) RHI 리소스 생성 */
    Tex->UpdateResource();   
   
    OnLoaded.Broadcast(Tex, TagName, TEXT(""));
    RemoveFromRoot();        // GC 해제  
}
