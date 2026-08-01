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
  __declspec(dllimport) HANDLE GetProcessHeap();
  __declspec(dllimport) LPVOID HeapAlloc(HANDLE hHeap, UINT32 dwFlags, UINT64 dwBytes);
  __declspec(dllimport) BOOL HeapFree(HANDLE hHeap, UINT32 dwFlags, LPVOID lpMem);
  __declspec(dllimport) void ExitProcess(UINT32 uExitCode);
}