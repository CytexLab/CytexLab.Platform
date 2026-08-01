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
  CYTEXLAB_API void memcpy(LPVOID To, LPCVOID From, UINT64 Count);
  CYTEXLAB_API void memset(LPVOID To, UINT8 Byte, UINT64 Count);
  CYTEXLAB_API void memmove(LPVOID To, LPCVOID From, UINT64 Count);
  CYTEXLAB_API BOOL memcmp(LPCVOID Mem1, LPCVOID Mem2, UINT64 Count);
}