// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/ProcessThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/RecvDataBox.h"
#include "Containers/StringConv.h"

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

							switch (packet.Main)
							{
							case (uint8)PROTOCOL_MAIN::ProgramSetting:
							{
								ProgramSetting(packet.Sub, castBuffer);
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

void ProcessThread::ProgramSetting(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (UINT8)PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE:
	{
		programSettingBindingData.Binding_RequestMovieNum(StringToFString(CastBuffer));
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
	case (uint8)PROTOCOLSUB_CMS::Start:
	{
		
		cmsBindingData.Binding_CmsControllerStart(StringToFString(CastBuffer));
	}
		break;
	case (uint8)PROTOCOLSUB_CMS::Play:
		cmsBindingData.Binding_CmsControllerPlay();
		break;
	case (uint8)PROTOCOLSUB_CMS::Stop:
		cmsBindingData.Binding_CmsControllerStop();
		break;
	case (uint8)PROTOCOLSUB_CMS::Pause:
		cmsBindingData.Binding_CmsControllerPause();
		break;
	case (uint8)PROTOCOLSUB_CMS::SectionMovement:
		cmsBindingData.Binding_CmsMovieNum(FCString::Atoi(*StringToFString(CastBuffer)));
		break;
	case (uint8)PROTOCOLSUB_CMS::Temp_NextRound:
		cmsBindingData.Binding_CmsNextRound();
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
