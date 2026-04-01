// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/SendThread.h"
#include "../../Public/Server/SocketManager.h"
#include "../../Public/Server/SendDataBox.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include "stringapiset.h"
#endif
#include "Containers/StringConv.h"

SendThread* SendThread::Instance = nullptr;

SendThread::SendThread()
{
	Thread = nullptr;
	bRun = true;
	sendMessage.Empty();
}

SendThread::~SendThread()
{
}

bool SendThread::Init()
{
	return true;
}

uint32 SendThread::Run()
{
	while (StopTaskCounter.GetValue() == 0 && bRun)
	{
		if (SocketManager::GetInst() != nullptr)
		{
			PACKET data;
			if (SendDataBox::GetInst()->Data_DeQueue(data))
			{
				int32 sent;

				UE_LOG(LogTemp, Warning, TEXT("SendCheck"));

				UE_LOG(LogTemp, Warning, TEXT("SendData             Data : %s"), *StringToFString(std::string(data.Buffer).c_str()));

				SocketManager::GetInst()->getSocket()->Send(reinterpret_cast<const uint8*>(&data), MAX_BUFFER, sent);
			}

			if (!SocketManager::GetInst()->IsConnected())
			{
				SocketManager::GetInst()->SendMessageCount = 0;
			}
		}
		else
			break;
	}
	return 0;
}

void SendThread::Stop()
{
	StopTaskCounter.Increment();
	bRun = false;
}

inline std::string SendThread::ToStdStringFromANSI(const FString& src, int codepage)
{
	if (src.IsEmpty()) return {};

#if PLATFORM_WINDOWS
	// Windows: 지정 코드페이지(없으면 CP_ACP)로 변환
	const wchar_t* w = *src;
	const int n = src.Len();
	const UINT cp = codepage ? codepage : CP_ACP;

	const int need = ::WideCharToMultiByte(cp, 0, w, n, nullptr, 0, nullptr, nullptr);
	std::string out; out.resize(need > 0 ? need : 0);
	if (need > 0)
		::WideCharToMultiByte(cp, 0, w, n, out.data(), need, nullptr, nullptr);
	return out;
#else
	// Android 등 비윈도우: UTF-8로 내보냄 (ANSI/CP949 개념 없음)
	FTCHARToUTF8 utf8(*src);
	return std::string(utf8.Get(), utf8.Length());
#endif
}

void SendThread::BuildTextPacket(PACKET& out, const FString& Text)
{
	FTCHARToUTF8 conv(*Text);
	const int32 N = conv.Length();

	FMemory::Memcpy(out.Buffer, conv.Get(), N);
}

void SendThread::MakeThread()
{
	if (Thread != nullptr && Thread->GetThreadName().Contains("SendThread"))
	{
		bRun = true;
	}
	else
	{
		Thread = FRunnableThread::Create(this, TEXT("SendThread"), 0, TPri_BelowNormal);
		bRun = (nullptr != Thread);
	}

	SocketManager::GetInst()->bSendConnected = true;
}

void SendThread::StopListen(bool bReset)
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
		SendDataBox::GetInst()->ClearQueue();
	}
}

void SendThread::SetMessage(uint8 main, uint8 sub, int none)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage = FString::FromInt(none);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FText test)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(test.ToString());

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FString num)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(num);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, FString text1, FString text2)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(text1 + "#" + text2);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}

void SendThread::SetMessage(uint8 main, uint8 sub, int type, FString prisonerNum, FString data)
{
	PACKET sendPacket;

	sendPacket.Main = main;
	sendPacket.Sub = sub;

	sendMessage.Append(FString::FromInt(type) + "#" + prisonerNum + "#" + data);

	//BuildTextPacket(sendPacket, sendMessage);

	strcpy(sendPacket.Buffer, std::string(TCHAR_TO_UTF8(*sendMessage)).c_str());

	SendDataBox::GetInst()->Data_Enqueue(sendPacket);

	sendMessage = "";
}
