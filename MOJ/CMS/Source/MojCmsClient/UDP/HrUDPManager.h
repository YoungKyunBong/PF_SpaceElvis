#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/UdpSocketReceiver.h"       // FUdpSocketReceiver, FArrayReaderPtr
#include "Interfaces/IPv4/IPv4Endpoint.h"   // FIPv4Endpoint

#include "HrUDPManager.generated.h"

class FSocket;
// 블루프린트 바인딩 가능하도록 멀티캐스트 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHeartRateReceived, int32, BPM, int64, Timestamp);

UCLASS()
class MOJCMSCLIENT_API AHrUDPManager : public AActor
{
	GENERATED_BODY()

public:
	AHrUDPManager();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;
	UFUNCTION()
	void OnAppWillEnterBackground(); // 백그라운드 직전
	
public:
	virtual void Tick(float DeltaTime) override;

	// ===== UDP 설정 =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDP|Settings")
	FString WatchIP = TEXT("192.168.1.23");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDP|Settings")
	int32 WatchPort = 7788;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDP|Settings")
	int32 ListenPort = 7779;

	// ===== 수신 이벤트 =====
	UPROPERTY(BlueprintAssignable, Category = "UDP|Events")
	FOnHeartRateReceived OnHeartRateReceived;

	// ===== 송신 함수 =====
	UFUNCTION(BlueprintCallable, Category = "UDP|Send")	
	bool SendCommandToWatch(const FString& Command);

private:
	// 내부
	FSocket* ListenSocket = nullptr;
	TSharedPtr<FUdpSocketReceiver> UdpReceiver;

	void StartReceiver();
	void StopReceiver();

	
	void OnPacketReceived(const FArrayReaderPtr& Data, const FIPv4Endpoint& Endpoint);
	void ParseHeartRateJson(const FString& JsonStr);
};
