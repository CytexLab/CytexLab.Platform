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
extern "C" void memcpy_avx_asm(LPCVOID From, LPVOID To, UINT64 Count);

void callback(UINT64 code)
{
}

extern "C" void startup()
{
  proc_support(TRUE, TRUE);
  set_fail_callback(callback);
  memcpy_sse42_set(memcpy_sse42_asm);
  memcpy_avx_set(memcpy_avx_asm);

  UINT8 buf1[32] = {0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x9,  0xA,  0xB,  0xC,  0xD,  0xE,  0xF,
                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
  UINT8 buf2[32];

  memcpy(buf1, buf2, 32);
}