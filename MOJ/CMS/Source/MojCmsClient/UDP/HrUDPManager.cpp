#include "HrUDPManager.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "Common/UdpSocketBuilder.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HAL/RunnableThread.h"
#include "Containers/StringConv.h"
#include "Async/Async.h"

AHrUDPManager::AHrUDPManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHrUDPManager::BeginPlay()
{
    Super::BeginPlay();
    FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &AHrUDPManager::OnAppWillEnterBackground);    
    StartReceiver();
    //SendCommandToWatch(TEXT("start"));
}

void AHrUDPManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{    
    SendCommandToWatch(TEXT("stop"));
    StopReceiver();
    Super::EndPlay(EndPlayReason);	
}

void AHrUDPManager::BeginDestroy()
{
    SendCommandToWatch(TEXT("stop"));
    StopReceiver();    
    Super::BeginDestroy();
}

void AHrUDPManager::OnAppWillEnterBackground()
{
    SendCommandToWatch(TEXT("stop"));
    StopReceiver();
}

void AHrUDPManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// ==================== UDP Receive ====================
void AHrUDPManager::StartReceiver()
{
    FIPv4Address AnyAddr;
    FIPv4Address::Parse(TEXT("0.0.0.0"), AnyAddr);

    ListenSocket = FUdpSocketBuilder(TEXT("HR_UDP_Listener"))
        .AsNonBlocking()
        .AsReusable()
        .BoundToAddress(AnyAddr)
        .BoundToPort(ListenPort)
        .WithReceiveBufferSize(2 * 1024 * 1024);

    if (!ListenSocket)
    {
        UE_LOG(LogTemp, Error, TEXT("[UDP] Listen socket creation failed"));
        return;
    }

    UdpReceiver = MakeShared<FUdpSocketReceiver>(
        ListenSocket,
        FTimespan::FromMilliseconds(10),
        TEXT("HR_UDP_ReceiverThread"));

    UdpReceiver->OnDataReceived().BindUObject(this, &AHrUDPManager::OnPacketReceived);
    UdpReceiver->Start();

    UE_LOG(LogTemp, Log, TEXT("[UDP] Listening on port %d"), ListenPort);
}

void AHrUDPManager::StopReceiver()
{
    if (UdpReceiver.IsValid())
    {
        UdpReceiver->Stop();
        UdpReceiver.Reset();
    }

    if (ListenSocket)
    {
        ListenSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
        ListenSocket = nullptr;
    }
}

void AHrUDPManager::OnPacketReceived(const FArrayReaderPtr& Data, const FIPv4Endpoint& Endpoint)
{
    // bytes -> UTF-8 -> FString
    const char* Raw = reinterpret_cast<const char*>(Data->GetData());
    const int32 Len = Data->Num();
    FString JsonStr = FString(FUTF8ToTCHAR(Raw, Len));

    //UE_LOG(LogTemp, Log, TEXT("[UDP] Received from %s : %s"), *Endpoint.ToString(), *JsonStr);
    ParseHeartRateJson(JsonStr);
}

void AHrUDPManager::ParseHeartRateJson(const FString& JsonStr)
{
    TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("[UDP] JSON parse failed: %s"), *JsonStr);
        return;
    }

    const FString Type = JsonObject->GetStringField(TEXT("type"));
    if (Type != TEXT("hr"))
    {
        return;
    }

    int32 Bpm = 0;
    double TsNumber = 0.0;
    int64 TimestampMs = 0;

    if (!JsonObject->TryGetNumberField(TEXT("bpm"), Bpm))
    {
        UE_LOG(LogTemp, Warning, TEXT("[UDP] JSON missing bpm: %s"), *JsonStr);
        return;
    }

    if (JsonObject->TryGetNumberField(TEXT("ts"), TsNumber))
    {
        TimestampMs = static_cast<int64>(TsNumber);
    }

    AsyncTask(ENamedThreads::GameThread, [this, Bpm, TimestampMs]()
        {
            OnHeartRateReceived.Broadcast(Bpm, TimestampMs);
        });
}

// ==================== UDP Send ====================
bool AHrUDPManager::SendCommandToWatch(const FString& Command)
{
    FIPv4Address Addr;
    if (!FIPv4Address::Parse(WatchIP, Addr))
    {
        UE_LOG(LogTemp, Warning, TEXT("[UDP] Invalid Watch IP: %s"), *WatchIP);
        return false;
    }

    TSharedRef<FInternetAddr> DestAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    DestAddr->SetIp(Addr.Value);
    DestAddr->SetPort(WatchPort);

    FSocket* SendSocket = FUdpSocketBuilder(TEXT("HR_UDP_Sender"))
        .AsReusable()
        .AsNonBlocking()
        .WithSendBufferSize(256 * 1024);

    if (!SendSocket)
    {
        UE_LOG(LogTemp, Error, TEXT("[UDP] Send socket creation failed"));
        return false;
    }

    FTCHARToUTF8 Converter(*Command);
    const uint8* Buffer = reinterpret_cast<const uint8*>(Converter.Get());
    const int32  Length = Converter.Length();

    int32 BytesSent = 0;
    const bool bSent = SendSocket->SendTo(Buffer, Length, BytesSent, *DestAddr);

    SendSocket->Close();
    ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SendSocket);

    if (bSent && BytesSent == Length)
    {
        UE_LOG(LogTemp, Log, TEXT("[UDP] -> %s:%d :: %s"), *WatchIP, WatchPort, *Command);
        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("[UDP] Send failed (BytesSent=%d / %d)"), BytesSent, Length);
    return false;
}
