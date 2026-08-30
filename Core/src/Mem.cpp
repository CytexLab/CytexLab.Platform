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

#define CYTEXLAB_PLATFORM_EXPORT
#include "Mem.hpp"

typedef void (*memcpy_sse42_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*memcpy_avx_asm_func)(LPCVOID From, LPVOID To, UINT64 Count);
typedef void (*fail_callback_sign)(UINT64 code);

memcpy_sse42_asm_func memcpy_sse42_asm = nullptr;
memcpy_avx_asm_func memcpy_avx_asm = nullptr;

extern BOOL is_proc_support_sse42();
extern BOOL is_proc_support_avx();
extern fail_callback_sign get_fail_callback();

static BOOL support_sse42 = FALSE;
static BOOL support_avx = FALSE;
static BOOL updated_info = FALSE;

void update_info()
{
  support_sse42 = is_proc_support_sse42();
  support_avx = is_proc_support_avx();
  updated_info = TRUE;
}

CYTEXLAB_API void memcpy_sse42_set(memcpy_sse42_asm_func func)
{
  memcpy_sse42_asm = func;
}

CYTEXLAB_API void memcpy_avx_set(memcpy_avx_asm_func func)
{
  memcpy_avx_asm = func;
}

CYTEXLAB_API void memcpy_sse42(LPCVOID From, LPVOID To, UINT64 Count)
{
  if (!updated_info)
    update_info();

  if (Count % 16 != 0)
    get_fail_callback()(2);

  if (support_sse42)
    memcpy_sse42_asm(From, To, Count);
  else
    get_fail_callback()(1);
}

CYTEXLAB_API void memcpy_avx(LPCVOID From, LPVOID To, UINT64 Count)
{
  if (!updated_info)
    update_info();

  if (Count % 32 != 0)
    get_fail_callback()(4);

  if (support_avx)
    memcpy_avx_asm(From, To, Count);
  else
    get_fail_callback()(3);
}

CYTEXLAB_API void memcpy(LPCVOID From, LPVOID To, UINT64 Count)
{
  if (!updated_info)
    update_info();

  if (support_avx && Count >= 32 && (Count % 32 == 0))
    memcpy_sse42(From, To, Count);
  else if (support_sse42 && Count >= 16 && (Count % 16 == 0))
    memcpy_avx(From, To, Count);
  else
  {
    asm volatile (
      "rep movsb\n"
      :
      : "S" (From), "D" (To), "c" (Count)
      : "memory"
    );
  }
}