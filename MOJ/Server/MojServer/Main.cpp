#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "DataPacket.h"
#include "ProcessDB.h"
#include "iomanip"

vector<string> Search_PlayData_EN_Inmate_ColumnName = { "ID", "INMATE_NAME", "PRISONER_NUMBER", "BIRTH", "CRIME_CODE", "CURRICULUM_CODE", "EDU_TIME", "SITUATION_CODE", "MANAGER", "REGIST_AT", "UPDATE_AT" };
vector<string> Search_PlayData_EN_Program_ColumnName = { "ID", "INMATE_ID", "PLAY_ROUND", "EYE_FOCUS", "REMARKS", "ROUND_STATUS_CODE", "ROUND_HEART_RATE"};
vector<string> Search_PlayData_EN_Treatment_ColumnName = { "ID", "INMATE_ID", "CONSENT_TEST", "PRE_TEST", "POST_TEST", "LAST_CHECK", "START_AT", "END_AT", "PROGRAM_STATUS_CODE" };
vector<string> Search_PlayData_EN_LOG_ColumnName = { "ID", "LOG_TYPE", "LOG_TIME", "LOG_ACTOR" };

vector<string> Insert_PlayData_EN_Inmate_ColumnName = { "INMATE_NAME", "PRISONER_NUMBER", "BIRTH", "CRIME_CODE", "CURRICULUM_CODE", "EDU_TIME", "SITUATION_CODE", "MANAGER", "REGIST_AT", "UPDATE_AT" };
vector<string> Update_PlayData_EN_Inmate_ColumnName = { "INMATE_NAME", "BIRTH", "EDU_TIME", "MANAGER", "UPDATE_AT" };
vector<string> Update_PlayData_EN_Program_ColumnName = { "EYE_FOCUS", "ROUND_STATUS_CODE" };
vector<string> Update_PlayData_EN_Treatment_LastCheck_ColumnName = { "LAST_CHECK", "END_AT", "PROGRAM_STATUS_CODE" };

vector<string> Remake_PlayData_EN_One_ColumnName = { "ID", "INMATE_NAME", "PRISONER_NUMBER", "BIRTH", "CRIME_CODE", "CURRICULUM_CODE", "EDU_TIME", "SITUATION_CODE" };
vector<string> Remake_PlayData_EN_Two_ColumnName = { "START_AT", "END_AT", "PROGRAM_STATUS_CODE" };
vector<string> Remake_PlayData_EN_Three_ColumnName = { "MANAGER", "REGIST_AT", "UPDATE_AT" };
vector<string> Remake_PlayData_EN_Four_ColumnName = { "LAST_CHECK", "CONSENT_TEST", "PRE_TEST", "POST_TEST" };
vector<string> Remake_PlayData_EN_Five_ColumnName = { "PLAY_ROUND", "EYE_FOCUS", "REMARKS" };

vector<string> Search_Code_KR_ColumnName = { "ID", "코드 종류", "코드 키", "코드 값", "코드 설명" };
vector<string> Search_Inmate_KR_ColumnName = { "ID", "수형번호", "이름", "재소자 상태코드", "생성날짜", "수정날짜" };
vector<string> Search_Log_KR_ColumnName = { "ID", "교육진행정보ID", "이벤트 발생 심박수", "이벤트 발생 지점", "추가메모", "기록 시간"};
vector<string> Search_ProgramProgress_KR_ColumnName = { "ID", "제소자ID", "치료교육ID", "평균 심박수", "최대 심박수", "교육진행 상태 코드", "선택지 백업 정보", "기타 메모", "생성 날짜", "수정 날짜"};
vector<string> Search_TreatmentProgram_KR_ColumnName = { "ID", "범죄코드", "상황코드", "회기번호", "프로그램 명", "프로그램 설명", "생성 날짜", "수정 날짜"};

vector<string> Search_PlayData_EN_InmateColumnName = { "ID", "InmateName" };
vector<string> Search_PlayData_EN_TreatmentColumnName = { "CrimeCode", "SituationCode", "SessionNum" };
vector<string> Search_PlayData_EN_ProgramColumnName = { "PlayRound", "AvarHeartRate", "MaxHeartRate", "ProgramStatusCode" };
vector<string> Search_PlayData_EN_LogColumnName = { "LOG_TYPE", "LOG_TIME", "LOG_ACTOR" };

vector<string> inmateTableColumns = { "PRISONER_NUMBER", "INMATE_NAME", "STATUS_CODE" };
vector<string> codeTableColumns = { "CATEGORY", "CODE_KEY", "CODE_VALUE", "CODE_DESCRIPTION" };
vector<string> treatmentTableColumns = { "CRIME_TYPE_CODE", "SITUATION_CODE", "SESSION_NUMBER", "TITLE", "TREATMENT_DESCRIPTION" };
//vector<string> programHeartRateColumns = { "AVERAGE_HEART_RATE", "MAX_HEART_RATE" };
vector<string> programTableColumns = { "INMATE_ID", "TREATMENT_PROGRAM_ID", "PLAY_ROUND", "AVERAGE_HEART_RATE", "MAX_HEART_RATE", "PROGRESS_STATUS_CODE", "SELECTS_INTERACTION", "REMARKS" };

vector<string> programAddPlayRoundColumns = { "INMATE_ID", "TREATMENT_PROGRAM_ID", "PLAY_ROUND" };

vector<string> InmateInsertColumns = { "PRISONER_NUMBER", "INMATE_NAME", "STATUS_CODE" };

int PlayRoundDefault = 1;
int CrimeCodeMaxCount = 5;

void err_quit(const char* msg);
void err_display(const char* msg);
string CP949ToUTF8(const char* bytes, int len);
string WtoUtf8(const wstring& w);
wstring Utf8ToW(const std::string& u8);

DWORD WINAPI ProcessClient(LPVOID arg);
void ProcessDashBoardSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessLoginSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessInmateSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessCodeSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessTreatmentProgram(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessProgramProgress(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessLogProgress(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);
void ProcessConnectClientSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer);
void ProcessCmsController(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB);

void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData);
void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, vector<string> SendDatas);

vector<string> RemakeListUnderMaxBufferSize(vector<vector<string>> datas);
vector<string> SplitBuffer(string buffer, string Split);

map<SOCKET, SocketInfo*> SocketInfoList;
ClientData MovieClientDataA;
ClientData MovieClientDataB;
ClientData CmsClientDataA;
ClientData CmsClientDataB;

void err_quit(const char* msg)
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
void err_display(const char* msg)
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

std::string UrlEncodeLikeUnreal(const std::string& utf8)
{
    static const char* Hex = "0123456789ABCDEF";

    std::string out;
    out.reserve(utf8.size() * 3); // 최악의 경우 대비

    for (unsigned char c : utf8)
    {
        bool bUnreserved =
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '-' || c == '_' || c == '.' || c == '~';

        if (bUnreserved)
        {
            out.push_back((char)c);
        }
        else
        {
            out.push_back('%');
            out.push_back(Hex[c >> 4]);
            out.push_back(Hex[c & 0x0F]);
        }
    }

    return out;
}

std::string GetShortDate()
{
    time_t t = time(nullptr);
    tm now;
#ifdef _WIN32
    localtime_s(&now, &t);
#else
    localtime_r(&t, &now);
#endif

    int year = (now.tm_year + 1900) % 100; // 2025 → 25
    int month = now.tm_mon + 1;           // 0~11 → 1~12
    int day = now.tm_mday;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;

    return ss.str();
}


static inline void dump_hex(const std::string& s) {
    std::string r; char b[4];
    for (unsigned char c : s) { _snprintf_s(b, 4, "%02X ", (int)c); r += b; }
    OutputDebugStringA((r + "\n").c_str());
}

static inline void trim_ascii(string& s) {
    // 앞/뒤 공백, 탭, CR/LF 제거
    size_t a = 0, b = s.size();
    while (a < b && (s[a] == ' ' || s[a] == '\t')) ++a;
    while (b > a && (s[b - 1] == ' ' || s[b - 1] == '\t' || s[b - 1] == '\r' || s[b - 1] == '\n')) --b;
    if (a == 0 && b == s.size()) return;
    s = s.substr(a, b - a);
}

static bool IsControlOrBom(uint32_t cp) {
    return (cp < 0x20 && cp != '\t' && cp != '\n' && cp != '\r')  // 제어문자 (일부 제외)
        || cp == 0xFEFF  // BOM
        || (cp >= 0x200B && cp <= 0x200F); // ZWSP/ZWJ 등
}


