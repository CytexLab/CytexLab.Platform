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

#include "Mem.hpp"
#include "Platform.hpp"

typedef void (*fail_callback_sign)(UINT64 code);
typedef void (*memcpy_sse42_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*memcpy_avx_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*memset_sse42_asm_func)(LPVOID To, UINT8 Byte, UINT64 Count);
typedef void (*memset_avx_asm_func)(LPVOID To, UINT8 Byte, UINT64 Count);

CYTEXLAB_API void proc_support(BOOL sse42, BOOL avx);
CYTEXLAB_API void set_fail_callback(fail_callback_sign callback);
CYTEXLAB_API void memcpy_sse42_set(memcpy_sse42_asm_func func);
CYTEXLAB_API void memcpy_avx_set(memcpy_avx_asm_func func);
CYTEXLAB_API void memset_sse42_set(memset_sse42_asm_func func);
CYTEXLAB_API void memset_avx_set(memset_avx_asm_func func);

extern "C" void memcpy_sse42_asm(LPCVOID From, LPVOID To, UINT64 Count);
extern "C" void memcpy_avx_asm(LPCVOID From, LPVOID To, UINT64 Count);
extern "C" void memset_sse42_asm(LPVOID To, UINT8 Byte, UINT64 Count);
extern "C" void memset_avx_asm(LPVOID To, UINT8 Byte, UINT64 Count);

void callback(UINT64 code)
{
}

extern "C" void startup()
{
  proc_support(TRUE, TRUE);
  set_fail_callback(callback);
  memset_sse42_set(memset_sse42_asm);
  memset_avx_set(memset_avx_asm);

  UINT8 buf[64];

  memset(buf, 0xAB, 64);
}