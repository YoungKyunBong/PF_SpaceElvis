
#include "Manager/InfoMovie/Wall_InfoMovieManager.h"
#include "Manager/GameManager.h"
#include "GameMode/DefaultGameMode.h"
#include "actors/StepActor/MoviePlayerActor.h"
#include "Common/UdpSocketBuilder.h"

void AWall_InfoMovieManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UDPSocket)
	{
		UDPSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
	}
}

void AWall_InfoMovieManager::C_Init()
{
	Super::C_Init();

	MoviePlayerActor->CustomInit(this);

	//GetGameMode()->Call_WidgetSwitcherIndex(1);

	GetGameManager()->RecvMovieLevelLoadingEnd.AddUFunction(this, FName("RecvLevelLoadingEnd"));

	GetGameManager()->Send_MovieLevelLoadingEnd();

	////UDP 테스트 소켓
	//{
	//	UDPSocket = FUdpSocketBuilder(TEXT("MyUDPSocket"))
	//		.AsNonBlocking()
	//		.AsReusable()
	//		.WithBroadcast()   // 브로드캐스트가 필요 없으면 제거 가능
	//		.Build();

	//	FIPv4Address Addr;
	//	FIPv4Address::Parse(TEXT("192.168.50.120"), Addr);
	//	RemoteEndpoint = FIPv4Endpoint(Addr, 10025);

	//	//UDPSocket->Connect(*RemoteEndpoint.ToInternetAddr());
	//}

	constexpr TCHAR  LocalName[] = TEXT("InfoMovie_UDP");
	constexpr int32  LocalPort = 30000;

	// 0.0.0.0:30000
	const FIPv4Endpoint LocalEndpoint(FIPv4Address::Any, LocalPort);

	UDPSocket = FUdpSocketBuilder(LocalName)
		.AsReusable()
		.BoundToEndpoint(LocalEndpoint)
		.WithSendBufferSize(2 * 1024 * 1024)
		.WithReceiveBufferSize(2 * 1024 * 1024)
		.Build();

	// Remote 192.168.50.120:10025
	FIPv4Address RemoteAddr;
	ensure(FIPv4Address::Parse(TEXT("192.168.50.120"), RemoteAddr));
	RemoteEndpoint = FIPv4Endpoint(RemoteAddr, 10025);

	//SendUDP(TEXT("play\r\n"));// 영상 플레이 시작
	//SendUDP(TEXT("706C61790D0A"), /*bHex=*/true);
	//if (GetGameManager()->GetNodeType() == ClientNodeType::Node0) {

	//	SendUDP(TEXT("show\r\n")); // 엣지 블랜딩 실행
	//	SendUDP(TEXT("start\r\n")); // 미디어 싱크 프로그램 실행
	//}
}

bool AWall_InfoMovieManager::HexStringToBytes(const FString& HexStr, TArray<uint8>& OutBytes)
{
	FString Clean;
	Clean.Reserve(HexStr.Len());

	// 공백·탭 제거 + 0x 접두어 무시
	for (TCHAR Ch : HexStr)
	{
		if (!FChar::IsWhitespace(Ch) && Ch != 'x' && Ch != 'X')
		{
			Clean.AppendChar(Ch);
		}
	}

	// 반드시 짝수 길이여야 함
	if (Clean.Len() % 2 != 0) { return false; }

	const int32 ByteCount = Clean.Len() / 2;
	OutBytes.Reset(ByteCount);

	for (int32 i = 0; i < Clean.Len(); i += 2)
	{
		const FString ByteStr = Clean.Mid(i, 2);
		uint8 Byte = (uint8)FCString::Strtoi(*ByteStr, nullptr, 16);
		OutBytes.Add(Byte);
	}
	return true;
}