std::string StripWeirdUtf8(const std::string& s) {
    // 간단 구현: UTF-8 디코드해서 필터 후 다시 UTF-8 인코드
    int wlen = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    wstring w;
    w.resize(wlen);
    wchar_t* wbuf = w.empty() ? nullptr : &w[0];
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), wbuf, wlen);

    std::wstring out; out.reserve(w.size());
    for (wchar_t ch : w) {
        uint32_t cp = (uint32_t)ch;
        if (!IsControlOrBom(cp)) out.push_back(ch);
    }

    int ulen = WideCharToMultiByte(CP_UTF8, 0, out.data(), (int)out.size(), nullptr, 0, nullptr, nullptr);
    string u;
    u.resize(ulen);
    char* buf = u.empty() ? nullptr : &u[0];
    WideCharToMultiByte(CP_UTF8, 0, out.data(), (int)out.size(), buf, ulen, nullptr, nullptr);
    return u;
}

static inline vector<string> split_by_delim(const string& s, char delim)
{
    vector<std::string> out;
    string cur;
    cur.reserve(s.size());

    for (size_t i = 0; i <= s.size(); ++i) {
        if (i == s.size() || s[i] == delim) {
            trim_ascii(cur);
            out.emplace_back(move(cur));
            cur.clear();
        }
        else {
            cur.push_back(s[i]);
        }
    }
    return out;
}

inline std::wstring FromUtf8(const char* s, int n) {
    int wlen = MultiByteToWideChar(CP_UTF8, 0, s, n, nullptr, 0);
    wstring w;
    w.resize(wlen);
    wchar_t* wbuf = w.empty() ? nullptr : &w[0];
    MultiByteToWideChar(CP_UTF8, 0, s, n, wbuf, wlen);
    return wbuf;
}

inline std::wstring FromCP949(const char* s, int n) {
    int wlen = MultiByteToWideChar(949, 0, s, n, nullptr, 0);
    wstring w;
    w.resize(wlen);
    wchar_t* wbuf = w.empty() ? nullptr : &w[0];
    MultiByteToWideChar(949, 0, s, n, wbuf, wlen);
    return wbuf;
}

string N949ToUTF8(const char* bytes, int len)
{
    if (!bytes || len <= 0) return {};

    int wlen = MultiByteToWideChar(949, 0, bytes, len, nullptr, 0);
    wstring w;
    w.resize(wlen);
    wchar_t* wbuf = w.empty() ? nullptr : &w[0];
    MultiByteToWideChar(949, 0, bytes, len, wbuf, wlen);

    int u8len = WideCharToMultiByte(CP_UTF8, 0, w.data(), wlen, nullptr, 0, nullptr, nullptr);
    string out;
    out.resize(u8len);
    char* buf = out.empty() ? nullptr : &out[0];
    WideCharToMultiByte(CP_UTF8, 0, w.data(), wlen, buf, u8len, nullptr, nullptr);
    return out;
}

string CP949ToUTF8(const char* bytes, int len)
{
    if(!bytes || len <= 0) return {};

    int wlen = MultiByteToWideChar(CP_UTF8, 0, bytes, len, nullptr, 0);
    wstring w;
    w.resize(wlen);
    wchar_t* wbuf = w.empty() ? nullptr : &w[0];
    MultiByteToWideChar(CP_UTF8, 0, bytes, len, wbuf, wlen);

    int u8len = WideCharToMultiByte(CP_UTF8, 0, w.data(), wlen, nullptr, 0, nullptr, nullptr);
    string out;
    out.resize(u8len);
    char* buf = out.empty() ? nullptr : &out[0];
    WideCharToMultiByte(CP_UTF8, 0, w.data(), wlen, buf, u8len, nullptr, nullptr);
    return out;
}

string WtoCP949(const wstring& w)
{
    if (w.empty()) return {};

    const int n = WideCharToMultiByte(949, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);

    string out;
    out.resize(n);

    char* buf = out.empty() ? nullptr : &out[0];

    WideCharToMultiByte(949, 0, w.data(), (int)w.size(), buf, n, nullptr, nullptr);

    return out;
}

wstring Utf8ToCP949(const std::string& u8)
{
    if (u8.empty()) return {};

    const int n = MultiByteToWideChar(949, 0, u8.data(), (int)u8.size(), nullptr, 0);
    wstring out;
    out.resize(n);
    wchar_t* buf = out.empty() ? nullptr : &out[0];
    MultiByteToWideChar(949, 0, u8.data(), (int)u8.size(), buf, n);
    return out;
}

string WtoUtf8(const wstring& w)
{
    if(w.empty()) return {};

    const int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);

    string out;
    out.resize(n);

    char* buf = out.empty() ? nullptr : &out[0];

    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), buf, n, nullptr, nullptr);

    return out;
}

wstring Utf8ToW(const std::string& u8)
{
    if(u8.empty()) return {};

    const int n = MultiByteToWideChar(CP_UTF8, 0, u8.data(), (int)u8.size(), nullptr, 0);
    wstring out;
    out.resize(n);
    wchar_t* buf = out.empty() ? nullptr : &out[0];
    MultiByteToWideChar(CP_UTF8, 0, u8.data(), (int)u8.size(), buf, n);
    return out;
}

bool castByte(byte*& Buf, wstring Str)
{
    enum{HEARDER = 2};
    short size = Str.size()*2;
    Buf[0] = size&0xff;
    Buf[1] = (size >> 8) & 0xff;
    memcpy_s(Buf + HEARDER, size, Str.c_str(), size);
    return true;
}

