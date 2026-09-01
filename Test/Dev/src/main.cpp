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

CYTEXLAB_API void proc_support(BOOL sse42, BOOL avx);
CYTEXLAB_API void set_fail_callback(fail_callback_sign callback);
CYTEXLAB_API void memcpy_sse42_set(memcpy_sse42_asm_func func);
CYTEXLAB_API void memcpy_avx_set(memcpy_avx_asm_func func);

extern "C" void memcpy_sse42_asm(LPCVOID From, LPVOID To, UINT64 Count);

void callback(UINT64 code)
{
}

extern "C" void startup()
{
  proc_support(FALSE, FALSE);
  set_fail_callback(callback);
  memcpy_sse42_set(memcpy_sse42_asm);

  UINT8 buf1[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
  UINT8 buf2[32];

  memcpy_sse42(buf1, buf2, 16);
}