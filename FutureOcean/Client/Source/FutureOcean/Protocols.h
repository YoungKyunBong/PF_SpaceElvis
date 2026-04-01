#pragma once
#include "CoreMinimal.h"
#include "Protocols.generated.h"

#define MAX_BUFFER 32
#define LOCAL_IP "127.0.0.1"				
#define LOCAL_PORT 9000

#define SAFE_DELETE(p) if(nullptr!=p){delete p; p=nullptr;}

UENUM()
enum class CMS_PlayType : uint8
{
	step1, step2,
};

//<<--------------------------------------------------------------------------------------------------------------------------------------------- 게임 분류 타입

UENUM(BlueprintType)
enum class CORAL_TYPE : uint8
{
	type1, type2, type3, type4, type5, type6, type7, Count UMETA(Hidden),
};

UENUM(BlueprintType)
enum class KELP_TYPE : uint8
{
	typeAB, typeAS, typeBB, typeBS, typeCB, typeCS, typeDB, typeDS,
};

UENUM(BlueprintType)
enum class SIDE_TYPE : uint8
{
	LeftSide, RightSide,
};

UENUM(BlueprintType)
enum class WHALE_SOUND_DISTANCE_TYPE : uint8
{
	LOW, MIDDLE, HIGH, Default,
};

UENUM(BlueprintType)
enum class RESET_TYPE : uint8
{
	WorldReset, LevelReset,
};

UENUM(BlueprintType)
enum class SOUND_TYPE : uint8
{
	Narr, BGM, Effect,
};

UENUM(BlueprintType)
enum class ClientNodeType : uint8
{
	Node0, Node1,
};

UENUM(BlueprintType)
enum class EFFECT_SOUND_TYPE : uint8
{
	SoundType0, SoundType1, SoundType2, SoundType3,
};

UENUM(BlueprintType)
enum class Lv_Sq_Type : uint8
{
	IntroType, OutroSucessType, OutroFailType, InteractionType, Cms_Type,
};


//>>---------------------------------------------------------------------------------------------------------------------------------------------

//<<--------------------------------------------------------------------------------------------------------------------------------------------- 패킷 타입
UENUM()
enum class PROTOCOL_MAIN : uint8
{
	SetSceneType = 0x01,
	InfoMovie = 0x02,
	CleaningOcean = 0x03,
	CoralForest = 0x04,
	KelpForest = 0x05,
	OceanVillage = 0x06,
	CamouFlageFish = 0x07,
	LuminaryFish = 0x08,
	PlayEffectSound = 0x96,
	ChangeLevelEnv = 0x97,
	LoadData = 0x98,
	CMS_Controller = 0x99,
};

UENUM()
enum class PROTOCOLSUB_CMS : UINT8
{
	Play = 0x01,
	Stop = 0x02,
	Skip = 0x03,
	Reset = 0x04,
	GuideScript_InfoMovie_Start = 0x05,
	GuideScript_InfoMovie_Middle = 0x06,
	GuideScript_InfoMovie_End = 0x07,
	GuideScript_CleaningOcean = 0x08,
	GuideScript_CoralForest = 0x09,
	GuideScript_KelpForest = 0x10,
	GuideScript_OceanVillage = 0x11,
	GuideScript_CamouFlageFish = 0x12,
	GuideScript_LuminaryFish = 0x13,
	ReStartWallClients = 0x97,
	ReStartFloorClients = 0x98,
	NewPlayerLevelReset = 0x99,
};

UENUM()
enum class PROTOCOLSUB_LOADDATA : uint8
{
	LoadPNG = 0x01,
};

UENUM()
enum class PROTOCOLSUB_ChangeLevelEnv : uint8
{
	OceanCleanChange = 0x01,
	PlayTimeOutEvent = 0x02,
};

UENUM()
enum class PROTOCOLSUB_TYPE : uint8
{
	Wall = 0x01,
	Floor = 0x02,
	CMS = 0x03,
};