DWORD __stdcall ProcessClient(LPVOID arg)
{
    std::cout << "ClientInfo : " << mysql_get_client_info() << std::endl;

    ProcessDB* processDB = new ProcessDB();

    processDB->Init();

    //processDB->SearchLoginData("select t.user_name, t2.state from test as t join test2 as t2 on t.user_name = t2.user_name where t.user_name = 'bbb'");

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

        // 받은 데이터 출력
        buf[retval] = '\0';
        recvPlayerData = (Player_Socket&)buf;
        castBuffer = recvPlayerData.Buffer;

        switch (recvPlayerData.Main)
        {
        case (UINT8)PROTOCOL_MAIN::DefaultSetting:
            ProcessDashBoardSetting(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::LoginSetting:
            ProcessLoginSetting(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::InmateSetting:
            ProcessInmateSetting(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::ProgramSetting:
            ProcessProgramProgress(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::TreatmentSetting:
            ProcessTreatmentProgram(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::LogSetting:
            ProcessLogProgress(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        case (UINT8)PROTOCOL_MAIN::ConnectClientSetting:
            ProcessConnectClientSetting(cs, client_sock, recvPlayerData, castBuffer);
            break;
        case (UINT8)PROTOCOL_MAIN::CMS_Controller:
            ProcessCmsController(cs, client_sock, recvPlayerData, castBuffer, processDB);
            break;
        default:
            break;
        }
        LeaveCriticalSection(&cs);

        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }
    }

    SocketInfoList.erase(client_sock);

    closesocket(client_sock);

    DeleteCriticalSection(&cs);

    return 0;
}

void ProcessDashBoardSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_DEFAULT::DEFAULT_SEARCH:
    {
        vector<vector<string>> inmateSeach = _processDB->SearchData("inmate", Search_PlayData_EN_Inmate_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);
        vector<vector<string>> programSeach = _processDB->SearchData("programprogress", Search_PlayData_EN_Program_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);
        vector<vector<string>> treatmentSeach = _processDB->SearchData("treatmentprograss", Search_PlayData_EN_Treatment_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);

        vector<vector<string>> tempData;
        for (int i = 0; i < inmateSeach.size(); i++)
        {
            vector<string> tempInmateTotalData;
            for (int j = 1; j < Remake_PlayData_EN_One_ColumnName.size(); j++)
            {
                tempInmateTotalData.push_back(inmateSeach[i][j]);
            }

            vector<string> sessionData;
            vector<string> heartRateData;
            int averEyeFocus = 0;
            int eyeFocusCount = 0;
            int programSearchIndex = i * CrimeCodeMaxCount;

            int roundIndex = find(Search_PlayData_EN_Program_ColumnName.begin(), Search_PlayData_EN_Program_ColumnName.end(), "PLAY_ROUND") - Search_PlayData_EN_Program_ColumnName.begin();
            int roundCodeIndex = find(Search_PlayData_EN_Program_ColumnName.begin(), Search_PlayData_EN_Program_ColumnName.end(), "ROUND_STATUS_CODE") - Search_PlayData_EN_Program_ColumnName.begin();

            int eyeFocusIndex = find(Search_PlayData_EN_Program_ColumnName.begin(), Search_PlayData_EN_Program_ColumnName.end(), "EYE_FOCUS") - Search_PlayData_EN_Program_ColumnName.begin();
            int remarksIndex = find(Search_PlayData_EN_Program_ColumnName.begin(), Search_PlayData_EN_Program_ColumnName.end(), "REMARKS") - Search_PlayData_EN_Program_ColumnName.begin();
            int roundHeartData = find(Search_PlayData_EN_Program_ColumnName.begin(), Search_PlayData_EN_Program_ColumnName.end(), "ROUND_HEART_RATE") - Search_PlayData_EN_Program_ColumnName.begin();

            bool isOnce = true;
            for (int j = programSearchIndex; j < programSearchIndex + CrimeCodeMaxCount; j++)
            {
                sessionData.push_back(programSeach[j][eyeFocusIndex] + "," + programSeach[j][remarksIndex]);
                if (programSeach[j][roundHeartData] != "")
                    heartRateData.push_back(programSeach[j][roundHeartData]);
                else
                    heartRateData.push_back("-");

                if ((programSeach[j][roundCodeIndex] == UrlEncodeLikeUnreal(u8"진행") || programSeach[j][roundCodeIndex] == UrlEncodeLikeUnreal(u8"취소")) && isOnce)
                {
                    isOnce = false;
                    tempInmateTotalData.push_back(programSeach[j][roundIndex]);
                }
                else if (isOnce && j + 1 == programSearchIndex + CrimeCodeMaxCount)
                {
                    tempInmateTotalData.push_back(to_string(6));
                }

                if (programSeach[j][eyeFocusIndex] != "-1")
                {
                    averEyeFocus += stoi(programSeach[j][eyeFocusIndex]);
                    eyeFocusCount++;
                }
            }

            for (int j = 0; j < Remake_PlayData_EN_Two_ColumnName.size(); j++)
            {
                int tempIndex = find(Search_PlayData_EN_Treatment_ColumnName.begin(), Search_PlayData_EN_Treatment_ColumnName.end(), Remake_PlayData_EN_Two_ColumnName[j]) - Search_PlayData_EN_Treatment_ColumnName.begin();
                tempInmateTotalData.push_back(treatmentSeach[i][tempIndex]);
            }

            for (int j = 0; j < Remake_PlayData_EN_Three_ColumnName.size(); j++)
            {
                int tempIndex = find(Search_PlayData_EN_Inmate_ColumnName.begin(), Search_PlayData_EN_Inmate_ColumnName.end(), Remake_PlayData_EN_Three_ColumnName[j]) - Search_PlayData_EN_Inmate_ColumnName.begin();
                tempInmateTotalData.push_back(inmateSeach[i][tempIndex]);
            }

            tempInmateTotalData.push_back(eyeFocusCount != 0 ? to_string(averEyeFocus / eyeFocusCount) : "0");

            for (int j = 0; j < Remake_PlayData_EN_Four_ColumnName.size(); j++)
            {
                int tempIndex = find(Search_PlayData_EN_Treatment_ColumnName.begin(), Search_PlayData_EN_Treatment_ColumnName.end(), Remake_PlayData_EN_Four_ColumnName[j]) - Search_PlayData_EN_Treatment_ColumnName.begin();
                tempInmateTotalData.push_back(treatmentSeach[i][tempIndex]);
            }

            for (int j = 0; j < sessionData.size(); j++)
            {
                tempInmateTotalData.push_back(sessionData[j]);
            }

            for (int j = 0; j < heartRateData.size(); j++)
            {
                tempInmateTotalData.push_back(heartRateData[j]);
            }

            tempData.push_back(tempInmateTotalData);
        }

        vector<string> sendData = RemakeListUnderMaxBufferSize(tempData);

        Sleep(1000);

        cout << "ProcessDashBoardSetting" << endl;

        SendMsg(cs, socketInfo, playerData, sendData);
    }
    break;
    case (UINT8)PROTOCOLSUB_DEFAULT::DEFAULT_SETDATA:
    {
        SendMsg(cs, socketInfo, playerData);
    }
    break;
    default:
        break;
    }
}

void ProcessLoginSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_LOGIN::MANAGE_CHANGE_PW:
    {
        cout << "MANAGE_CHANGE_PW" << endl;
        vector<string> ss = split_by_delim(castBuffer, '#');
        string currPassword = ss[0];
        string newPassword = ss[1];

        if (currPassword != "")
        {
            string dbVersionPassword = _processDB->SearchData("logindata");

            wstring wCurrPassword = FromUtf8(currPassword.c_str(), currPassword.size());
            wstring wDbVersionPassword = FromUtf8(dbVersionPassword.c_str(), dbVersionPassword.size());

            if (wDbVersionPassword == wCurrPassword)
            {
                _processDB->UpdateData("logindata", "pinNum", newPassword, " where pinNum = ", currPassword);
                castBuffer = "true";
            }
            else
            {
                castBuffer = "false";
            }
        }
        else
        {
            castBuffer = "false";
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_LOGIN::MANAGE_CHECK_PW:
    {
        vector<string> ss = split_by_delim(castBuffer, '#');

        string currPassword = ss[0];
        string dbVersionPassword = _processDB->SearchData("logindata");

        wstring wCurrPassword = FromUtf8(currPassword.c_str(), currPassword.size());
        wstring wDbVersionPassword = FromUtf8(dbVersionPassword.c_str(), dbVersionPassword.size());

        castBuffer = "";

        if (wDbVersionPassword == wCurrPassword)
        {
            castBuffer.append("true");
        }
        else
        {
            castBuffer.append("false");
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_LOGIN::INMATE_LOGIN_CHECK:
    {
        stringstream ss;
        string prisonerNumber;

        ss.str(castBuffer);
        ss >> prisonerNumber;

        int checkCount = _processDB->SearchDataToCount("inmate", "where PRISONER_NUMBER = ", prisonerNumber);

        castBuffer = "";
        if (checkCount == 0)
        {
            cout << "false" << endl;
            castBuffer = to_string(SEND_TEXT_TYPE::TYPE_FALSE);
        }
        else
        {
            cout << "true" << endl;
            castBuffer = to_string(SEND_TEXT_TYPE::TYPE_TRUE);
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    default:
        break;
    }
}

void ProcessInmateSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_INMATE::INMATE_ADD:
    {
        //성명, 수용번호, 생일, 범죄유형, 교육과정, VR유형, 관리자
        vector<string> ss = split_by_delim(castBuffer, '#');

        int tempIndex = find(Insert_PlayData_EN_Inmate_ColumnName.begin(), Insert_PlayData_EN_Inmate_ColumnName.end(), "PRISONER_NUMBER") - Insert_PlayData_EN_Inmate_ColumnName.begin();
        castBuffer = "";
        //if (_processDB->SearchData("inmate", "where PRISONER_NUMBER = ", ss[tempIndex], false).size() != 0)
        //{
        //    //castBuffer.append("중복되는 재소자 고유번호가 존재합니다.\n다시 입력해 주세요.");
        //    castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_SAME));
        //}
        //else
        {
            string tempColumn = "";
            for(int i = 0; i < Insert_PlayData_EN_Inmate_ColumnName.size(); i++)
                tempColumn += Insert_PlayData_EN_Inmate_ColumnName[i] + ",";
            tempColumn.pop_back();

            string shortDate = GetShortDate();
            ss.push_back(shortDate);
            ss.push_back(shortDate);

            switch (_processDB->InsertData("inmate", tempColumn, ss))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
            case QUERY_RETURN_TYPE::RETURN_ERROR:
            {
                castBuffer = to_string(SEND_TEXT_TYPE::TYPE_FALSE);
                cout << "Inmate ADD error" << endl;
            }
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                castBuffer = to_string(SEND_TEXT_TYPE::TYPE_TRUE);
                break;
            default:
                break;
            }

            switch (_processDB->InsertData("treatmentprograss", "INMATE_ID", ss[tempIndex]))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
            case QUERY_RETURN_TYPE::RETURN_ERROR:
            {
                castBuffer = to_string(SEND_TEXT_TYPE::TYPE_FALSE);
                cout << "Treatment ADD error" << endl;
            }
            break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                castBuffer = to_string(SEND_TEXT_TYPE::TYPE_TRUE);
                break;
            default:
                break;
            }

            vector<string> tempColumns = { "INMATE_ID", "PROGRAM_STATUS_CODE" };
            vector<string> tempDatas = { ss[tempIndex], "%EC%A7%84%ED%96%89" };
            string treatmentID = _processDB->SearchData("treatmentprograss", "ID", tempColumns, tempDatas)[0];

            vector<string> tempProgramData;
            tempProgramData.push_back(treatmentID);
            tempProgramData.push_back("");
            tempProgramData.push_back("-");
            for (int i = 0; i < CrimeCodeMaxCount; i++)
            {
                tempProgramData[1] = to_string(i + 1);
                switch (_processDB->InsertData("programprogress", "INMATE_ID, PLAY_ROUND, ROUND_HEART_RATE", tempProgramData))
                {
                case QUERY_RETURN_TYPE::RETURN_NONE:
                case QUERY_RETURN_TYPE::RETURN_ERROR:
                {
                    castBuffer = to_string(SEND_TEXT_TYPE::TYPE_FALSE);
                    cout << "Program ADD error" << endl;
                }
                break;
                case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                    castBuffer = to_string(SEND_TEXT_TYPE::TYPE_TRUE);
                    break;
                default:
                    break;
                }
            }
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_INMATE::INMATE_DELETE:
    {
        stringstream ss;
        string prisonerNumber;

        ss.str(castBuffer);
        ss >> prisonerNumber;

        castBuffer = "";

        string inmateName = _processDB->SearchData("inmate", "INMATE_NAME", "where PRISONER_NUMBER = ", prisonerNumber);
        if (inmateName == "")
        {
            castBuffer.append("중복되는 재소자 고유번호가 존재합니다.\n 다시 입력해 주세요.");
        }
        else
        {
            vector<string> tempColumns = { "INMATE_ID", "PROGRAM_STATUS_CODE" };
            vector<string> tempDatas = { prisonerNumber, "%EC%A7%84%ED%96%89" };
            string treatmentID = _processDB->SearchData("treatmentprograss", "ID", tempColumns, tempDatas)[0];

            switch (_processDB->DeleteData("programprogress", "where INMATE_ID = " + prisonerNumber + ";"))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append("입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append("해당 제소자에 관한 정보가 남아있어 삭제가 불가능합니다.\n 관련 정보 삭제를 먼저 진행해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                castBuffer.append("재소자 정보를 삭제했습니다.");
                break;
            default:
                break;
            }

            switch (_processDB->DeleteData("treatmentprograss", "where INMATE_ID = " + prisonerNumber + ";"))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append("입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append("해당 제소자에 관한 정보가 남아있어 삭제가 불가능합니다.\n 관련 정보 삭제를 먼저 진행해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                castBuffer.append("재소자 정보를 삭제했습니다.");
                break;
            default:
                break;
            }

            switch (_processDB->DeleteData("inmate", "where PRISONER_NUMBER = " + prisonerNumber + ";"))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append("입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append("해당 제소자에 관한 정보가 남아있어 삭제가 불가능합니다.\n 관련 정보 삭제를 먼저 진행해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                castBuffer.append("재소자 정보를 삭제했습니다.");
                break;
            default:
                break;
            }
        }

        //strcpy_s(playerData.Buffer, castBuffer.c_str());

        //SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_INMATE::INMATE_UPDATE:
    {
        vector<string> ss = split_by_delim(castBuffer, '$');

        string prisonerNumber = ss[0];
        vector<string> tempUpdateData = split_by_delim(ss[1], '#');
        string programStatusCode = ss[2];

        tempUpdateData.push_back(GetShortDate());

        for (int i = 0; i < tempUpdateData.size(); i++)
        {
            if (tempUpdateData[i].empty())
            {
                tempUpdateData[i] = "-";
            }
        }

        string treatmentID = "";

        vector<string> tempColumns = { "INMATE_ID", "PROGRAM_STATUS_CODE" };
        vector<string> tempDatas = { prisonerNumber, "%EC%A7%84%ED%96%89" };
        treatmentID = _processDB->SearchData("treatmentprograss", "ID", tempColumns, tempDatas)[0];

        if(programStatusCode == "%EC%A2%85%EB%A3%8C" && treatmentID == "")
            return;

        //if(programStatusCode == "%EC%A7%84%ED%96%89" && checkData.size() != 0)
        //    return;

        castBuffer = "";
        switch (_processDB->UpdateData("inmate", Update_PlayData_EN_Inmate_ColumnName, tempUpdateData, " where ID = ", treatmentID))
        {
        case QUERY_RETURN_TYPE::RETURN_ERROR:
            castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
            break;
        default:
            break;
        }

        castBuffer = "";
        switch (_processDB->UpdateData("treatmentprograss", "PROGRAM_STATUS_CODE", programStatusCode, " where ID = ", treatmentID))
        {
        case QUERY_RETURN_TYPE::RETURN_NONE:
            castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
            break;
        case QUERY_RETURN_TYPE::RETURN_ERROR:
            castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
            break;
        case QUERY_RETURN_TYPE::RETURN_SUCCESS:
        {
            castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
        }
        break;
        default:
            break;
        }

        string wCastBuffer = N949ToUTF8(castBuffer.c_str(), castBuffer.size());

        //Sleep(1000);

        strcpy_s(playerData.Buffer, wCastBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_INMATE::INMATE_SEARCH:
    {
        vector<vector<string>> inmateSeach = _processDB->SearchData("inmate", Search_Inmate_KR_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);

        vector<vector<string>> utf_InmateSeach;
        for (int i = 0; i < inmateSeach.size(); i++)
        {
            utf_InmateSeach.push_back(vector<string>());
            for (int j = 0; j < inmateSeach[0].size(); j++)
            {
                utf_InmateSeach[i].push_back(CP949ToUTF8(inmateSeach[i][j].c_str(), inmateSeach[i][j].size()));
            }
        }

        string data;
        for (int i = 0; i < Search_Inmate_KR_ColumnName.size(); i++)
        {
            data += Search_Inmate_KR_ColumnName[i] + "#";
        }
        data.pop_back();
        data += "$";

        vector<string> W_SendData;
        W_SendData.push_back(N949ToUTF8(data.c_str(), data.size()));

        vector<string> sendData = RemakeListUnderMaxBufferSize(utf_InmateSeach);
        for (int i = 0; i < sendData.size(); i++)
        {
            W_SendData.push_back(sendData[i]);
        }

        Sleep(1000);

        SendMsg(cs, socketInfo, playerData, W_SendData);
    }
    break;
    default:
        break;
    }
}

void ProcessCodeSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_CODE::CODE_ADD:
    {
        stringstream ss;
        string category;
        string key;
        string value;
        string description;

        ss.str(castBuffer);
        ss >> category >> key >> value >> description;

        vector<string> insertDatas;

        castBuffer = "";
        if (_processDB->SearchData("code", "where CODE_KEY = ", key, false).size() == 0)
        {
            castBuffer.append("중복되는 코드가 존재합니다.\n 다시 입력해 주세요.");
        }
        else
        {
            //insertDatas.push_back("'" + category + "','" + key + "','" + value + "','" + description + "'");

            //vector<QUERY_RETURN_TYPE> checkInsertData = _processDB->InsertData("inmate", INMATE_INSERTTABLE_DEFAULT_COLUMNS, insertDatas);

            //for (int i = 0; i < checkInsertData.size(); i++)
            //{
            //    switch (checkInsertData[i])
            //    {
            //    case QUERY_RETURN_TYPE::RETURN_NONE:
            //    case QUERY_RETURN_TYPE::RETURN_ERROR:
            //        castBuffer.append("신규 코드 등록을 실패했습니다.\n정보를 다시 입력해 주세요.");
            //        break;
            //    case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            //        castBuffer.append("신규 코드 등록을 완료했습니다.");
            //        break;
            //    default:
            //        break;
            //    }
            //}
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_CODE::CODE_DELETE:
    {
        //추후 필요에 따라 작업 진행
    }
    break;
    case (UINT8)PROTOCOLSUB_CODE::CODE_UPDATE:
    {
        stringstream ss;
        int id;
        string category;
        string key;
        string value;
        string description;

        ss.str(castBuffer);
        ss >> id >> category >> key >> value >> description;

        vector<string> codeTableUpdateDatas = { category, key, value, description };

        castBuffer = "";
        _processDB->UpdateData("inmate", codeTableColumns, codeTableUpdateDatas, "ID", to_string(id));
        castBuffer.append("코드 정보를 수정했습니다.");

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_CODE::CODE_SEARCH:
    {
        vector<vector<string>> codeSeach = _processDB->SearchData("code", Search_Code_KR_ColumnName.size());

        castBuffer = "";
        for (int i = 0, k = 0; i < codeSeach.size(); i++, k++)
        {
            if (k < Search_Code_KR_ColumnName.size())
                castBuffer.append(Search_Code_KR_ColumnName[k]);

            for (int j = 0; j < codeSeach[0].size(); j++)
            {
                castBuffer.append("#" + codeSeach[i][j]);
            }

            castBuffer.append("$");
        }
        castBuffer.pop_back();

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    default:
        break;
    }
}

void ProcessTreatmentProgram(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    string tableName = "treatmentprogram";
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_TREATMENT::TREATMENT_ADD:
    {
        stringstream ss;
        string crimeCode;
        string situationCode;
        string sessionNum;

        ss.str(castBuffer);
        ss >> crimeCode >> situationCode >> sessionNum;

        vector<string> insertDatas = { crimeCode, situationCode, sessionNum };

        castBuffer = "";
        if (_processDB->SearchData(tableName, "where CRIME_TYPE_CODE = ", crimeCode, false).size() == 0)
        {
            castBuffer.append("입력하신 범죄 코드가 존재하지 않습니다.\n 다시 입력해 주세요.");
        }
        else if (_processDB->SearchData(tableName, "where SITUATION_CODE = ", situationCode, false).size() == 0)
        {
            castBuffer.append("입력하신 상황 코드가 존재하지 않습니다.\n 다시 입력해 주세요.");
        }
        else
        {
            //insertDatas.push_back("'" + crimeCode + "','" + situationCode + "','" + sessionNum + "'");

            //vector<QUERY_RETURN_TYPE> checkInsertData = _processDB->InsertData("inmate", INMATE_INSERTTABLE_DEFAULT_COLUMNS, insertDatas);

            //for (int i = 0; i < checkInsertData.size(); i++)
            //{
            //    switch (checkInsertData[i])
            //    {
            //    case QUERY_RETURN_TYPE::RETURN_NONE:
            //    case QUERY_RETURN_TYPE::RETURN_ERROR:
            //        castBuffer.append("치료 교육 정보 추가에 실패했습니다.\n정보를 다시 입력해 주세요.");
            //        break;
            //    case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            //        castBuffer.append("치료 교육 정보를 추가했습니다.");
            //        break;
            //    default:
            //        break;
            //    }
            //}
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_TREATMENT::TREATMENT_DELETE:
    {
        
    }
    break;
    case (UINT8)PROTOCOLSUB_TREATMENT::TREATMENT_UPDATE:
    {
        vector<string> ss = split_by_delim(castBuffer, '#');

        int type = stoi(ss[0]);
        string prisonerNumber = ss[1];

        vector<string> tempColumns = { "INMATE_ID", "PROGRAM_STATUS_CODE" };
        vector<string> tempDatas = { prisonerNumber, "%EC%A7%84%ED%96%89" };
        string treatmentID = _processDB->SearchData("treatmentprograss", "ID", tempColumns, tempDatas)[0];

        switch (type)
        {
        case (UINT8)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_CONSENTTEST:
        {
            castBuffer = "";
            switch (_processDB->UpdateData("treatmentprograss", "CONSENT_TEST", "Check", " where ID = ", treatmentID))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }
        }
        break;
        case (UINT8)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_PRETEST:
        {
            string testScore = ss[2];

            if(testScore.empty())
                testScore = "-";

            castBuffer = "";
            switch (_processDB->UpdateData("treatmentprograss", "PRE_TEST", testScore, " where ID = ", treatmentID))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }
        }
        break;
        case (UINT8)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_POSTTEST:
        {
            string testScore = ss[2];

            if (testScore.empty())
                testScore = "-";

            castBuffer = "";
            switch (_processDB->UpdateData("treatmentprograss", "POST_TEST", testScore, " where ID = ", treatmentID))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }
        }
        break;
        case (UINT8)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_LASTCHECK:
        {
            string testScore = ss[2];
            //vector<string> Update_PlayData_EN_Treatment_LastCheck_ColumnName = { "LAST_CHECK", "END_AT", "PROGRAM_STATUS_CODE" };

            if (testScore.empty())
                testScore = "-";

            vector<string> tempUpdateData;
            tempUpdateData.push_back(testScore);
            tempUpdateData.push_back(GetShortDate());
            tempUpdateData.push_back(UrlEncodeLikeUnreal(u8"종료"));

            castBuffer = "";
            switch (_processDB->UpdateData("treatmentprograss", Update_PlayData_EN_Treatment_LastCheck_ColumnName, tempUpdateData, " where ID = ", treatmentID))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }
        }
        break;
        case (UINT8)TREATMENT_UPDATE_TYPE::UPDATE_TREATMENT_STARTAT:
        {
            string checkData = _processDB->SearchData("treatmentprograss", "START_AT", " where ID = ", treatmentID);

            if (checkData == "-")
            {
                cout << "First Start" << endl;
                castBuffer = "";
                switch (_processDB->UpdateData("treatmentprograss", "START_AT", GetShortDate(), " where ID = ", treatmentID))
                {
                case QUERY_RETURN_TYPE::RETURN_NONE:
                    castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                    break;
                case QUERY_RETURN_TYPE::RETURN_ERROR:
                    castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                    break;
                case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                {
                    castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
                }
                break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Already Start At" << endl;
            }
        }
        break;
        default:
            break;
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_TREATMENT::TREATMENT_SEARCH:
    {
        vector<vector<string>> treatmentSeach = _processDB->SearchData(tableName, Search_TreatmentProgram_KR_ColumnName.size());

        castBuffer = "";
        for (int i = 0, k = 0; i < treatmentSeach.size(); i++, k++)
        {
            if (k < Search_TreatmentProgram_KR_ColumnName.size())
                castBuffer.append(Search_TreatmentProgram_KR_ColumnName[k]);

            for (int j = 0; j < treatmentSeach[0].size(); j++)
            {
                castBuffer.append("#" + treatmentSeach[i][j]);
            }

            castBuffer.append("$");
        }
        castBuffer.pop_back();

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    default:
        break;
    }
}

void ProcessProgramProgress(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    Sleep(1000);
    string tableName = "programprogress";
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_PROGRAM::PROGRAM_ADD:
    {
        stringstream ss;
        int type;

        ss.str(castBuffer);
        ss >> type;

        switch (type)
        {
        case (UINT8)PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_PLAYROUND:
        {
            int id;

            ss.str(castBuffer);
            ss >> type >> id;

            vector<string> tempProgramData = _processDB->SearchData(tableName, PROGRAM_INSERTTABLE_DEFAULT_COLUMNS, "where ID = ", to_string(id), programAddPlayRoundColumns.size());

            vector<string> insertDatas;

            string data = "";

            for (int i = 0; i < programAddPlayRoundColumns.size(); i++)
            {
                if (programAddPlayRoundColumns[i] == "PLAY_ROUND")
                {
                    data.append("'" + to_string(stoi(tempProgramData[i]) + 1) + "',");
                }
                else
                {
                    data.append("'" + tempProgramData[i] + "',");
                }
            }
            data.pop_back();

            insertDatas.push_back(data);

            //vector<QUERY_RETURN_TYPE> checkInsertData = _processDB->InsertData(tableName, PROGRAM_INSERTTABLE_DEFAULT_COLUMNS, insertDatas);

            //for (int i = 0; i < checkInsertData.size(); i++)
            //{
            //    switch (checkInsertData[i])
            //    {
            //    case QUERY_RETURN_TYPE::RETURN_NONE:
            //    case QUERY_RETURN_TYPE::RETURN_ERROR:
            //        castBuffer.append("회차 정보 추가에 실패했습니다.\n정보를 다시 입력해 주세요.");
            //        break;
            //    case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            //        castBuffer.append("회차 정보 추가를 완료했습니다.\n정보를 불러오는 중 입니다.\n잠시만 기다려주세요.");
            //        break;
            //    default:
            //        break;
            //    }
            //}
        }
        break;
        case (UINT8)PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_NEWCRIME:
        {
            string prisonerNumber;
            string crimeCode;
            string situationCode;

            ss.str(castBuffer);
            ss >> type >> prisonerNumber >> crimeCode >> situationCode;

            vector<string> tempColumns = { "CRIME_TYPE_CODE", "SITUATION_CODE" };
            vector<string> tempDatas = { crimeCode, situationCode };

            int treatmentCount = _processDB->SearchDataToCount("treatmentprogram", tempColumns, tempDatas, "AND");

            map<int, int> roundCount;
            for (int i = 0; i < treatmentCount; i++)
                roundCount[i + 1] = 0;

            vector<string> joinColumns = { "INMATE_ID", "TREATMENT_PROGRAM_ID", "PLAY_ROUND" };
            unordered_map<string, vector<string>> joinProgramCheckDatas = _processDB->JoinSearchData(joinColumns, "t", "programprogress", "inmate", "INMATE_ID", "where PRISONER_NUMBER = ", prisonerNumber);

            for (int i = 0; i < joinProgramCheckDatas["PLAY_ROUND"].size(); i++)
            {
                roundCount[stoi(joinProgramCheckDatas["TREATMENT_PROGRAM_ID"][i])] = stoi(joinProgramCheckDatas["PLAY_ROUND"][i]);
            }

            vector<string> insertDatas;
            for (int i = 0; i < treatmentCount; i++)
            {
                insertDatas.push_back("'" + joinProgramCheckDatas["INMATE_ID"][0] + "','" + to_string(i + 1) + "','" + to_string(roundCount[i + 1] + 1) + "'");
            }

            //vector<QUERY_RETURN_TYPE> checkInsertData = _processDB->InsertData(INMATE_CREATETABLE_DEFAULT_NAME, PROGRAM_INSERTTABLE_DEFAULT_COLUMNS, insertDatas);

            //for (int i = 0; i < checkInsertData.size(); i++)
            //{
            //    switch (checkInsertData[i])
            //    {
            //    case QUERY_RETURN_TYPE::RETURN_NONE:
            //    case QUERY_RETURN_TYPE::RETURN_ERROR:
            //        castBuffer.append("신규 범죄유형의 회차 정보 추가에 실패했습니다.\n정보를 다시 입력해 주세요.");
            //        break;
            //    case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            //        castBuffer.append("신규 범죄유형의 회차 정보 추가를 완료했습니다.");
            //        break;
            //    default:
            //        break;
            //    }
            //}

            strcpy_s(playerData.Buffer, castBuffer.c_str());

            SendMsg(cs, socketInfo, playerData);
        }
        break;
        case (UINT8)PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_NEWINMATE:
        {
            string prisonerNumber;
            string crimeCode;
            string situationCode;

            ss.str(castBuffer);
            ss >> type >> prisonerNumber >> crimeCode >> situationCode;

            string inmanteID = _processDB->SearchData("inmate", "ID", "where PRISONER_NUMBER = ", prisonerNumber);

            vector<string> tempColumns = { "CRIME_TYPE_CODE", "SITUATION_CODE" };
            vector<string> tempDatas = { crimeCode, situationCode };

            vector<string> treatmentIDs = _processDB->SearchData("treatmentprogram", "ID", tempColumns, tempDatas);

            castBuffer = "";
            if (_processDB->SearchTableName(INMATE_CREATETABLE_DEFAULT_NAME, DB_NAME))
            {
                vector<string> insertDatas;
                for (int i = 0; i < treatmentIDs.size(); i++)
                {
                    insertDatas.push_back("'" + inmanteID + "','" + treatmentIDs[i] + "','" + to_string(PlayRoundDefault) + "'");
                }

                //vector<QUERY_RETURN_TYPE> checkInsertData = _processDB->InsertData(INMATE_CREATETABLE_DEFAULT_NAME, PROGRAM_INSERTTABLE_DEFAULT_COLUMNS, insertDatas);

                //for (int i = 0; i < checkInsertData.size(); i++)
                //{
                //    switch (checkInsertData[i])
                //    {
                //    case QUERY_RETURN_TYPE::RETURN_NONE:
                //    case QUERY_RETURN_TYPE::RETURN_ERROR:
                //        castBuffer.append("신규 체험 정보 등록에 실패했습니다.\n정보를 다시 입력해 주세요.");
                //        break;
                //    case QUERY_RETURN_TYPE::RETURN_SUCCESS:
                //        castBuffer.append("신규 체험 정보 등록을 완료했습니다.");
                //        break;
                //    default:
                //        break;
                //    }
                //}
            }
        }
        break;
        default:
            break;
        }

        strcpy_s(playerData.Buffer, castBuffer.c_str());

        SendMsg(cs, socketInfo, playerData);
    }
    break;
    case (UINT8)PROTOCOLSUB_PROGRAM::PROGRAM_DELETE:
    {

    }
    break;
    case (UINT8)PROTOCOLSUB_PROGRAM::PROGRAM_UPDATE:
    {
        vector<string> ss = split_by_delim(castBuffer, '#');
        int type = stoi(ss[0]);
        string prisonerNumber = ss[1];
        string updateRound = ss[2];

        vector<string> tempColumns = { "INMATE_ID", "PROGRAM_STATUS_CODE" };
        vector<string> tempDatas = { prisonerNumber, "%EC%A7%84%ED%96%89" };
        string treatmentID = _processDB->SearchData("treatmentprograss", "ID", tempColumns, tempDatas)[0];

        switch (type)
        {
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_DEFAULT:
        {
            cout << "UPDATE_PROGRAM_DEFAULT" << endl;

            vector<string> tempUpdateData;
            tempUpdateData.push_back(ss[3]);
            tempUpdateData.push_back(UrlEncodeLikeUnreal(u8"종료"));

            string whereCondition = " where INMATE_ID = '" + treatmentID + "' and PLAY_ROUND = '" + updateRound + "'";

            castBuffer = "";
            switch (_processDB->UpdateData("programprogress", Update_PlayData_EN_Program_ColumnName, tempUpdateData, whereCondition))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }


        }
        break;
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_REMARKS:
        {
            string remarks = ss[3];

            string find_str = "-";
            string replace_str = "";

            if (remarks.empty() || remarks == replace_str)
                remarks = find_str;
            if(remarks == find_str)
                return;

            string whereCondition = " where INMATE_ID = '" + treatmentID + "' and PLAY_ROUND = '" + updateRound + "'";

            if(remarks.find(find_str) != string::npos)
                remarks.replace(remarks.find(find_str), find_str.length(), replace_str);

            castBuffer = "";
            switch (_processDB->UpdateData("programprogress", "REMARKS", remarks, whereCondition))
            {
            case QUERY_RETURN_TYPE::RETURN_NONE:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 재소자 번호가 존재하지 않습니다.\n 확인 후 다시 입력해 주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_ERROR:
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_FALSE) + "#입력하신 범죄코드는 존재하지 않습니다.\n 확인 후 다시 입력해주세요.");
                break;
            case QUERY_RETURN_TYPE::RETURN_SUCCESS:
            {
                castBuffer.append(to_string(SEND_TEXT_TYPE::TYPE_TRUE) + "#재소자 정보를 수정했습니다.");
            }
            break;
            default:
                break;
            }
        }
        break;
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE:
        {
            cout << "UPDATE_PROGRAM_ROUND_HEARTRATE" << endl;

            if (CmsClientDataA.socket == socketInfo)
            {
                SendMsg(cs, MovieClientDataA.socket, playerData);
            }
            else if (CmsClientDataB.socket == socketInfo)
            {
                SendMsg(cs, MovieClientDataB.socket, playerData);
            }
            else
            {
                cout << "socketInfo error!" << endl; 
            }
        }
        break;
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MOVIE_NUM:
        {
            string tempHeartRate = ss[3];
            string tempMovieNum = ss[4];

            string whereCondition = " where INMATE_ID = '" + treatmentID + "' and PLAY_ROUND = '" + updateRound + "'";

            string heartRate = _processDB->SearchData("programprogress", "ROUND_HEART_RATE", whereCondition);

            if (heartRate == "-")
            {
                _processDB->UpdateData("programprogress", "ROUND_HEART_RATE", tempHeartRate + "," + tempMovieNum, whereCondition);
            }
            else
            {
                _processDB->UpdateData("programprogress", "ROUND_HEART_RATE", heartRate + "@" + tempHeartRate + "," + tempMovieNum, whereCondition);
            }
            
            //string tempHeartRate = ss[3];

            //string whereCondition = " where INMATE_ID = '" + prisonerNumber + "' and PLAY_ROUND = '" + updateRound + "'";

            //_processDB->UpdateData("programprogress", "ROUND_HEART_RATE", tempHeartRate, whereCondition);

            //SendMsg(cs, MovieClientData.socket, playerData);
        }
        break;
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_REQUEST_MOVIE_NUM:
        {
            cout << "UPDATE_PROGRAM_ROUND_REQUEST_MOVIE_NUM" << endl;

            castBuffer = "";

            castBuffer.append(prisonerNumber + "#" + updateRound);

            strcpy_s(playerData.Buffer, castBuffer.c_str());

            if (CmsClientDataA.socket == socketInfo)
            {
                SendMsg(cs, MovieClientDataA.socket, playerData);
            }
            else if (CmsClientDataB.socket == socketInfo)
            {
                SendMsg(cs, MovieClientDataB.socket, playerData);
            }
            else
            {
                cout << "socketInfo error!" << endl;
            }
        }
        break;
        case (UINT8)PROGRAM_UPDATE_TYPE::UPDATE_PROGRAM_ROUND_HEARTRATE_MARK:
        {
            cout << "UPDATE_PROGRAM_ROUND_HEARTRATE_MARK" << endl;

            if (MovieClientDataA.socket == socketInfo)
            {
                SendMsg(cs, CmsClientDataA.socket, playerData);
            }
            else if (MovieClientDataB.socket == socketInfo)
            {
                SendMsg(cs, CmsClientDataB.socket, playerData);
            }
            else
            {
                cout << "socketInfo error!" << endl;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_PROGRAM::PROGRAM_SEARCH:
    {
        stringstream ss;
        int type;
        string prisonerNumber;

        ss.str(castBuffer);
        ss >> type >> prisonerNumber;

        string inmateName = _processDB->SearchData("inmate", "INMATE_NAME", "where PRISONER_NUMBER = ", prisonerNumber);
        string programTableName = "_" + inmateName;

        castBuffer = to_string(type) + " ";
        switch (type)
        {
        case (UINT8)PROGRAM_SEARCH_TYPE::PROGRAM_SEARCH_MANAGE:
        {
            vector<vector<string>> programSeach = _processDB->SearchData(programTableName, Search_ProgramProgress_KR_ColumnName.size());

            for (int i = 0, k = 0; i < programSeach.size(); i++, k++)
            {
                if (k < Search_ProgramProgress_KR_ColumnName.size())
                    castBuffer.append(Search_ProgramProgress_KR_ColumnName[k]);

                for (int j = 0; j < programSeach[0].size(); j++)
                {
                    castBuffer.append("#" + programSeach[i][j]);
                }

                castBuffer.append("$");
            }
            castBuffer.pop_back();

            strcpy_s(playerData.Buffer, castBuffer.c_str());

            SendMsg(cs, socketInfo, playerData);
        }
            break;
        case (UINT8)PROGRAM_SEARCH_TYPE::PROGRAM_SEARCH_PLAY_DATA:
        {
            list<string> playData = _processDB->SearchData(programTableName, "where PROGRESS_STATUS_CODE = ", "진행대기", true, Search_ProgramProgress_KR_ColumnName.size());

            string key = "";
            string value = "";

            list<string>::iterator iter = playData.begin();

            for (int i = 0, j = 0; i < playData.size(); i++, iter++)
            {
                switch (i)
                {
                case 0://ID
                {
                    key.append(Search_PlayData_EN_InmateColumnName[i] + "#");
                    value.append((*iter) + "#");
                }
                break;
                case 1://INMATE_ID
                {
                    key.append(Search_PlayData_EN_InmateColumnName[i] + "#");
                    value.append(inmateName + "#");
                }
                break;
                case 2://TREATMENT_PROGRAM_ID
                {
                    vector<string> treatmentPlayData = _processDB->SearchData("treatmentprogram", TREATMENT_INSERTTABLE_DEFAULT_COLUMNS, "where ID = ", *iter, Search_PlayData_EN_TreatmentColumnName.size());

                    for (int i = 0; i < treatmentPlayData.size(); i++)
                    { 
                        key.append(Search_PlayData_EN_TreatmentColumnName[i] + "#");
                        value.append(treatmentPlayData[i] + "#");
                    }
                }
                break;
                case 3://PLAY_ROUND
                case 4://AVERAGE_HEART_RATE
                case 5://MAX_HEART_RATE
                {
                    key.append(Search_PlayData_EN_ProgramColumnName[j++] + "#");
                    value.append((*iter) + "#");
                }
                break;
                case 6://PROGRESS_STATUS_CODE
                {
                    key.append(Search_PlayData_EN_ProgramColumnName[j] + "$");
                    value.append((*iter));
                }
                break;
                default:
                    break;
                }
            }

            castBuffer.append(key + value);

            strcpy_s(playerData.Buffer, castBuffer.c_str());

            SendMsg(cs, socketInfo, playerData);
        }
            break;
        case (UINT8)PROGRAM_SEARCH_TYPE::PROGRAM_SEARCH_ADD_CHECK:
        {
            Sleep(1000);

            stringstream ss;
            string prisonerNumber;

            ss.str(castBuffer);
            ss >> prisonerNumber;

            castBuffer = "";

            vector<string> joinColumns = { "ID", "PROGRESS_STATUS_CODE" };

            unordered_map<string, vector<string>> joinProgramCheckDatas = _processDB->JoinSearchData(joinColumns, "t", "programprogress", "inmate", "INMATE_ID", "where PRISONER_NUMBER = ", prisonerNumber);

            if (joinProgramCheckDatas.size() != 0)
            {
                int indexPlayRound = -1;
                int indexAddNone = -1;
                int indexNewCrime = -1;
                string resultText = "";

                for (int i = 0; i < joinProgramCheckDatas.begin()->second.size(); i++)
                {
                    if (joinProgramCheckDatas["PROGRESS_STATUS_CODE"][i] == "중단" && indexPlayRound == -1)
                    {
                        indexPlayRound = i;
                        resultText.append("해당 제소자의 이전 체험이 중단 되어서 신규 회차를 추가 할 예정입니다.\n진행하시겠습까?");
                    }

                    if (joinProgramCheckDatas["PROGRESS_STATUS_CODE"][i] == "진행대기" && indexAddNone == -1)
                    {
                        indexAddNone = i;
                    }

                    if (joinProgramCheckDatas["PROGRESS_STATUS_CODE"][i] != "완료" && indexNewCrime == -1)
                    {
                        indexNewCrime = i;
                    }
                }

                if (indexPlayRound != -1)
                {
                    //중단 이후 회차 정보 추가 -> 조회 -> 시작
                    castBuffer.append(to_string(PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_PLAYROUND) + "#");
                    castBuffer.append(joinProgramCheckDatas["ID"][indexPlayRound] + "$");
                    castBuffer.append("이전 체험에서 해당 회기를 중단시킨 정보가 존재하여\n해당 회기에 대한 재시작 정보를 정리 중 입니다.\n잠시만 기다려주세요.");
                }
                else if (indexAddNone != -1)
                {
                    //진행 대기에 맞는 회기 조회 -> 시작
                    castBuffer.append(to_string(PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_NONE) + "#" + joinProgramCheckDatas["ID"][indexPlayRound]);
                }
                else if (indexNewCrime == -1)
                {
                    //기존 정보를 토대로 회기, 회차 정보들 추가(5회기면 5개 add) -> 조회 -> 시작
                    castBuffer.append(to_string(PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_NEWCRIME) + "$");
                    castBuffer.append("해당 제소자의 치료 프로그램이 전부 완료 된 상태입니다.\n새로운 치료 프로그램을 등록하시겠습니까?\n('예'를 누르면 추가 페이지로 이동합니다.)");
                }
            }
            else
            {
                //완전 새로운 정보 추가 -> 조회 -> 시작
                castBuffer.append(to_string(PROGRAM_ADD_CHECK_TYPE::PROGRAM_ADD_NEWINMATE) + "$");
                castBuffer.append("해당 제소자의 치료 프로그램이 없습니다.\n새로운 치료 프로그램을 등록하시겠습니까?\n('예'를 누르면 추가 페이지로 이동합니다.)");
            }

            strcpy_s(playerData.Buffer, castBuffer.c_str());

            SendMsg(cs, socketInfo, playerData);
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

void ProcessLogProgress(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    string tableName = "programlog";
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_LOG::LOG_ADD:
    {
        vector<string> ss = split_by_delim(castBuffer, '#');

        _processDB->InsertData("logdata", "LOG_TYPE, LOG_TIME, LOG_ACTOR", ss);
    }
        break;
    case (UINT8)PROTOCOLSUB_LOG::LOG_DELETE:
        break;
    case (UINT8)PROTOCOLSUB_LOG::LOG_UPDATE:
        break;
    case (UINT8)PROTOCOLSUB_LOG::LOG_SEARCH:
    {
        cout << "LOG_SEARCH" << endl;

        _processDB->LogDataOptimization();

        vector<vector<string>> logSearch = _processDB->SearchData("logdata", Search_PlayData_EN_LOG_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);

        vector<vector<string>> tempData;

        for (int i = 0; i < logSearch.size(); i++)
        {
            vector<string> checkData;
            for (int j = 0; j < Search_PlayData_EN_LogColumnName.size(); j++)
            {
                int tempIndex = find(Search_PlayData_EN_LOG_ColumnName.begin(), Search_PlayData_EN_LOG_ColumnName.end(), Search_PlayData_EN_LogColumnName[j]) - Search_PlayData_EN_LOG_ColumnName.begin();
                checkData.push_back(logSearch[i][tempIndex]);
            }

            tempData.push_back(checkData);
        }

        vector<string> sendData = RemakeListUnderMaxBufferSize(tempData);

        Sleep(1000);

        SendMsg(cs, socketInfo, playerData, sendData);
    }
        break;
    default:
        break;
    }
}

void ProcessConnectClientSetting(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer)
{
    ClientData gameStartData;
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_DEVICE_TYPE::MovieClientA:
    {
        cout << "MovieClientA" << endl;
        gameStartData.SceneType = "MovieClientA";
        gameStartData.socket = socketInfo;
        MovieClientDataA = gameStartData;
    }
    break;
    case (UINT8)PROTOCOLSUB_DEVICE_TYPE::MovieClientB:
    {
        cout << "MovieClientB" << endl;
        gameStartData.SceneType = "MovieClientB";
        gameStartData.socket = socketInfo;
        MovieClientDataB = gameStartData;
    }
    break;
    case (UINT8)PROTOCOLSUB_DEVICE_TYPE::CmsClinetA:
    {
        cout << "CmsClientA" << endl;
        gameStartData.SceneType = "CmsClientA";
        gameStartData.socket = socketInfo;
        CmsClientDataA = gameStartData;
    }
    break;
    case (UINT8)PROTOCOLSUB_DEVICE_TYPE::CmsClinetB:
    {
        cout << "CmsClientB" << endl;
        gameStartData.SceneType = "CmsClientB";
        gameStartData.socket = socketInfo;
        CmsClientDataB = gameStartData;
    }
    break;
    default:
        break;
    }
}

void ProcessCmsController(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, string castBuffer, ProcessDB* _processDB)
{
    switch (playerData.Sub)
    {
    case (UINT8)PROTOCOLSUB_CMS::Play:
    {
        cout << "Play" << endl;
        //SendMsg(cs, CmsClient.socket, playerData);
        if (CmsClientDataA.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataA.socket, playerData);
        }
        else if (CmsClientDataB.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Stop:
    {
        cout << "Stop" << endl;
        //SendMsg(cs, CmsClient.socket, playerData);
        if (CmsClientDataA.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataA.socket, playerData);
        }
        else if (CmsClientDataB.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Skip:
    {

    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Reset:
    {

    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Start:
    {
        cout << "Start" << endl;
        if (CmsClientDataA.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataA.socket, playerData);
        }
        else if (CmsClientDataB.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Pause:
    {
        cout << "Pause" << endl;
        if (CmsClientDataA.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataA.socket, playerData);
        }
        else if (CmsClientDataB.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::HeadTracking:
    {
        //cout << "HeadTracking" << endl;

        if (MovieClientDataA.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataA.socket, playerData);
        }
        else if (MovieClientDataB.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::Temp_NextRound:
    {
        cout << "Temp_NextRound" << endl;

        if (MovieClientDataA.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataA.socket, playerData);
        }
        else if (MovieClientDataB.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::SectionMovement:
    {
        cout << "SectionMovement" << endl;

        if (CmsClientDataA.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataA.socket, playerData);
        }
        else if (CmsClientDataB.socket == socketInfo)
        {
            SendMsg(cs, MovieClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::TutoEnd:
    {
        cout << "TutoEnd" << endl;

        if (MovieClientDataA.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataA.socket, playerData);
        }
        else if (MovieClientDataB.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    case (UINT8)PROTOCOLSUB_CMS::RoundEnd:
    {
        cout << "RoundEnd" << endl;

        if (MovieClientDataA.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataA.socket, playerData);
        }
        else if (MovieClientDataB.socket == socketInfo)
        {
            SendMsg(cs, CmsClientDataB.socket, playerData);
        }
        else
        {
            cout << "socketInfo error!" << endl;
        }
    }
    break;
    default:
        break;
    }

    //SendMsg(cs, MovieClientData.socket, playerData);
}

void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData)
{
    char buf[BUFSIZE];

    //EnterCriticalSection(&cs);
    strcpy_s(buf, (char*)&playerData);
    send(socketInfo, buf, BUFSIZE, 0);
    //LeaveCriticalSection(&cs);
}

void SendMsg(CRITICAL_SECTION cs, SOCKET socketInfo, Player_Socket playerData, vector<string> SendDatas)
{
    EnterCriticalSection(&cs);

    for (int i = 0; i < SendDatas.size(); i++)
    {
        char buf[BUFSIZE];

        playerData.Flag = DATA_FLAG::SENDING;
        strcpy_s(playerData.Buffer, SendDatas[i].c_str());

        strcpy_s(buf, (char*)&playerData);
        send(socketInfo, buf, BUFSIZE, 0);

        Sleep(1);

        //cout << UrlDecodeLikeUnreal(SendDatas[i].c_str()) << endl;

        //cout << SendDatas[i] << endl;
    }

    char buf[BUFSIZE];
    string end = "end";
    playerData.Flag = DATA_FLAG::LISTEND;
    strcpy_s(playerData.Buffer, end.c_str());

    strcpy_s(buf, (char*)&playerData);
    send(socketInfo, buf, BUFSIZE, 0);

    LeaveCriticalSection(&cs);
}

vector<string> RemakeListUnderMaxBufferSize(vector<vector<string>> datas)
{
    vector<string> result;
    string data = "";
    string splitValue = "#";
    string splitColumn = "$";
    //for (int i = 0; i < krColumn.size(); i++)
    //{
    //    data += krColumn[i] + "#";
    //}
    //data.pop_back();
    //data += splitColumn;

    for (int i = 0; i < datas.size(); i++)
    {
        for (int j = 0; j < datas[0].size(); j++)
        {
            if(data.size() + datas[i][j].size() + splitValue.size() < BUFSIZE - 5)
            {
                if(j != datas[0].size() -1)
                    data += datas[i][j] + "#";
                else
                    data += datas[i][j] + "$";
            }
            else
            {
                if(data != "")
                    if(data.back() == '\0')
                        data.pop_back();

                data.pop_back();
                result.push_back(data);
                data.clear();
                j--;

                if (j != datas[0].size() - 1)
                    data += "#";
                else
                    data += "$";
            }
        }

        if (i == datas.size() - 1 && data != "")
        {
            if (data != "")
                if (data.back() == '\0')
                    data.pop_back();

            data.pop_back();
            result.push_back(data);
        }
    }

    return result;
}

vector<string> SplitBuffer(string buffer, string Split)
{
    return vector<string>();
}

int main()
{   
    //ProcessDB* processDB = new ProcessDB();

    //processDB->Init();

    //vector<vector<string>> logSearch = processDB->SearchData("logdata", Search_PlayData_EN_LOG_ColumnName.size(), SEARCH_DIRECTION_TYPE::HORIZON_TYPE);

    //vector<string> sendData = RemakeListUnderMaxBufferSize(logSearch);

    int retval;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

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

        SocketInfoList.insert({client_sock, socketInfo});

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