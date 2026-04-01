#pragma once
#include "CoreMinimal.h"
//#include "Protocols.generated.h"

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
enum class SEND_TEXT_TYPE : uint8
{
    TYPE_TRUE = 1,
    TYPE_FALSE = 2,
    TYPE_SAME = 3,
};

UENUM()
enum class INMATE_UPDATE_TYPE : uint8
{
    INMATE_STATUS_CODE = 0x01,
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
enum class TREATMENT_UPDATE_TYPE : uint8
{
    UPDATE_TREATMENT_CONSENTTEST = 0x01,
    UPDATE_TREATMENT_PRETEST = 0x02,
    UPDATE_TREATMENT_POSTTEST = 0x03,
    UPDATE_TREATMENT_LASTCHECK = 0x04,
    UPDATE_TREATMENT_STARTAT = 0x05,
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
    DefaultSetting = 0x07,
    ConnectClientSetting = 0x098,
    CMS_Controller = 0x99,
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
enum class PROTOCOLSUB_DEFAULT : uint8
{
    DEFAULT_SEARCH = 0x01,
    DEFAULT_SETDATA = 0x02,
};

UENUM()
enum class PROTOCOLSUB_LOGIN : uint8
{
    MANAGE_CHANGE_PW = 0x01,
    MANAGE_CHECK_PW = 0x02,
    INMATE_LOGIN_CHECK = 0x03,
};

UENUM()
enum class PROTOCOLSUB_INMATE : uint8
{
    INMATE_ADD = 0x01,
    INMATE_DELETE = 0x02,
    INMATE_UPDATE = 0x03,
    INMATE_SEARCH = 0x04,
};

UENUM()
enum class PROTOCOLSUB_CODE : uint8
{
    CODE_ADD = 0x01,
    CODE_DELETE = 0x02,
    CODE_UPDATE = 0x03,
    CODE_SEARCH = 0x04,
};

UENUM()
enum class PROTOCOLSUB_TREATMENT : uint8
{
    TREATMENT_ADD = 0x01,
    TREATMENT_DELETE = 0x02,
    TREATMENT_UPDATE = 0x03,
    TREATMENT_SEARCH = 0x04,
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
enum class PROTOCOLSUB_LOG : uint8
{
    LOG_ADD = 0x01,
    LOG_DELETE = 0x02,
    LOG_UPDATE = 0x03,
    LOG_SEARCH = 0x04,
};

UENUM()
enum class DATA_FLAG : uint8
{
    SENDING = 0x01,
    LISTEND = 0x02,
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

//<<--------------------------------------------------------------------------------------------------------------------------------------------- 바인딩 구조체

typedef struct _loginSettingBindingData
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FManageChangePW, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FManageCheckPW, bool);
	DECLARE_MULTICAST_DELEGATE_OneParam(FInmateLogin, bool);

    FManageChangePW manageChangePW;
    FManageCheckPW manageCheckPW;
    FInmateLogin inmateLogin;

	inline void Binding_ManageChangePW(bool isSuccess) { manageChangePW.Broadcast(isSuccess); }
	inline void Binding_ManageCheckPW(bool isSuccess) { manageCheckPW.Broadcast(isSuccess); }
	inline void Binding_InmateLogin(bool isSuccess) { inmateLogin.Broadcast(isSuccess); }

}LoginSettingBindingData, * PLoginSettingBindingData;

typedef struct _inmateSettingBindingData
{
    DECLARE_MULTICAST_DELEGATE_OneParam(FInmateADD, SEND_TEXT_TYPE);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FInmateUpdate, SEND_TEXT_TYPE, FString);
    DECLARE_MULTICAST_DELEGATE_OneParam(FInmateSearch, FString);

    FInmateADD inmateADD;
    FInmateUpdate inmateUpdate;
    FInmateSearch inmateSearch;

    inline void Binding_InmateADD(SEND_TEXT_TYPE printType) { inmateADD.Broadcast(printType); }
    inline void Binding_InmateUpdate(SEND_TEXT_TYPE type, FString data) { inmateUpdate.Broadcast(type, data); }
    inline void Binding_InmateSearch(FString data) { inmateSearch.Broadcast(data); }

}InmateSettingBindingData, * PInmateSettingBindingData;

typedef struct _programSettingBindingData
{
    DECLARE_MULTICAST_DELEGATE_OneParam(FProgramUpdate, FString);

    FProgramUpdate ProgramUpdate;

    inline void Binding_ProgramUpdate(FString data) { ProgramUpdate.Broadcast(data); }

}ProgramSettingBindingData, * PProgramSettingBindingData;

typedef struct _defaultSettingBindingData
{
    DECLARE_MULTICAST_DELEGATE_OneParam(FDefaultSearch, FString);
    DECLARE_MULTICAST_DELEGATE(FDefaultSetting);

    FDefaultSearch defaultSearch;
    FDefaultSetting defaultSetting;

    inline void Binding_DefaultSearch(FString data) { defaultSearch.Broadcast(data); UE_LOG(LogTemp, Warning, TEXT("defaultSearch.Broadcast")); }
    inline void Binding_DefaultSetting() { defaultSetting.Broadcast(); UE_LOG(LogTemp, Warning, TEXT("defaultSetting.Broadcast")); }

}DefaultSettingBindingData, * PDefaultSettingBindingData;

typedef struct _logSettingBindingData
{
    DECLARE_MULTICAST_DELEGATE_OneParam(FLogSearch, FString);

    FLogSearch logSearch;

    inline void Binding_LogSearch(FString data) { logSearch.Broadcast(data); }

}LogSettingBindingData, * PLogSettingBindingData;

typedef struct _cmsBindingData
{
    DECLARE_MULTICAST_DELEGATE_OneParam(FTrackingNumber, int);
    DECLARE_MULTICAST_DELEGATE(FCmsNextRound);
    DECLARE_MULTICAST_DELEGATE(FTutoEnd);
    DECLARE_MULTICAST_DELEGATE(FRoundEnd);

    FTrackingNumber TrackingNumber;
    FCmsNextRound CmsNextRound;
    FTutoEnd TutoEnd;
    FRoundEnd RoundEnd;

    inline void Binding_TrackingNumber(int num) { TrackingNumber.Broadcast(num); }
    inline void Binding_CmsNextRound() { CmsNextRound.Broadcast(); }
    inline void Binding_TutoEnd() { TutoEnd.Broadcast(); }
    inline void Binding_RoundEnd() { RoundEnd.Broadcast(); }

}CmsBindingData, * PCmsBindingData;

//>>---------------------------------------------------------------------------------------------------------------------------------------------
