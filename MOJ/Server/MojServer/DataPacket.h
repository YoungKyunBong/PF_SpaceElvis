#pragma once
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <mutex>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>
#include <thread>
#include <sstream>
#include <chrono>
#include <ws2tcpip.h>
#include <mysql.h>
#include <cstring>
#include <ctime>

using namespace std;

#pragma comment(lib, "libmysql.lib")

//#define DB_HOST "192.168.0.46"
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1111"
#define DB_NAME "mojdatabase"

#define INMATE_CREATETABLE_DEFAULT_NAME "programprogress"

#define CODE_INSERTTABLE_DEFAULT_COLUMNS "CATEGORY, CODE_KEY, CODE_VALUE, CODE_DESCRIPTION"
#define LOG_INSERTTABLE_DEFAULT_COLUMNS "PROGRAM_PROGRESS_ID, HEART_RATE, LOG_EVENT"
#define TREATMENT_INSERTTABLE_DEFAULT_COLUMNS "CRIME_TYPE_CODE, SITUATION_CODE, SESSION_NUMBER"
#define PROGRAM_INSERTTABLE_DEFAULT_COLUMNS "INMATE_ID, TREATMENT_PROGRAM_ID, PLAY_ROUND"

#define SERVERPORT 9000
#define BUFSIZE    2048
#define READ 1
#define WRITE 0

#define _WINSOCK_DEPRECATED_NO_WARNINGS

enum PROTOCOLSUB_DEVICE_TYPE : UINT8
{
    MovieClientA = 0x01,
    MovieClientB = 0x02,
    CmsClinetA = 0x03,
    CmsClinetB = 0x04,
};

enum SEND_TEXT_TYPE : int
{
    TYPE_TRUE = 1,
    TYPE_FALSE = 2,
    TYPE_SAME = 3,
};

enum SEARCH_DIRECTION_TYPE : UINT8
{
    VERTICAL_TYPE = 0x01,
    HORIZON_TYPE = 0x02,
};

enum QUERY_RETURN_TYPE : UINT8
{
    RETURN_NONE = 0x01,
    RETURN_ERROR = 0x02,
    RETURN_SUCCESS = 0x03,
};

enum SEACHTYPE : UINT8
{
    SEACH_ALL = 0x01,
    SEACH_COLUMN = 0x02,
    SEACH_COLUMN_WHERE = 0x03,
    SEACH_ONEDATA_TABLE = 0x04,
};

enum INMATE_UPDATE_TYPE : UINT8
{
    INMATE_STATUS_CODE = 0x01,
};

enum PROGRAM_UPDATE_TYPE : UINT8
{
    UPDATE_PROGRAM_DEFAULT = 0x01,
    UPDATE_PROGRAM_ROUND_REMARKS = 0x02,
    UPDATE_PROGRAM_ROUND_HEARTRATE = 0x03,
    UPDATE_PROGRAM_ROUND_HEARTRATE_MOVIE_NUM = 0x04,
    UPDATE_PROGRAM_ROUND_REQUEST_MOVIE_NUM = 0x05,
    UPDATE_PROGRAM_ROUND_HEARTRATE_MARK = 0x06,
};

enum TREATMENT_UPDATE_TYPE : UINT8
{
    UPDATE_TREATMENT_CONSENTTEST = 0x01,
    UPDATE_TREATMENT_PRETEST = 0x02,
    UPDATE_TREATMENT_POSTTEST = 0x03,
    UPDATE_TREATMENT_LASTCHECK = 0x04,
    UPDATE_TREATMENT_STARTAT = 0x05,
};

enum PROGRAM_SEARCH_TYPE : UINT8
{
    PROGRAM_SEARCH_MANAGE = 0x01,
    PROGRAM_SEARCH_PLAY_DATA = 0x02,
    PROGRAM_SEARCH_ADD_CHECK = 0x03,
};

enum PROGRAM_ADD_CHECK_TYPE : UINT8
{
    PROGRAM_ADD_PLAYROUND = 0x01,
    PROGRAM_ADD_NEWCRIME = 0x02,
    PROGRAM_ADD_NONE = 0x03,
    PROGRAM_ADD_NEWINMATE = 0x04,
};

enum DATA_FLAG : UINT8
{
    SENDING = 0x01,
    LISTEND = 0x02,
};

struct SocketInfo
{
    SOCKET sock;
    SOCKADDR_IN clientAddr;
    int client_imei = -1;
};

struct Player_Socket
{
    UINT8 Main;
    UINT8 Sub;
    UINT8 Flag;

    char Buffer[BUFSIZE];
    //byte krBuffer[KR_BUFSIZE];

    Player_Socket()
    {
        Main = 0;
        Sub = 0;
        memset(this, 0x0, sizeof(struct Player_Socket));
    }
};

struct ClientData
{
    string SceneType;
    SOCKET socket;
};


enum PROTOCOL_MAIN : UINT8
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

enum PROTOCOLSUB_CMS : UINT8
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

enum PROTOCOLSUB_DEFAULT : UINT8
{
    DEFAULT_SEARCH = 0x01,
    DEFAULT_SETDATA = 0x02,
};

enum PROTOCOLSUB_LOGIN : UINT8
{
    MANAGE_CHANGE_PW = 0x01,
    MANAGE_CHECK_PW = 0x02,
    INMATE_LOGIN_CHECK = 0x03,
};

enum PROTOCOLSUB_INMATE : UINT8
{
    INMATE_ADD = 0x01,
    INMATE_DELETE = 0x02,
    INMATE_UPDATE = 0x03,
    INMATE_SEARCH = 0x04,
    INMATE_UPDATE_SEARCH = 0x05,
};


enum PROTOCOLSUB_CODE : UINT8
{
    CODE_ADD = 0x01,
    CODE_DELETE = 0x02,
    CODE_UPDATE = 0x03,
    CODE_SEARCH = 0x04,
};

enum PROTOCOLSUB_TREATMENT : UINT8
{
    TREATMENT_ADD = 0x01,
    TREATMENT_DELETE = 0x02,
    TREATMENT_UPDATE = 0x03,
    TREATMENT_SEARCH = 0x04,
};

enum PROTOCOLSUB_PROGRAM : UINT8
{
    PROGRAM_ADD = 0x01,
    PROGRAM_DELETE = 0x02,
    PROGRAM_UPDATE = 0x03,
    PROGRAM_SEARCH = 0x04,
};

enum PROTOCOLSUB_LOG : UINT8
{
    LOG_ADD = 0x01,
    LOG_DELETE = 0x02,
    LOG_UPDATE = 0x03,
    LOG_SEARCH = 0x04,
};