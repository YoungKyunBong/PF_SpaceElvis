#pragma once
#include "CoreMinimal.h"

#define MAX_BUFFER 2048
#define LOCAL_IP "127.0.0.1"
#define LOCAL_PORT 9000

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

UENUM()
enum class PROTOCOLSUB_DEVICE_TYPE : uint8
{
	MovieClientA = 0x01,
	MovieClientB = 0x02,
	CmsClinetA = 0x03,
	CmsClinetB = 0x04,
};

UENUM()
enum class PROTOCOLSUB_CMS : uint8
{
	Play = 0x01,
	Stop = 0x02,
	Skip = 0x03,
	Reset = 0x04,
	Start = 0x05,
	Pause = 0x06,
	HeadTracking = 0x07,
	Temp_NextRound = 0x08,

	SectionMovement = 0x80,
	TutoEnd = 0x90,
	RoundEnd = 0x91,
};

UENUM()
enum class DATA_FLAG : uint8
{
	SENDING = 0x01,
	LISTEND = 0x02,
};

UENUM()
enum class PROTOCOLSUB_PROGRAM : uint8
{
	PROGRAM_ADD = 0x01,
	PROGRAM_DELETE = 0x02,
	PROGRAM_UPDATE = 0x03,
	PROGRAM_SEARCH = 0x04,
};

UENUM()
enum class PROGRAM_UPDATE_TYPE : uint8
{
	UPDATE_PROGRAM_DEFAULT = 0x01,
	UPDATE_PROGRAM_ROUND_REMARKS = 0x02,
	UPDATE_PROGRAM_ROUND_HEARTRATE = 0x03,
	UPDATE_PROGRAM_ROUND_HEARTRATE_MOVIE_NUM = 0x04,
	UPDATE_PROGRAM_ROUND_REQUEST_MOVIE_NUM = 0x05,
	UPDATE_PROGRAM_ROUND_HEARTRATE_MARK = 0x06,
};

UENUM()
enum class PROTOCOL_MAIN : uint8
{
	LoginSetting = 0x01,
	InmateSetting = 0x02,
	CodeSetting = 0x03,
	TreatmentSetting = 0x04,
	ProgramSetting = 0x05,
	LogSetting = 0x06,
	ConnectClientSetting = 0x098,
	CMS_Controller = 0x99,
};

typedef struct _tagPacket
{
	////PACKET HEADER
	uint8 Main;
	uint8 Sub;
	uint8 Flag = (uint8)DATA_FLAG::LISTEND;
	//uint8 EventFlag;
	//uint16 Size;
	////=====================

	char Buffer[MAX_BUFFER];
	//BYTE krBuffer[KR_BUFSIZE];
}PACKET, * PPACKET;

typedef struct _programSettingBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FRequestMovieNum, FString);

	FRequestMovieNum RequestMovieNum;

	inline void Binding_RequestMovieNum(FString data) { RequestMovieNum.Broadcast(data); }

}ProgramSettingBindingData, * PProgramSettingBindingData;

typedef struct _cmsBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FCmsControllerStart, FString);
	DECLARE_MULTICAST_DELEGATE(FCmsControllerPlay);
	DECLARE_MULTICAST_DELEGATE(FCmsControllerStop);
	DECLARE_MULTICAST_DELEGATE(FCmsControllerPause);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCmsMovieNum, int);
	DECLARE_MULTICAST_DELEGATE(FCmsNextRound);

	FCmsControllerStart CmsControllerStart;
	FCmsControllerPlay CmsControllerPlay;
	FCmsControllerStop CmsControllerStop;
	FCmsControllerPause CmsControllerPause;

	FCmsMovieNum CmsMovieNum;
	FCmsNextRound CmsNextRound;

	inline void Binding_CmsControllerStart(FString data) { CmsControllerStart.Broadcast(data); }
	inline void Binding_CmsControllerPlay() { CmsControllerPlay.Broadcast(); }
	inline void Binding_CmsControllerStop() { CmsControllerStop.Broadcast(); }
	inline void Binding_CmsControllerPause() { CmsControllerPause.Broadcast(); }
	inline void Binding_CmsMovieNum(int num) { CmsMovieNum.Broadcast(num); }
	inline void Binding_CmsNextRound() { CmsNextRound.Broadcast(); }

}CmsBindingData, * PCmsBindingData;

UENUM(BlueprintType)
enum class MovieSceneType : uint8
{
	SceneType1 = 0,
	SceneType2 = 1,
	SceneType3 = 2,
	SceneType4 = 3,
	SceneType5 = 4,
	SceneType6 = 5,
	SceneType7 = 6,
	SceneType8 = 7,
	SceneType9 = 8,
	SceneType10 = 9,
	SceneType11 = 10,
	SceneType12 = 11,
	SceneType13 = 12,
	SceneType14 = 13,
	SceneType15 = 14,
	SceneType16 = 15,
	SceneType17 = 16,
	SceneType18 = 17,
	SceneType19 = 18,
	SceneType20 = 19,
	SceneType21 = 20,
	SceneType22 = 21,
	SceneType23 = 22,
	SceneType24 = 23,
	SceneType25 = 24,
	SceneType26 = 25,
	SceneType27 = 26,
	SceneType28 = 27,
	SceneType29 = 28,
	SceneType30 = 29,
	SceneType31 = 30,
	SceneType32 = 31,
	SceneType33 = 32,
	SceneType34 = 33,
	SceneType35 = 34,
	SceneType36 = 35,
	SceneType37 = 36,
	SceneType38 = 37,
	SceneType39 = 38,
	SceneType40 = 39,
	SceneType41 = 40,
	SceneType42 = 41,
	SceneType43 = 42,
	SceneType44 = 43,
	SceneType45 = 44,
	SceneType46 = 45,
	SceneType47 = 46,
	SceneType48 = 47,
	SceneType49 = 48,
	SceneType50 = 49,
	SceneType51 = 50,
	SceneType52 = 51,
	SceneType53 = 52,
	SceneType54 = 53,
	SceneType55 = 54,
	SceneType56 = 55,
	SceneType57 = 56,
	SceneType58 = 57,
	SceneType59 = 58,
	SceneType60 = 59,
	SceneType61 = 60,
	SceneType62 = 61,
	SceneType63 = 62,
	SceneType64 = 63,
	SceneType65 = 64,
	SceneType66 = 65,
	SceneType67 = 66,
	SceneType68 = 67,
	SceneType69 = 68,
	SceneType70 = 69,
	SceneType71 = 70,
	SceneType72 = 71,
	SceneType73 = 72,
	SceneType74 = 73,
	SceneType75 = 74,
	SceneType76 = 75,
	SceneType77 = 76,
	SceneType78 = 77,
	SceneType79 = 78,
	SceneType80 = 79,
	SceneType81 = 80,
	SceneType82 = 81,
	SceneType83 = 82,
	SceneType84 = 83,
	SceneType85 = 84,
	SceneType86 = 85,
	SceneType87 = 86,
	SceneType88 = 87,
	SceneType89 = 88,
	SceneType90 = 89,
};