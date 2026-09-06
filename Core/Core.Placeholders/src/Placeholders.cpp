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

#include "Platform.hpp"

#define CYTEXLAB_CORE_PLACEHOLDERS_API __declspec(dllexport)

extern "C" CYTEXLAB_CORE_PLACEHOLDERS_API INT32 __cdecl _purecall(void)
{
  return 0;
}