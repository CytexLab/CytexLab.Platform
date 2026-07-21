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

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    UINT32  dwProcessId;
    UINT32  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _STARTUPINFOW {
    UINT32  cb;
    LPWCHAR lpReserved;
    LPWCHAR lpDesktop;
    LPWCHAR lpTitle;
    UINT32  dwX;
    UINT32  dwY;
    UINT32  dwXSize;
    UINT32  dwYSize;
    UINT32  dwXCountChars;
    UINT32  dwYCountChars;
    UINT32  dwFillAttribute;
    UINT32  dwFlags;
    INT32   wShowWindow;
    INT32   cbReserved2;
    LPUINT8 lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;


typedef INT64 (__stdcall *WNDPROC)(HANDLE, UINT32, UINT64, INT64);

struct WNDCLASSEXW
{
    UINT32 cbSize;
    UINT32 style;
    WNDPROC lpfnWndProc;
    INT32 cbClsExtra;
    INT32 cbWndExtra;
    HANDLE hInstance;
    HANDLE hIcon;
    HANDLE hCursor;
    HANDLE hbrBackground;
    LPCWCHAR lpszMenuName;
    LPCWCHAR lpszClassName;
    HANDLE hIconSm;
};

struct MSG {
    HANDLE hwnd;
    UINT32 message;
    UINT64 wParam;
    INT64 lParam;
    UINT32 time;
    struct { INT32 x; INT32 y; } pt;
};

struct PIXELFORMATDESCRIPTOR {
    UINT16 nSize;
    UINT16 nVersion;
    UINT32 dwFlags;
    UINT8 iPixelType;
    UINT8 cColorBits;
    UINT8 cRedBits;
    UINT8 cRedShift;
    UINT8 cGreenBits;
    UINT8 cGreenShift;
    UINT8 cBlueBits;
    UINT8 cBlueShift;
    UINT8 cAlphaBits;
    UINT8 cAlphaShift;
    UINT8 cAccumBits;
    UINT8 cAccumRedBits;
    UINT8 cAccumGreenBits;
    UINT8 cAccumBlueBits;
    UINT8 cAccumAlphaBits;
    UINT8 cDepthBits;
    UINT8 cStencilBits;
    UINT8 cAuxBuffers;
    UINT8 iLayerType;
    UINT8 bReserved;
    UINT32 dwLayerMask;
    UINT32 dwVisibleMask;
    UINT32 dwDamageMask;
};

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
    __declspec(dllimport) BOOL TerminateProcess(HANDLE hProcess, UINT32 uExitCode);
    __declspec(dllimport) BOOL CreateProcessW(LPCWCHAR lpApplicationName, LPWCHAR lpCommandLine, LPVOID lpProcessAttributes, LPVOID lpThreadAttributes, BOOL bInheritHandles, UINT32 dwCreationFlags, LPVOID lpEnvironment, LPCWCHAR lpCurrentDirectory, LPVOID lpStartupInfo, LPVOID lpProcessInformation);
    __declspec(dllimport) BOOL GetConsoleMode(HANDLE hConsoleHandle, LPUINT32 lpMode);
    __declspec(dllimport) UINT16 RegisterClassExW(LPCVOID lpwcx);
    __declspec(dllimport) HANDLE CreateWindowExW(UINT32 dwExStyle, LPCWCHAR lpClassName, LPCWCHAR lpWindowName, UINT32 dwStyle, INT32 X, INT32 Y, INT32 nWidth, INT32 nHeight, HANDLE hWndParent, HANDLE hMenu, HANDLE hInstance, LPVOID lpParam);
    __declspec(dllimport) BOOL ShowWindow(HANDLE hWindow, INT32 nCmdShow);
    __declspec(dllimport) BOOL UpdateWindow(HANDLE hWindow);
    __declspec(dllimport) HANDLE GetDC(HANDLE hWindow);
    __declspec(dllimport) INT32 ReleaseDC(HANDLE hWindow, HANDLE hDC);
    __declspec(dllimport) BOOL DestroyWindow(HANDLE hWindow);
    __declspec(dllimport) INT64 DefWindowProcW(HANDLE hWindow, UINT32 Msg, UINT64 wParam, INT64 lParam);
    __declspec(dllimport) BOOL PeekMessageW(LPVOID lpMsg, HANDLE hWnd, UINT32 wMsgFilterMin, UINT32 wMsgFilterMax, UINT32 wRemoveMsg);
    __declspec(dllimport) BOOL TranslateMessage(LPCVOID lpMsg);
    __declspec(dllimport) INT64 DispatchMessageW(LPCVOID lpMsg);
    __declspec(dllimport) void PostQuitMessage(INT32 nExitCode);
    __declspec(dllimport) HANDLE LoadCursorW(HANDLE hInstance, LPCWCHAR lpCursorName);
    __declspec(dllimport) HANDLE GetModuleHandleW(LPCWCHAR lpModuleName);
    __declspec(dllimport) INT32 ChoosePixelFormat(HANDLE hDC, LPCVOID pfd);
    __declspec(dllimport) BOOL SetPixelFormat(HANDLE hDC, INT32 format, LPCVOID pfd);
    __declspec(dllimport) BOOL SwapBuffers(HANDLE hDC);
    __declspec(dllimport) HANDLE wglCreateContext(HANDLE hDC);
    __declspec(dllimport) BOOL wglDeleteContext(HANDLE hGLRC);
    __declspec(dllimport) BOOL wglMakeCurrent(HANDLE hDC, HANDLE hGLRC);
    __declspec(dllimport) LPVOID wglGetProcAddress(LPCCHAR lpszProc);
    __declspec(dllimport) LPVOID GetProcAddress(HANDLE hModule, LPCCHAR lpProcName);
    __declspec(dllimport) HANDLE GetModuleHandleA(LPCCHAR lpModuleName);
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
#define CREATE_NO_WINDOW 0x08000000
#define DETACHED_PROCESS 0x00000008

#define CS_HREDRAW      0x0002
#define CS_VREDRAW      0x0001
#define CS_OWNDC        0x0020

#define WS_OVERLAPPED   0x00000000
#define WS_CAPTION      0x00C00000
#define WS_SYSMENU      0x00080000
#define WS_THICKFRAME   0x00040000
#define WS_MINIMIZEBOX  0x00020000
#define WS_MAXIMIZEBOX  0x00010000
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

#define CW_USEDEFAULT   0x80000000
#define SW_SHOW         5
#define PM_REMOVE       0x0001

#define WM_DESTROY      0x0002
#define WM_QUIT         0x0012
#define WM_CLOSE        0x0010

#define IDC_ARROW       (LPCWCHAR)((UINT64)32512)

#define PFD_DRAW_TO_WINDOW  0x00000004
#define PFD_SUPPORT_OPENGL  0x00000020
#define PFD_DOUBLEBUFFER    0x00000001
#define PFD_TYPE_RGBA       0
#define PFD_MAIN_PLANE      0

#define GL_COLOR_BUFFER_BIT 0x00004000