UENUM()
enum class PROTOCOLSUB_INFOMOVIE : uint8
{
	InfoMovieLevelLoadingEnd = 0x01,
	ChangeScript = 0x02,
	InfoMovieEnd = 0x03,
};

UENUM()
enum class PROTOCOLSUB_CLEANING : UINT8
{
	CleaningLevelLoadingEnd = 0x01,
	WallSpawnWhale = 0x02,
	ChangeWhaleDirection = 0x03,
	WallWhaleSpawnEnd = 0x04,
	PlayWhaleSound = 0x05,
	FloorSpawnWhale = 0x06,
	CleaningOceanEnd = 0x07,
};

UENUM()
enum class PROTOCOLSUB_CORAL : uint8
{
	CoralLevelLoadingEnd = 0x01,
	CoralOverlap = 0x02,
	CoralEnd = 0x03,
	CoralWhiteSwitch = 0x90,
};

UENUM()
enum class PROTOCOLSUB_KELP : uint8
{
	KelpLevelLoadingEnd = 0x01,
	OilCount = 0x02,
	OilOverlap = 0x03,
	KelpLevelPlaySequence = 0x04,
	OilEnd = 0x05,
};

UENUM()
enum class PROTOCOLSUB_OceanVillage : uint8
{
	OceanVillageLevelLoadingEnd = 0x01,
	GuideActorTargetChange = 0x02,
	FishActorTargetChange = 0x03,
	FishTransform = 0x04,
};

UENUM()
enum class PROTOCOLSUB_CamouFlageFish : uint8
{
	CamouFlageFishLevelLoadingEnd = 0x01,
	CamouFlageFishCount = 0x02,
	CamouFishFind = 0x03,
	CamouFishEnd = 0x04,
};

UENUM()
enum class PROTOCOLSUB_LuminaryFish : uint8
{
	LuminaryFishLevelLoadingEnd = 0x01,
	LumiFishCount = 0x02,
	LumiFishFind = 0x03,
	LumiFishEnd = 0x04,
};

typedef struct _tagPacket
{
	////PACKET HEADER
	uint8 Main;
	uint8 Sub;
	//uint8 EventFlag;
	//uint16 Size;
	////=====================

	char Buffer[MAX_BUFFER];
}PACKET, * PPACKET;

//>>---------------------------------------------------------------------------------------------------------------------------------------------

//<<--------------------------------------------------------------------------------------------------------------------------------------------- 바인딩 구조체

typedef struct _infoMovieBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FMovieLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE(FInfoMovieEnd);

	FMovieLevelLoadingEnd movieLevelLoadingEnd;
	FInfoMovieEnd infoMovieEnd;

	inline void Binding_MovieLevelLoadingEnd(bool isStart) { movieLevelLoadingEnd.Broadcast(isStart); }
	inline void Binding_InfoMovieEnd() { infoMovieEnd.Broadcast(); }

}InfoMovieBindingData, * PInfoMovieBindingData;

typedef struct _cleaningOceanBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FCleaningLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FWallSpawnWhale, SIDE_TYPE);
	DECLARE_MULTICAST_DELEGATE(FChangeWhaleDirection);
	DECLARE_MULTICAST_DELEGATE(FWallSpawnWhaleEnd);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayWhaleSound, WHALE_SOUND_DISTANCE_TYPE);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FFloorSpawnWhale, SIDE_TYPE, bool);
	DECLARE_MULTICAST_DELEGATE(FCleaningOceanEnd);

	FCleaningLevelLoadingEnd cleaningLevelLoadingEnd;
	FWallSpawnWhale wallSpawnWhale;
	FChangeWhaleDirection changeWhaleDirection;
	FWallSpawnWhaleEnd wallSpawnWhaleEnd;
	FPlayWhaleSound playWhaleSound;
	FFloorSpawnWhale floorSpawnWhale;
	FCleaningOceanEnd cleaningOceanEnd;

	inline void Binding_CleaningLevelLoadingEnd(bool isStart) { cleaningLevelLoadingEnd.Broadcast(isStart); }
	inline void Binding_WallSpawnWhale(SIDE_TYPE type) { wallSpawnWhale.Broadcast(type); }
	inline void Binding_ChangeWhaleDirection() { changeWhaleDirection.Broadcast(); }
	inline void Binding_WallSpawnWhaleEnd() { wallSpawnWhaleEnd.Broadcast(); }
	inline void Binding_PlayWhaleSound(WHALE_SOUND_DISTANCE_TYPE type) { playWhaleSound.Broadcast(type); }
	inline void Binding_FloorSpawnWhale(SIDE_TYPE type, bool IsSuccess) { floorSpawnWhale.Broadcast(type, IsSuccess); }
	inline void Binding_CleaningOceanEnd() { cleaningOceanEnd.Broadcast(); }
}CleaningOceanBindingData, * PCleaningOceanBindingData;

