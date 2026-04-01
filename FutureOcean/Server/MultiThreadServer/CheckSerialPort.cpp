#include <windows.h>
#include <iostream>
#include "CheckSerialPort.h"

CSerialPort::CSerialPort(void)
{
}

CSerialPort::~CSerialPort(void)
{
}

bool CSerialPort::OpenPort()
{
    m_hComm = CreateFile(
        "\\\\.\\COM20",                    // 포트 이름
        GENERIC_READ | GENERIC_WRITE,      // 읽기/쓰기 접근
        0,                                 // 공유 없음
        NULL,                              // 보안 속성 없음
        OPEN_EXISTING,                     // 존재하는 포트만 열기
        0,                                 // 동기식 I/O
        NULL);                             // 템플릿 없음

    if (m_hComm == INVALID_HANDLE_VALUE)
        return false;
    else
        return true;
}

void CSerialPort::ClosePort()
{
    CloseHandle(m_hComm);
    return;
}

bool CSerialPort::ReadByte(BYTE& resp)
{
    BYTE rx;
    resp = 0;

    DWORD dwBytesTransferred = 0;

    if (ReadFile(m_hComm, &rx, 1, &dwBytesTransferred, 0))
    {
        if (dwBytesTransferred == 1)
        {
            resp = rx;
            return true;
        }
    }

    return false;
}

bool CSerialPort::ReadByte(BYTE*& resp, UINT size)
{
    DWORD dwBytesTransferred = 0;

    if (ReadFile(m_hComm, resp, size, &dwBytesTransferred, 0))
    {
        if (dwBytesTransferred == size)
            return true;
    }

    return false;
}

bool CSerialPort::WriteByte(BYTE bybyte)
{
    int iBytesWritten = 0;

    if (WriteFile(m_hComm, &bybyte, 1, &m_iBytesWritten, NULL) == 0)
        return false;
    else
        return true;
}

bool CSerialPort::SetCommunicationTimeouts(DWORD ReadIntervalTimeout, DWORD ReadTotalTimeoutMultiplier, DWORD ReadTotalTimeoutConstant, DWORD WriteTotalTimeoutMultiplier, DWORD WriteTotalTimeoutConstant)
{
    if ((m_bPortReady = GetCommTimeouts(m_hComm, &m_CommTimeouts)) == 0)
        return false;

    m_CommTimeouts.ReadIntervalTimeout = ReadIntervalTimeout;
    m_CommTimeouts.ReadTotalTimeoutConstant = ReadTotalTimeoutConstant;
    m_CommTimeouts.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;
    m_CommTimeouts.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;
    m_CommTimeouts.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;

    m_bPortReady = SetCommTimeouts(m_hComm, &m_CommTimeouts);

    if (m_bPortReady == 0)
    {
        std::cerr << "StCommTimeouts function failed : COM Port Error" << std::endl;
        CloseHandle(m_hComm);

        return false;
    }

    return true;
}

bool CSerialPort::ConfigurePort(DWORD BaudRate, BYTE ByteSize, DWORD fParity, BYTE Parity, BYTE StopBits)
{
    if ((m_bPortReady = GetCommState(m_hComm, &m_dcb)) == 0)
    {
        std::cerr << "GetCommState Error" << std::endl;
        CloseHandle(m_hComm);

        return false;
    }

    m_dcb.BaudRate = BaudRate;
    m_dcb.ByteSize = ByteSize;
    m_dcb.Parity = Parity;
    m_dcb.StopBits = StopBits;
    m_dcb.fBinary = true;
    m_dcb.fDsrSensitivity = false;
    m_dcb.fParity = fParity;
    m_dcb.fOutX = false;
    m_dcb.fInX = false;
    m_dcb.fNull = false;
    m_dcb.fAbortOnError = true;
    m_dcb.fOutxCtsFlow = false;
    m_dcb.fOutxDsrFlow = false;
    m_dcb.fDtrControl = DTR_CONTROL_DISABLE;
    m_dcb.fDsrSensitivity = false;
    m_dcb.fRtsControl = RTS_CONTROL_DISABLE;
    m_dcb.fOutxCtsFlow = false;
    m_dcb.fOutxCtsFlow = false;

    m_bPortReady = SetCommState(m_hComm, &m_dcb);

    if (m_bPortReady == 0)
    {
        std::cerr << "SetCommState Error" << std::endl;
        CloseHandle(m_hComm);

        return false;
    }

    return true;
}

void CSerialPort::SerialPortInit()
{
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

        if (_serial.ReadByte(pByte, 2))
        {
            std::cerr << "Test" << std::endl;
        }
        else
        {
            //::OutputDebugString(_T("Failed to read data\n"));
        }

        delete[] pByte;
    }
    else
    {
        //::OutputDebugString(_T("Failed to Open Port\n"));
    }

    _serial.ClosePort();
}