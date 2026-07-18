/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "Types.hpp"

typedef union _LARGE_INTEGER {
  struct {
    UINT32 LowPart;
    INT32  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    UINT32 LowPart;
    INT32  HighPart;
  } u;
  INT64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

extern "C"
{
  __declspec(dllimport) HANDLE GetProcessHeap();
  __declspec(dllimport) LPVOID HeapAlloc(HANDLE hHeap, UINT32 dwFlags, UINT64 dwBytes);
  __declspec(dllimport) BOOL HeapFree(HANDLE hHeap, UINT32 dwFlags, LPVOID lpMem);
  __declspec(dllimport) HANDLE GetStdHandle(UINT32 nStdHandle);
  __declspec(dllimport) BOOL WriteConsoleW(HANDLE hConsoleOutput, LPCWCHAR lpBuffer, UINT32 nNumberOfCharsToWrite, LPUINT32 lpNumberOfCharsWritten, LPVOID lpReserved);
  __declspec(dllimport) BOOL ReadConsoleW(HANDLE hConsoleInput, LPWCHAR lpBuffer, UINT32 nNumberOfCharsToRead, LPUINT32 lpNumberOfCharsRead, LPVOID pInputControl);
  __declspec(dllimport) BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, UINT32 nNumberOfBytesToWrite, LPUINT32 lpNumberOfBytesWritten, LPVOID lpOverlapped);
  __declspec(dllimport) BOOL ReadFile(HANDLE hFile, LPVOID Buffer, UINT32 nNumberOfBytesToRead, LPUINT32 lpNumberOfBytesRead, LPVOID lpOverlapped);
  __declspec(dllimport) BOOL CloseHandle(HANDLE hObject);
  __declspec(dllimport) UINT32 GetLastError();
  __declspec(dllimport) void ExitProcess(UINT32 uExitCode); 
  __declspec(dllimport) BOOL GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize);
  __declspec(dllimport) BOOL SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, UINT32 dwMoveMethod);
  __declspec(dllimport) HANDLE CreateFileW(LPCWCHAR lpFileName, UINT32 dwDesiredAccess, UINT32 dwShareMode, LPVOID lpSecurityAttributes, UINT32 dwCreationDisposition, UINT32 dwFlagsAndAttributes, HANDLE hTemplateFile);
  __declspec(dllimport) HANDLE CreateThread(LPVOID lpThreadAttributes, UINT64 dwStackSize, LPVOID lpStartAddress, LPVOID lpParameter, UINT32 dwCreationFlags, LPUINT32 lpThreadId);
  __declspec(dllimport) UINT32 ResumeThread(HANDLE hThread);
  __declspec(dllimport) BOOL TerminateThread(HANDLE hThread, UINT32 dwExitCode);
  __declspec(dllimport) UINT32 WaitForSingleObject(HANDLE hHandle, UINT32 dwMilliseconds); 
  __declspec(dllimport) HANDLE CreateMutexW(LPVOID lpMutexAttributes, BOOL bInitialOwner, LPCWCHAR lpName);
  __declspec(dllimport) BOOL ReleaseMutex(HANDLE hMutex);
  __declspec(dllimport) HANDLE CreateNamedPipeW(LPCWCHAR lpName, UINT32 dwOpenMode, UINT32 dwPipeMode, UINT32 nMaxInstances, UINT32 nOutBufferSize, UINT32 nInBufferSize, UINT32 nDefaultTimeOut, LPVOID lpSecurityAttributes);
  __declspec(dllimport) BOOL ConnectNamedPipe(HANDLE hNamedPipe, LPVOID lpOverlapped);
  __declspec(dllimport) BOOL DisconnectNamedPipe(HANDLE hNamedPipe);
  __declspec(dllimport) BOOL WaitNamedPipeW(LPCWCHAR lpNamedPipeName, UINT32 nTimeOut);
  __declspec(dllimport) LPVOID LocalFree(LPVOID hMem);
  __declspec(dllimport) LPWCHAR GetCommandLineW();
  __declspec(dllimport) LPWCHAR* CommandLineToArgvW(LPWCHAR lpCmdLine, LPINT32 pNumArgs);
}

#define STD_INPUT_HANDLE ((UINT32)-10)
#define STD_OUTPUT_HANDLE ((UINT32)-11)
#define STD_ERROR_HANDLE ((UINT32)-12)
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define GENERIC_READ 0x80000000 
#define GENERIC_WRITE 0x40000000
#define FILE_SHARE_READ 0x00000001
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define CREATE_SUSPENDED 0x00000004
#define WAIT_OBJECT_0 0x000000000L
#define WAIT_FAILED (UINT32)0xFFFFFFFF
#define WAIT_TIMEOUT 0x00000102L
#define PIPE_ACCESS_DUPLEX 0x00000003
#define PIPE_TYPE_BYTE 0x00000000
#define PIPE_WAIT 0x00000000
#define NMPWAIT_WAIT_FOREVER 0xffffffff