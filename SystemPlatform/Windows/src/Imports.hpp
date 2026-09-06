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
  __declspec(dllimport) void RtlExitUserProcess(UINT32 ExitStatus);
  __declspec(dllimport) UINT64 NtAllocateVirtualMemory(LPVOID ProcessHandle, LPVOID* BaseAddress, UINT64 ZeroBits, LPUINT64 RegionSize, UINT32 AllocationType, UINT32 Protect);
  __declspec(dllimport) UINT32 NtFreeVirtualMemory(LPVOID ProcessHandle, LPVOID* BaseAddress, LPUINT64 RegionSize, UINT32 FreeType);
}

#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD             0x100
#define PAGE_NOCACHE           0x200
#define PAGE_WRITECOMBINE      0x400
#define MEM_COMMIT             0x00001000
#define MEM_RESERVE            0x00002000
#define MEM_RESET              0x00080000
#define MEM_RELEASE            0x00008000
#define MEM_DECOMMIT           0x00004000
#define STATUS_SUCCESS         ((UINT32)0x00000000L)
#define NtCurrentProcess()     (LPVOID)-1