typedef struct _coralForestBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FCoralLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCoralOverlap, CORAL_TYPE);
	DECLARE_MULTICAST_DELEGATE(FCoralWhiteSwitch);
	DECLARE_MULTICAST_DELEGATE(FCoralEnd);

	FCoralLevelLoadingEnd coralLevelLoadingEnd;
	FCoralOverlap coralOverlap;
	FCoralWhiteSwitch coralWhiteSwitch;
	FCoralEnd coralEnd;

	inline void Binding_CoralLevelLoadingEnd(bool isStart) { coralLevelLoadingEnd.Broadcast(isStart); }
	inline void Binding_CoralOverlap(CORAL_TYPE coralType) { coralOverlap.Broadcast(coralType); }
	inline void Binding_CoralWhieSwitch() { coralWhiteSwitch.Broadcast(); }
	inline void Binding_CoralEnd() { coralEnd.Broadcast(); }

}CoralForestBindingData, * PCoralForestBindingData;

typedef struct _kelpForestBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FKelpLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOilCount, int32);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOilOverlap, int32);
	DECLARE_MULTICAST_DELEGATE(FKelpLevelPlaySequence);
	DECLARE_MULTICAST_DELEGATE(FOilEnd);

	FKelpLevelLoadingEnd kelpLevelLoadingEnd;
	FOilCount OilCount;
	FOilOverlap OilOverlap;
	FKelpLevelPlaySequence KelpLevelPlaySequence;
	FOilEnd OilEnd;

	inline void Binding_KelpLevelLoadingEnd(bool isA) { kelpLevelLoadingEnd.Broadcast(isA); }
	inline void Binding_OilCount(int32 count) { OilCount.Broadcast(count); }
	inline void Binding_OilOverlap(int32 cnt) { OilOverlap.Broadcast(cnt); }
	inline void Binding_KelpLevelPlaySequence() { KelpLevelPlaySequence.Broadcast(); }
	inline void Binding_OilEnd() { OilEnd.Broadcast(); }

}KelpForestBindingData, * PKelpForestBindingData;

typedef struct _OceanVillageBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOceanVillageLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FGuideActorTargetChange, int, int);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FFishActorTargetChange, int, int, bool);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FFishTransform, int, FTransform);

	FOceanVillageLevelLoadingEnd oceanVillageLevelLoadingEnd;
	FGuideActorTargetChange guideActorTargetChange;
	FFishActorTargetChange fishActorTargetChange;
	FFishTransform fishTransform;

	inline void Binding_OceanVillageLevelLoadingEnd(bool isA) { oceanVillageLevelLoadingEnd.Broadcast(isA); }
	inline void Binding_GuideActorTargetChange(int guideActorNum, int targetActorNum) { guideActorTargetChange.Broadcast(guideActorNum, targetActorNum); }
	inline void Binding_FishActorTargetChange(int fishActorNum, int guideActorNum, bool IsFirst) { fishActorTargetChange.Broadcast(fishActorNum, guideActorNum, IsFirst); }
	inline void Binding_FishTransform(int fishActorNum, FTransform transform) { fishTransform.Broadcast(fishActorNum, transform); }

}OceanVillageBindingData, * POceanVillageBindingData;

