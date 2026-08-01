/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
 */

#pragma once

#include "Platform.hpp"

typedef LPVOID HANDLE;

extern "C"
{
  // API
  __declspec(dllimport) UINT32 GetLastError();

  // Память
  __declspec(dllimport) HANDLE GetProcessHeap();
  __declspec(dllimport) LPVOID HeapAlloc(HANDLE hHeap, UINT32 dwFlags, UINT64 dwBytes);
  __declspec(dllimport) INT32 HeapFree(HANDLE hHeap, UINT32 dwFlags, LPVOID lpMem);

  // Процессы
  __declspec(dllimport) void ExitProcess(UINT32 uExitCode);

  // Консоль
  __declspec(dllimport) HANDLE GetStdHandle(UINT32 dwHandle);
  __declspec(dllimport) INT32 WriteConsoleW(HANDLE hConsoleOutput, LPCWCHAR lpBuffer, UINT32 nNumberOfCharsToWrite, LPUINT32 lpNumberOfCharsWritten, LPVOID lpReserved);
  __declspec(dllimport) INT32 GetConsoleMode(HANDLE hConsoleHandle, LPUINT32 lpMode);

  // Файлы
  __declspec(dllimport) INT32 WriteFile(HANDLE hFile, LPCVOID lpBuffer, UINT32 nNumberOfBytesToWrite, LPUINT32 lpNumberOfBytesWritten, LPVOID lpOverlapped);
}

// Константы

#define STD_OUTPUT_HANDLE ((UINT32) - 11)