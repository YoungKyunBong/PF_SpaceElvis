// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/ProcessThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/RecvDataBox.h"

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
							case (uint8)PROTOCOL_MAIN::InfoMovie:
							{
								InfoMovie(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::CleaningOcean:
							{
								CleaningOcean(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::CoralForest:
							{
								CoralForest(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::KelpForest:
							{
								KelpForest(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::OceanVillage:
							{
								OceanVillage(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::CamouFlageFish:
							{
								CamouFlageFish(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::LuminaryFish:
							{
								LuminaryFish(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::PlayEffectSound:
							{
								PlayEffectSound(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::ChangeLevelEnv:
							{
								ChangeEnv(packet.Sub, castBuffer);
							}
							break;
							case (uint8)PROTOCOL_MAIN::LoadData:
							{
								LoadData(packet.Sub, castBuffer);
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

//bool ProcessThread::ProcessMessage()
//{
//	TArray<uint8> ReceiveBuffer;
//
//	if (!RecvDataBox::GetInst()->CheckEmpty())
//	{
//		if (bRun)
//		{
//			TArray<uint8> ReceiveBufferGT;
//			ReceiveBufferGT.Append(ReceiveBuffer);
//			AsyncTask(ENamedThreads::GameThread, [&, ReceiveBufferGT]()
//				{
//					PACKET data;
//					if (RecvDataBox::GetInst()->Data_DeQueue(data))
//					{
//						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
//						if (data.Buffer != NULL && bRun)
//						{
//							FString RecvCastBuffer = StringToFString(std::string(data.Buffer).c_str());
//							std::string castBuffer = std::string(data.Buffer).c_str();
//
//							switch (data.Main)
//							{
//							case (uint8)PROTOCOL_MAIN::InfoMovie:
//							{
//								InfoMovie(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::CleaningOcean:
//							{
//								CleaningOcean(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::CoralForest:
//							{
//								CoralForest(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::KelpForest:
//							{
//								KelpForest(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::OceanVillage:
//							{
//								OceanVillage(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::CamouFlageFish:
//							{
//								CamouFlageFish(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::LuminaryFish:
//							{
//								LuminaryFish(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::PlayEffectSound:
//							{
//								PlayEffectSound(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::ChangeLevelEnv:
//							{
//								ChangeEnv(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::LoadData:
//							{
//								LoadData(data.Sub, castBuffer);
//							}
//							break;
//							case (uint8)PROTOCOL_MAIN::CMS_Controller:
//							{
//								CmsController(data.Sub, castBuffer);
//							}
//							break;
//							default:
//								break;
//							}
//						}
//					}
//				});
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

void ProcessThread::InfoMovie(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_INFOMOVIE::InfoMovieLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		infoMovieBindingData.Binding_MovieLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_INFOMOVIE::InfoMovieEnd:
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("InitTimer"));
		infoMovieBindingData.Binding_InfoMovieEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::CleaningOcean(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_CLEANING::CleaningLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		cleaningOceanBindingData.Binding_CleaningLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::WallSpawnWhale:
	{
		std::stringstream ss;
		int type;

		ss.str(CastBuffer);
		ss >> type;

		cleaningOceanBindingData.Binding_WallSpawnWhale(SIDE_TYPE(type));
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::ChangeWhaleDirection:
	{
		cleaningOceanBindingData.Binding_ChangeWhaleDirection();
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::WallWhaleSpawnEnd:
	{
		cleaningOceanBindingData.Binding_WallSpawnWhaleEnd();
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::PlayWhaleSound:
	{
		std::stringstream ss;
		int type;

		ss.str(CastBuffer);
		ss >> type;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));

		cleaningOceanBindingData.Binding_PlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE(type));
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::FloorSpawnWhale:
	{
		std::stringstream ss;
		int type;
		std::string isA;

		ss.str(CastBuffer);
		ss >> type >> isA;

		cleaningOceanBindingData.Binding_FloorSpawnWhale(SIDE_TYPE(type), StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_CLEANING::CleaningOceanEnd:
	{
		cleaningOceanBindingData.Binding_CleaningOceanEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::CoralForest(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_CORAL::CoralLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		coralForestBindingData.Binding_CoralLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_CORAL::CoralOverlap:
	{
		std::stringstream ss;
		int type;

		ss.str(CastBuffer);
		ss >> type;

		coralForestBindingData.Binding_CoralOverlap(CORAL_TYPE(type));
	}
	break;
	case (uint8)PROTOCOLSUB_CORAL::CoralWhiteSwitch:
	{
		coralForestBindingData.Binding_CoralWhieSwitch();
	}
	break;
	case (uint8)PROTOCOLSUB_CORAL::CoralEnd:
	{
		coralForestBindingData.Binding_CoralEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::KelpForest(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_KELP::KelpLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		kelpForestBindingData.Binding_KelpLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_KELP::OilCount:
	{
		std::stringstream ss;
		int32 count;

		ss.str(CastBuffer);
		ss >> count;

		kelpForestBindingData.Binding_OilCount(count);
	}
	break;
	case (uint8)PROTOCOLSUB_KELP::OilOverlap:
	{
		std::stringstream ss;
		int32 count;

		ss.str(CastBuffer);
		ss >> count;

		kelpForestBindingData.Binding_OilOverlap(count);
	}
	break;
	case (uint8)PROTOCOLSUB_KELP::KelpLevelPlaySequence:
	{
		kelpForestBindingData.Binding_KelpLevelPlaySequence();
	}
	break;
	case (uint8)PROTOCOLSUB_KELP::OilEnd:
	{
		kelpForestBindingData.Binding_OilEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::OceanVillage(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_OceanVillage::OceanVillageLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		oceanVillageBindingData.Binding_OceanVillageLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_OceanVillage::GuideActorTargetChange:
	{
		std::stringstream ss;
		int32 guideActorNum;
		int32 targetActorNum;

		ss.str(CastBuffer);
		ss >> guideActorNum >> targetActorNum;

		oceanVillageBindingData.Binding_GuideActorTargetChange(guideActorNum, targetActorNum);
	}
	break;
	case (uint8)PROTOCOLSUB_OceanVillage::FishActorTargetChange:
	{
		std::stringstream ss;
		int32 fishActorNum;
		int32 guideActorNum;
		int32 IsFirst;

		ss.str(CastBuffer);
		ss >> fishActorNum >> guideActorNum >> IsFirst;

		oceanVillageBindingData.Binding_FishActorTargetChange(fishActorNum, guideActorNum, (IsFirst == 0) ? true : false);
	}
	break;
	case (uint8)PROTOCOLSUB_OceanVillage::FishTransform:
	{
		std::stringstream ss;
		int32 fishActorNum;
		FTransform transform;
		FVector pos;
		FRotator rot;
		FVector scale;

		ss.str(CastBuffer);
		ss >> fishActorNum >> pos.X >> pos.Y >> pos.Z >> rot.Roll >> rot.Pitch >> rot.Yaw >> scale.X >> scale.Y >> scale.Z;

		transform.SetLocation(pos);
		transform.SetRotation(rot.Quaternion());
		transform.SetScale3D(scale);

		oceanVillageBindingData.Binding_FishTransform(fishActorNum, transform);
	}
	break;
	default:
		break;
	}
}

void ProcessThread::CamouFlageFish(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_CamouFlageFish::CamouFlageFishLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		camouFishBindingData.Binding_CamouFlageFishLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_CamouFlageFish::CamouFishEnd:
	{
		camouFishBindingData.Binding_CamouFishEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::LuminaryFish(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_LuminaryFish::LuminaryFishLevelLoadingEnd:
	{
		std::stringstream ss;
		std::string isA;

		ss.str(CastBuffer);
		ss >> isA;

		luminaryFishBindingData.Binding_LuminaryFishLevelLoadingEnd(StringToFString(isA).ToBool());
	}
	break;
	case (uint8)PROTOCOLSUB_LuminaryFish::LumiFishEnd:
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("luminaryFishBindingData"));
		luminaryFishBindingData.Binding_LumiFishEnd();
	}
	break;
	default:
		break;
	}
}

void ProcessThread::PlayEffectSound(uint8 Sub, std::string CastBuffer)
{
	std::stringstream ss;
	int type;

	ss.str(CastBuffer);
	ss >> type;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
	playEffectSoundBindingData.Binding_PlayEffectSound(EFFECT_SOUND_TYPE(type));
}

void ProcessThread::ChangeEnv(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_ChangeLevelEnv::OceanCleanChange:
		changeEnvBindingData.Binding_OceanCleanChange();
		break;
	case (uint8)PROTOCOLSUB_ChangeLevelEnv::PlayTimeOutEvent:
		changeEnvBindingData.Binding_PlayTimeOutEvent();
		break;
	default:
		break;
	}
}

void ProcessThread::LoadData(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_LOADDATA::LoadPNG:
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SkipStep"));
		loadBindingData.Binding_LoadPNG();
		break;
	default:
		break;
	}
}

void ProcessThread::CmsController(uint8 Sub, std::string CastBuffer)
{
	switch (Sub)
	{
	case (uint8)PROTOCOLSUB_CMS::Play:
		cmsBindingData.Binding_CmsControllerStart();
		break;
	case (uint8)PROTOCOLSUB_CMS::Stop:
		cmsBindingData.Binding_CmsControllerStop();
		break;
	case (uint8)PROTOCOLSUB_CMS::Skip:
		cmsBindingData.Binding_CmsControllerSkip();
		break;
	case (uint8)PROTOCOLSUB_CMS::Reset:
	{
		std::stringstream ss;
		int type;

		ss.str(CastBuffer);
		ss >> type;

		cmsBindingData.Binding_CmsControllerReset(RESET_TYPE(type));
	}
	break;
	case (uint8)PROTOCOLSUB_CMS::NewPlayerLevelReset:
	{
		std::stringstream ss;
		std::string levelName;

		ss.str(CastBuffer);
		ss >> levelName;

		cmsBindingData.Binding_CmsControllerNewPlayer(StringToFString(levelName));
	}
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
