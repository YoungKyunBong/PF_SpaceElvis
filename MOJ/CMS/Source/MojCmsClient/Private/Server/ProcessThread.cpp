// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/ProcessThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/RecvDataBox.h"
#include "Containers/StringConv.h"
#include "GenericPlatform/GenericPlatformHttp.h"

ProcessThread* ProcessThread::Instance = nullptr;

ProcessThread::ProcessThread()
{
	Thread = nullptr;
	bRun = true;
	IsSpawn = false;
}

ProcessThread::~ProcessThread()
{
}

bool ProcessThread::Init()
{
	return true;
}

uint32 ProcessThread::Run()
{
	PACKET* packetPtr = nullptr;
	while (StopTaskCounter.GetValue() == 0 && bRun)
	{
		if (!RecvDataBox::GetInst()->CheckEmpty())
		{
			while (RecvDataBox::GetInst()->Data_Dequeue(packetPtr))
			{
				PACKET packet = *packetPtr;
				delete packetPtr;
				packetPtr = nullptr;

				AsyncTask(ENamedThreads::GameThread, [this, packet]()
					{
						if (packet.Buffer != NULL)
						{
							FString RecvCastBuffer = StringToFString(std::string(packet.Buffer).c_str());
							std::string castBuffer = std::string(packet.Buffer).c_str();

							//FUTF8ToTCHAR conv(reinterpret_cast<const UTF8CHAR*>(castBuffer.c_str()), castBuffer.size());
							//FString text(conv.Length(), conv.Get());

							//// 수신 직후
							//UE_LOG(LogTemp, Warning, TEXT("[RAW HEX] %s"), *text);


							switch (packet.Main)
							{
							case (uint8)PROTOCOL_MAIN::DefaultSetting:
							{
								DefaultSetting(packet.Sub, packet.Flag, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::LoginSetting:
							{
								LoginSetting(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::InmateSetting:
							{
								InmateSetting(packet.Sub, packet.Flag, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::ProgramSetting:
							{
								ProgramSetting(packet.Sub, packet.Flag, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::LogSetting:
							{
								LogSetting(packet.Sub, packet.Flag, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::CMS_Controller:
							{
								CmsController(packet.Sub, castBuffer);
							}
							break;
							default:
								break;
							}
						}
					});
			}
		}
	}
	return 0;
}

void ProcessThread::Stop()
{
	StopTaskCounter.Increment();
	bRun = false;
}

void ProcessThread::DefaultSetting(uint8 Sub, uint8 Flag, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_DEFAULT::DEFAULT_SEARCH:
	{
		//UE_LOG(LogTemp, Warning, TEXT("DefaultSetting"));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT(" DefaultSetting")); // 화면출력

		switch (Flag)
		{
		case (uint8)DATA_FLAG::SENDING:
		{
			ListData += ToFStringFromANSI(CastBuffer);
			UE_LOG(LogTemp, Warning, TEXT("SENDING"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FGenericPlatformHttp::UrlDecode(ListData));
		}
		break;
		case (uint8)DATA_FLAG::LISTEND:
		{
			UE_LOG(LogTemp, Warning, TEXT("LISTEND"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FGenericPlatformHttp::UrlDecode(ListData));
			FString tempListData = FGenericPlatformHttp::UrlDecode(ListData);
			defaultSettingBindingData.Binding_DefaultSearch(tempListData);
			ListData = "";
		}
		break;
		default:
			break;
		}
	}
	break;
	case (uint8)PROTOCOLSUB_DEFAULT::DEFAULT_SETDATA:
	{
		defaultSettingBindingData.Binding_DefaultSetting();
	}
	break;
	default:
		break;
	}

}

void ProcessThread::LoginSetting(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_LOGIN::MANAGE_CHANGE_PW:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		loginSettingBindingData.Binding_ManageChangePW(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_LOGIN::MANAGE_CHECK_PW:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		loginSettingBindingData.Binding_ManageCheckPW(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_LOGIN::INMATE_LOGIN_CHECK:
	{
		std::stringstream ss;
		int _type;

		ss.str(CastBuffer);
		ss >> _type;

		bool isA = false;

		switch (SEND_TEXT_TYPE(_type))
		{
		case SEND_TEXT_TYPE::TYPE_TRUE:
		{
			isA = true;
		}
		break;
		case SEND_TEXT_TYPE::TYPE_FALSE:
		{
			isA = false;
		}
		break;
		default:
			break;
		}

		loginSettingBindingData.Binding_InmateLogin(isA);
	}
	break;
	default:
		break;
	}
}

void ProcessThread::InmateSetting(uint8 Sub, uint8 Flag, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_INMATE::INMATE_ADD:
	{
		std::stringstream ss;
		int _type;

		ss.str(CastBuffer);
		ss >> _type;

		inmateSettingBindingData.Binding_InmateADD(SEND_TEXT_TYPE(_type));
	}
	break;
	case (uint8)PROTOCOLSUB_INMATE::INMATE_UPDATE:
	{
		TArray<FString> datas;
		ToFStringFromANSI(CastBuffer).ParseIntoArray(datas, TEXT("#"));
		
		inmateSettingBindingData.Binding_InmateUpdate((SEND_TEXT_TYPE)FCString::Atoi(*datas[0]), datas[1]);
	}
	break;
	case (uint8)PROTOCOLSUB_INMATE::INMATE_SEARCH:
	{
		switch (Flag)
		{
		case (uint8)DATA_FLAG::SENDING:
		{
			ListData += ToFStringFromANSI(CastBuffer);
		}
		break;
		case (uint8)DATA_FLAG::LISTEND:
		{
			inmateSettingBindingData.Binding_InmateSearch(ListData);
			ListData = "";
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}

void ProcessThread::ProgramSetting(uint8 Sub, uint8 Flag, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE:
	{
		programSettingBindingData.Binding_ProgramUpdate(StringToFString(CastBuffer));
	}
	break;
	default:
		break;
	}
}

void ProcessThread::LogSetting(uint8 Sub, uint8 Flag, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_LOG::LOG_SEARCH:
	{
		switch (Flag)
		{
		case (uint8)DATA_FLAG::SENDING:
		{
			UE_LOG(LogTemp, Warning, TEXT("LogSending"));
			ListData += ToFStringFromANSI(CastBuffer);
		}
		break;
		case (uint8)DATA_FLAG::LISTEND:
		{
			UE_LOG(LogTemp, Warning, TEXT("LogSendEnd"));
			FString tempListData = FGenericPlatformHttp::UrlDecode(ListData);
			logSettingBindingData.Binding_LogSearch(tempListData);
			ListData = "";
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}

void ProcessThread::CmsController(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_CMS::HeadTracking:
	{
		std::stringstream ss;
		int _trackingNum;

		ss.str(CastBuffer);
		ss >> _trackingNum;

		cmsBindingData.Binding_TrackingNumber(_trackingNum);
	}
		break;
	case (uint8)PROTOCOLSUB_CMS::Temp_NextRound:
		cmsBindingData.Binding_CmsNextRound();
		break;
	case (uint8)PROTOCOLSUB_CMS::TutoEnd:
		cmsBindingData.Binding_TutoEnd();
		break;	
	case (uint8)PROTOCOLSUB_CMS::RoundEnd:
		cmsBindingData.Binding_RoundEnd();
		break;
	default:
		break;
	}
}

void ProcessThread::MakeThread()
{
	if (Thread != nullptr && Thread->GetThreadName().Contains("ProcessThread"))
	{
		bRun = true;
	}
	else
	{
		Thread = FRunnableThread::Create(this, TEXT("ProcessThread"), 0, TPri_BelowNormal);
		bRun = (nullptr != Thread);
	}
}

void ProcessThread::StopListen(bool bReset)
{
	if (!bReset)
	{
		Stop();
		if (Thread != nullptr)
		{
			Thread->WaitForCompletion();
		}
		delete Instance;
		Instance = NULL;
	}
}

FString ProcessThread::ToFStringFromANSI(const std::string castBuffer)
{
	FUTF8ToTCHAR conv(reinterpret_cast<const UTF8CHAR*>(castBuffer.c_str()), castBuffer.size());
	FString text(conv.Length(), conv.Get());

	return text;
}
