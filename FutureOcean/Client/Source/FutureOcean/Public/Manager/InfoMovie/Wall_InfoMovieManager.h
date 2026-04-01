

#pragma once

#include "CoreMinimal.h"
#include "Manager/DefaultManager.h"
#include "../Protocols.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Wall_InfoMovieManager.generated.h"

/**
 * 
 */
UCLASS()
class FUTUREOCEAN_API AWall_InfoMovieManager : public ADefaultManager
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	class AMoviePlayerActor* MoviePlayerActor;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual	void C_Init() override;	
	UFUNCTION()
	static bool HexStringToBytes(const FString& HexStr, TArray<uint8>& OutBytes);

	UFUNCTION()
	void RecvLevelLoadingEnd(bool isStart);

	virtual void SetCmsIsStart(bool isStart) override;

	void SendInfoMovieLevelEnd();

	void SendChangeScript(PROTOCOLSUB_CMS changeType);

	virtual void RecvLevelEnd() override;

	virtual void RecvInfoMovieLevelEnd() override;

private:
	FSocket* UDPSocket;
	FIPv4Endpoint RemoteEndpoint;

	void SendUDP(const FString& Data, bool bHex = false);

	bool isFirst = true;
//private:
//	CMS_PlayType cms_PlayType = CMS_PlayType::step1;
};
