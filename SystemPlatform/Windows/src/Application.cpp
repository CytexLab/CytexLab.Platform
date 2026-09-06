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

#define CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API_EXPORT

#include "Application.hpp"
#include "Imports.hpp"

#define SYSTEM_POOL_SIZE 1024 * 4 * 16

typedef void (*fail_callback_sign)(UINT64 code);
typedef void (*memcpy_sse42_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*memcpy_avx_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*memset_sse42_asm_func)(LPVOID Mem, UINT8 Byte, UINT64 Count);
typedef void (*memset_avx_asm_func)(LPVOID Mem, UINT8 Byte, UINT64 Count);

__declspec(dllimport) void proc_support(BOOL sse42, BOOL avx);
__declspec(dllimport) void set_fail_callback(fail_callback_sign callback);
__declspec(dllimport) void memcpy_sse42_set(memcpy_sse42_asm_func func);
__declspec(dllimport) void memcpy_avx_set(memcpy_avx_asm_func func);
__declspec(dllimport) void memset_sse42_set(memset_sse42_asm_func func);
__declspec(dllimport) void memset_avx_set(memset_avx_asm_func func);

extern "C" void memcpy_sse42_asm(LPCVOID From, LPVOID To, UINT64 Count);
extern "C" void memcpy_avx_asm(LPCVOID From, LPVOID To, UINT64 Count);
extern "C" void memset_sse42_asm(LPVOID To, UINT8 Byte, UINT64 Count);
extern "C" void memset_avx_asm(LPVOID To, UINT8 Byte, UINT64 Count);

static LPVOID SystemPool;
static UINT64 Free;

void core_fail_callback(UINT64 Code)
{
  RtlExitUserProcess(-5);
}

LPVOID AllocateSystemPool(UINT64 Size)
{
  if (Size > Free)
    RtlExitUserProcess(-4);

  LPVOID p = SystemPool;
  SystemPool = (LPUINT8)SystemPool - Size;
  Free -= Size;
  return p;
}

CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void cl::SystemPlatform::Application::Init()
{
  if (this->inited == TRUE)
    this->Exit(-1);

  BOOL support_sse42 = FALSE;
  BOOL support_avx = FALSE;

  UINT32 eax = 0;
  UINT32 ecx = 0;
  UINT32 ebx = 0;
  UINT32 edx = 0;

  asm volatile (
    "cpuid"
    : "=c"(ecx), "=a"(eax), "=b"(ebx), "=d"(edx)
    : "a"(1)
  );

  support_sse42 = ecx >> 20 & 1;
  support_avx = ecx >> 28 & 1 & (ecx >> 27 & 1);

  proc_support(support_sse42, support_avx);
  set_fail_callback(core_fail_callback);
  memcpy_sse42_set(memcpy_sse42_asm);
  memcpy_avx_set(memcpy_avx_asm);
  memset_sse42_set(memset_sse42_asm);
  memset_avx_set(memset_avx_asm);

  UINT64 size = SYSTEM_POOL_SIZE;
  UINT32 status = NtAllocateVirtualMemory(NtCurrentProcess(), &SystemPool, 0, &size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  if (status != STATUS_SUCCESS)
    RtlExitUserProcess(-2);

  this->inited = TRUE;
}

CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void cl::SystemPlatform::Application::Exit(UINT32 Code)
{
  UINT64 size = SYSTEM_POOL_SIZE;
  UINT32 status = NtFreeVirtualMemory(NtCurrentProcess(), &SystemPool, &size, MEM_RELEASE);

  if (status != STATUS_SUCCESS)
    RtlExitUserProcess(-3);

  RtlExitUserProcess(Code);
}