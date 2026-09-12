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

#define CYTEXLAB_CORE_API __declspec(dllexport)

#include "Platform.hpp"

typedef void (*fail_callback_sign)(UINT64 code);

static BOOL support_sse42 = FALSE;
static BOOL support_avx = FALSE;

fail_callback_sign fail_callback;

CYTEXLAB_CORE_API void proc_support(BOOL sse42, BOOL avx)
{
  support_sse42 = sse42;
  support_avx = avx;
}

CYTEXLAB_CORE_API void set_fail_callback(fail_callback_sign callback)
{
  fail_callback = callback;
}

CYTEXLAB_CORE_API fail_callback_sign get_fail_callback()
{
  return fail_callback;
}

CYTEXLAB_CORE_API BOOL is_proc_support_sse42()
{
  return support_sse42;
}

CYTEXLAB_CORE_API BOOL is_proc_support_avx()
{
  return support_avx;
}