void AWall_InfoMovieManager::RecvLevelLoadingEnd(bool isStart)
{

	if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
	{
		FTimerHandle StartHandle;
		float startdelay = 2.0f;
		// (1) 3초 후 “show”
		GetWorld()->GetTimerManager().SetTimer(
			StartHandle,
			[this]()                
			{
				SendUDP(TEXT("start\r\n"));
				// (2) “show” 를 보낸 뒤 2초 후 “start”
				FTimerHandle ShowHandle;
				float showdelay = 5.0f;
				GetWorld()->GetTimerManager().SetTimer(
					ShowHandle,
					[this]()
					{
						SendUDP(TEXT("show\r\n"));

					},
					showdelay,
					false);
			},
			startdelay,
			false);
	}
	
	//SetCmsIsStart(isStart);
}

void AWall_InfoMovieManager::SetCmsIsStart(bool isStart)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	if (isStart)
	{
		MoviePlayerActor->CMS_Start();
		if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
		{
			//SendUDP("play"); // 영상 플레이 시작
			if (isFirst)
			{
				SendUDP(TEXT("play\r\n"));
				isFirst = false;
			}
			else
				SendUDP(TEXT("resume\r\n"));
		}
	}
	else
	{
		MoviePlayerActor->CMS_Stop();
		if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
			SendUDP(TEXT("pause\r\n")); // 영상 플레이 중지
	}
	//isStart ? MoviePlayerActor->CMS_Start() : MoviePlayerActor->CMS_Stop();
	//switch (cms_PlayType)
	//{
	//case CMS_PlayType::step1:
	//{
	//	RecvLevelEnd();
	//	//GetGameMode()->Call_WidgetSwitcherIndex(0);
	//	cms_PlayType = CMS_PlayType::step2;
	//}
	//	break;
	//case CMS_PlayType::step2:
	//{
	//	//RecvLevelEnd();
	//	GetGameMode()->Call_StepManager_CmsIsStart(0, isStart);
	//}
	//	break;
	//default:
	//	break;
	//}
}

void AWall_InfoMovieManager::SendInfoMovieLevelEnd()
{
	GetGameManager()->Send_InfoMovieEnd();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("InitTimer"));
}

void AWall_InfoMovieManager::SendChangeScript(PROTOCOLSUB_CMS scriptType)
{
	GetGameManager()->Send_ChangeScript(scriptType);
}

void AWall_InfoMovieManager::RecvLevelEnd()
{
	MoviePlayerActor->CheckSkip();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RecvLevelEnd"));
}

void AWall_InfoMovieManager::RecvInfoMovieLevelEnd()
{
	if (GetGameManager()->GetNodeType() == ClientNodeType::Node0)
	{
		SendUDP(TEXT("kill\r\n")); // 미디어 싱크 프로그램 종료
	}

	GetGameMode()->Call_StepManager_SkipStep(0);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("InfoMovieEnd"));
}

void AWall_InfoMovieManager::SendUDP(const FString& Data, bool bHex)
{
	/*FString Message = _data;
	FTCHARToUTF8 Converter(*Message);
	int32 BytesSent = 0;

	UDPSocket->Send(
			(uint8*)Converter.Get(),
			Converter.Length(),
			BytesSent

	);*/
	// 3) 보낼 데이터 준비
	/*if (!UDPSocket) { return; }

	FTCHARToUTF8  Utf8(*_data);
	int32         BytesSent = 0;

	const bool bOk = UDPSocket->SendTo(
		(uint8*)Utf8.Get(), Utf8.Length(),
		BytesSent,
		*RemoteEndpoint.ToInternetAddr());	*/
	if (!UDPSocket) { return; }

	TArray<uint8> Payload;
	if (bHex)
	{
		if (!HexStringToBytes(Data, Payload))
		{
			UE_LOG(LogTemp, Error, TEXT("Hex parse failed: %s"), *Data);
			return;
		}
	}
	else
	{
		FTCHARToUTF8 Utf8(*Data);
		Payload.Append((uint8*)Utf8.Get(), Utf8.Length());
	}

	int32 BytesSent = 0;
	const bool bOk = UDPSocket->SendTo(
		Payload.GetData(), Payload.Num(),
		BytesSent,
		*RemoteEndpoint.ToInternetAddr());
}
