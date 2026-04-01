#define _WINSOCK_DEPRECATED_NO_WARNINGS // 최신 VC++ 컴파일 시 경고 방지
#pragma comment(lib, "ws2_32")

#include "DataPacket.h"
#include "math.h"
#include "mysql.h"
#include "CheckSerialPort.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1111"
#define DB_NAME "mojdatabase"

#define Quarter 0.75
#define TwoQuarters 0.5
#define ThreeQuarters 0.25

#define OneThird 2
#define TwoThird 4
#define ThreeThird 6

void err_quit(char* msg);
void err_display(char* msg);

DWORD WINAPI ProcessClient(LPVOID arg);

void SendMsg(Player_Socket playerData, SendType _type);
void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData);

inline string GetBoolToString(bool isA) { return isA ? "true" : "false"; }
vector<string> split(string input, char dlim);
DWORD WINAPI SerialThread(LPVOID lpParam);

int TotalPlayerNumber = 0;

int TotalTrashCount = 0;
int CurrTrashCount = 0;

int wallPlayerCount = 1;
int floorPlayerCount = 0;

int LoadPNGCount = 0;
int EffectSoundCheckCount = 0;

int wallCheckCount = 0;
int floorCheckCount = 0;

bool IsLow = true;
bool IsMiddle = true;
bool IsHigh = true;

int fishCount = 0;

int coralSensorCount = 0;

int tempFishNum = 0;
int tempGuideNum = 0;

bool IsKelpToVillage = false;

int testNum = 0;

int sideType = -1;

string currLevelName;

vector<SocketInfo*> SocketInfoList;
map<SOCKET, SceneData> WallClients;
map<SOCKET, SceneData> FloorClients;
map<SOCKET, SceneData> DisplayClients;
SceneData CMS_Client;
vector<SOCKET> WallBackGroundClients;
vector<SOCKET> FloorBackGroundClients;

void err_quit(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// 소켓 함수 오류 출력
void err_display(char* msg)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    cout << "[%s] %s" << msg << (char*)lpMsgBuf << endl;
    LocalFree(lpMsgBuf);
}

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
    SOCKET client_sock = (SOCKET)arg;
    int retval;
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE + 1];

    Player_Socket recvPlayerData;
    string castBuffer;
    bool IsGameOut = false;
    int tempCount = 0;



    // 클라이언트 정보 얻기
    addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);

    CRITICAL_SECTION cs;

    InitializeCriticalSection(&cs);

    while (1) {
        EnterCriticalSection(&cs);
        //cout << "Recv" << endl;
        // 데이터 받기
        retval = recv(client_sock, buf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0)
            break;

        //Player_Socket recvPlayerData;
        //string castBuffer;
        // 
        // 받은 데이터 출력
        buf[retval] = '\0';
        recvPlayerData = (Player_Socket&)buf;
        castBuffer = recvPlayerData.Buffer;

        //cout << endl;
        //cout << "RecvCheck : " << recvPlayerData.Main << " , " << recvPlayerData.Sub << " , " << recvPlayerData.Buffer << endl;
        //cout << endl;

        switch (recvPlayerData.Main)
        {

        default:
            break;
        }
        //if (castBuffer != "")
        //    datas.push(QueueData(client_sock, recvPlayerData));

        LeaveCriticalSection(&cs);

        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }
        //recvPlayerData = Player_Socket();
        //memset(buf, 0x0, sizeof(BUFSIZE));
    }

    //EnterCriticalSection(&cs);

    ////Player_Socket recvPlayerData;
    ////string castBuffer;

    cout << "LogOut Before" << endl;
    for (vector<SocketInfo*>::iterator iter = SocketInfoList.begin(); iter != SocketInfoList.end(); iter++)
    {
        if ((*iter)->sock == client_sock)
        {
            cout << "Check Sock Map" << endl;
            SocketInfoList.erase(iter);

            SceneData clientIter =  DisplayClients[client_sock];
            if (clientIter.SceneType == "Wall")
            {
                WallClients.erase(client_sock);
                //wallPlayerCount--;
                //wallCheckCount--;

                //if(wallPlayerCount < 0)
                //    wallPlayerCount = 0;
            }
            else
            {
                FloorClients.erase(client_sock);
                //floorPlayerCount--;
                //floorCheckCount--;

                //if (floorPlayerCount < 0)
                //    floorPlayerCount = 0;
            }

            DisplayClients.erase(client_sock);

            break;
        }
    }

    if (DisplayClients.size() == 0)
    {
        wallCheckCount = 0;
        floorCheckCount = 0;

        //wallPlayerCount = 2;
        //floorPlayerCount = 2;
    }

    //cout << SocketInfoList.size() << endl;
    cout << "LogOut After" << endl;

    cout << "wallPlayerCount : " << wallPlayerCount << endl;
    cout << "floorPlayerCount : " << floorPlayerCount << endl;
    cout << "wallCheckCount : " << wallCheckCount << endl;
    cout << "floorCheckCount : " << floorCheckCount << endl;

    cout << "WallClients.size() : " << WallClients.size() << endl;
    cout << "FloorClients.size() : " << FloorClients.size() << endl;
    cout << "DisplayClients.size() : " << DisplayClients.size() << endl;

    //PlayerDefaultDataList.erase(client_sock);
    closesocket(client_sock);
    //LeaveCriticalSection(&cs);

    printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
        inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    //DeleteCriticalSection(&cs);

    return 0;
}

