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

#ifdef CYTEXLAB_CORE_MEM_API_EXPORT
#define CYTEXLAB_CORE_MEM_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_MEM_API __declspec(dllimport)
#endif

extern "C"
{
  CYTEXLAB_CORE_MEM_API void memcpy(LPVOID To, LPCVOID From, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memcpy_sse42(LPCVOID From, LPVOID To, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memcpy_avx(LPCVOID From, LPVOID To, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memset_sse42(LPVOID To, UINT8 Byte, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memset_avx(LPVOID To, UINT8 Byte, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memset(LPVOID To, UINT8 Byte, UINT64 Count);
  CYTEXLAB_CORE_MEM_API void memclear(LPVOID To, UINT64 Count);
}