typedef struct _CamouFishBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FCamouFlageFishLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE(FCamouFishEnd);

	FCamouFlageFishLevelLoadingEnd camouFlageFishLevelLoadingEnd;
	FCamouFishEnd camouFishEnd;

	inline void Binding_CamouFlageFishLevelLoadingEnd(bool isA) { camouFlageFishLevelLoadingEnd.Broadcast(isA); }
	inline void Binding_CamouFishEnd() { camouFishEnd.Broadcast(); }
}CamouFishBindingData, * PCamouFishBindingData;

typedef struct _LuminaryFishBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FLuminaryFishLevelLoadingEnd, bool);
	DECLARE_MULTICAST_DELEGATE(FLumiFishEnd);

	FLuminaryFishLevelLoadingEnd luminaryFishLevelLoadingEnd;
	FLumiFishEnd lumiFishEnd;

	inline void Binding_LuminaryFishLevelLoadingEnd(bool isA) { luminaryFishLevelLoadingEnd.Broadcast(isA); }
	inline void Binding_LumiFishEnd() { lumiFishEnd.Broadcast(); }
}LuminaryFishBindingData, * PLuminaryFishBindingData;

typedef struct _cmsBindingData
{
	DECLARE_MULTICAST_DELEGATE(FCmsControllerStart);
	DECLARE_MULTICAST_DELEGATE(FCmsControllerStop);
	DECLARE_MULTICAST_DELEGATE(FCmsControllerSkip);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCmsControllerReset, RESET_TYPE);
	DECLARE_MULTICAST_DELEGATE_OneParam(FCmsControllerNewPlayer, FString);

	FCmsControllerStart CmsControllerStart;
	FCmsControllerStop CmsControllerStop;
	FCmsControllerSkip CmsControllerSkip;
	FCmsControllerReset CmsControllerReset;
	FCmsControllerNewPlayer CmsControllerNewPlayer;

	inline void Binding_CmsControllerStart() { CmsControllerStart.Broadcast(); }
	inline void Binding_CmsControllerStop() { CmsControllerStop.Broadcast(); }
	inline void Binding_CmsControllerSkip() { CmsControllerSkip.Broadcast(); }
	inline void Binding_CmsControllerReset(RESET_TYPE _type) { CmsControllerReset.Broadcast(_type); }
	inline void Binding_CmsControllerNewPlayer(FString _levelName) { CmsControllerNewPlayer.Broadcast(_levelName); }

}CmsBindingData, * PCmsBindingData;

typedef struct _playEffectSoundBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayEffectSound, EFFECT_SOUND_TYPE);

	FPlayEffectSound PlayEffectSound;

	inline void Binding_PlayEffectSound(EFFECT_SOUND_TYPE _type) { PlayEffectSound.Broadcast(_type); }

}PlayEffectSoundBindingData, * PPlayEffectSoundBindingData;

typedef struct _loadBindingData
{
	DECLARE_MULTICAST_DELEGATE(FLoadPNG);

	FLoadPNG LoadPNG;

	inline void Binding_LoadPNG() { LoadPNG.Broadcast(); }

}LoadBindingData, * PLoadBindingData;

typedef struct _ChangeLevelEnv
{
	DECLARE_MULTICAST_DELEGATE(FOceanCleanChange);
	DECLARE_MULTICAST_DELEGATE(FPlayTimeOutEvent);

	FOceanCleanChange OceanCleanChange;
	FPlayTimeOutEvent PlayTimeOutEvent;

	inline void Binding_OceanCleanChange() { OceanCleanChange.Broadcast(); }
	inline void Binding_PlayTimeOutEvent() { PlayTimeOutEvent.Broadcast(); }

}ChangeEnvBindingData, * PChangeEnvBindingData;

//>>---------------------------------------------------------------------------------------------------------------------------------------------