void SendMsg(Player_Socket playerData, SendType _type)
{
    CRITICAL_SECTION cs;

    InitializeCriticalSection(&cs);

    switch (_type)
    {
    case SendType_All:
    {
        char buf[BUFSIZE + 1];
        for (auto iter = DisplayClients.begin(); iter != DisplayClients.end(); iter++)
        {
            EnterCriticalSection(&cs);
            strcpy_s(buf, (char*)&playerData);
            send(iter->second.socket, buf, BUFSIZE, 0);
            LeaveCriticalSection(&cs);
            cout << "Send!!" << endl;
        }
        cout << "AllTypeSendEnd" << endl;
    }
        break;
    case SendType_Wall:
    {
        char buf[BUFSIZE + 1];
        for (auto iter = WallClients.begin(); iter != WallClients.end(); iter++)
        {
            EnterCriticalSection(&cs);
            strcpy_s(buf, (char*)&playerData);
            send(iter->second.socket, buf, BUFSIZE, 0);
            LeaveCriticalSection(&cs);
        }
    }
        break;
    case SendType_Floor:
    {
        char buf[BUFSIZE + 1];
        for (auto iter = FloorClients.begin(); iter != FloorClients.end(); iter++)
        {
            EnterCriticalSection(&cs);
            strcpy_s(buf, (char*)&playerData);
            send(iter->second.socket, buf, BUFSIZE, 0);
            LeaveCriticalSection(&cs);
        }
    }
        break;
    case SendType_BG_Wall:
    {
        char buf[BUFSIZE + 1];
        for (int i = 0; i < WallBackGroundClients.size(); i++)
        {
            EnterCriticalSection(&cs);
            strcpy_s(buf, (char*)&playerData);
            send(WallBackGroundClients[i], buf, BUFSIZE, 0);
            LeaveCriticalSection(&cs);
        }
    }
        break;
    case SendType_BG_Floor:
    {
        char buf[BUFSIZE + 1];
        for (int i = 0; i < FloorBackGroundClients.size(); i++)
        {
            EnterCriticalSection(&cs);
            strcpy_s(buf, (char*)&playerData);
            send(FloorBackGroundClients[i], buf, BUFSIZE, 0);
            LeaveCriticalSection(&cs);
        }
    }
        break;
    default:
        break;
    }

    DeleteCriticalSection(&cs);

    cout << "SendEnd" << endl;
}

void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData)
{
    char buf[BUFSIZE];

    //EnterCriticalSection(&cs);
    strcpy(buf, (char*)&playerData);
    send(socketInfo, buf, BUFSIZE, 0);
    //LeaveCriticalSection(&cs);
}

vector<string> split(string input, char dlim)
{
    vector<string> result;	// 분리한 문자열들을 저장하는 vector

    stringstream ss;		// stringstream 객체인 ss 선언
    string stringBuffer;	// stringstream에서 문자열 자를 때마다 임시로 저장하는 변수
    ss.str(input);			// ss에 문자열 삽입

    // ss에서 dlim 직전까지의 문자열을 잘라서 stringBuffer에 저장. ss가 빌 때까지 실행
    while (getline(ss, stringBuffer, dlim))
    {
        result.push_back(stringBuffer);	// stringBuffer에 저장된 값을 result에 push_back
    }

    return result;
}

DWORD WINAPI SerialThread(LPVOID lpParam)
{
    cout << "Test" << endl;
    CSerialPort _serial;

    _serial.ClosePort();

    if (_serial.OpenPort())
    {
        //::OutputDebugString(_T("Succeded to Open Port\n"));
        _serial.ConfigurePort(CBR_9600, 8, FALSE, NOPARITY, ONESTOPBIT);

        // Timeout configuration
        _serial.SetCommunicationTimeouts(0, 0, 0, 0, 0);

        // memory buffer
        BYTE* pByte = new BYTE[2];

        CRITICAL_SECTION cs;

        Player_Socket playerData;

        string castBuffer;

        InitializeCriticalSection(&cs);

        while (1)
        {
            if (_serial.ReadByte(pByte, 2))
            {
                EnterCriticalSection(&cs);

                coralSensorCount++;
                
                cout << "Test : " << testNum++ << endl;

                LeaveCriticalSection(&cs);
            }
            Sleep(1); // CPU 점유 방지
        }
        delete[] pByte;
    }

    //InitializeCriticalSection(&cs);

    _serial.ClosePort();
    return 0;
}

void CustomMysqlInit()
{
    //MYSQL* conn;
    //MYSQL_RES* res;
    //MYSQL_ROW* row;

    //conn = mysql_init(NULL);
}

int main()
{
    int retval;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW* row;

    conn = mysql_init(NULL);

    //HANDLE hSerialThread = CreateThread(NULL, 0, SerialThread, NULL, 0, NULL);
    //if (hSerialThread == NULL) {
    //    printf("시리얼 스레드 생성 실패\n");
    //}

    // socket()
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    // 데이터 통신에 사용할 변수
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;
    HANDLE hThread;

    while (1) {
        // accept()
        addrlen = sizeof(clientaddr);
        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            err_display("accept()");
            break;
        }

        SocketInfo* socketInfo = new SocketInfo();
        socketInfo->sock = client_sock;
        memcpy(&socketInfo->clientAddr, &clientaddr, addrlen);
        socketInfo->client_imei = SocketInfoList.size();

        SocketInfoList.push_back(socketInfo);

        // 접속한 클라이언트 정보 출력
        printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
            inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        // 스레드 생성
        hThread = CreateThread(NULL, 0, ProcessClient,
            (LPVOID)client_sock, 0, NULL);
        if (hThread == NULL) { closesocket(client_sock); }
        else { CloseHandle(hThread); }
    }
    
}