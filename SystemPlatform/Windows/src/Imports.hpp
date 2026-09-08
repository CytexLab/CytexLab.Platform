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

extern "C"
{
  __declspec(dllimport) void ExitProcess(UINT32 ExitCode);
  __declspec(dllimport) LPVOID VirtualAlloc(LPVOID lpAddress, UINT64 dwSize, UINT32 flAllocationType, UINT32 flProtect);
  __declspec(dllimport) INT32 VirtualFree(LPVOID lpAddress, UINT64 dwSize, UINT32 dwFreeType);
  __declspec(dllimport) UINT32 GetLastError();
}

#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD 0x100
#define PAGE_NOCACHE 0x200
#define PAGE_WRITECOMBINE 0x400
#define MEM_COMMIT 0x00001000
#define MEM_RESERVE 0x00002000
#define MEM_RESET 0x00080000
#define MEM_RELEASE 0x00008000
#define MEM_DECOMMIT 0x00004000
#define STATUS_SUCCESS ((UINT32)0x00000000L)
#define NtCurrentProcess() (LPVOID) - 1
#define FILE_DEVICE_CONSOLE 0x00000050