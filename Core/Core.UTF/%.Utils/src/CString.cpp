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

#define CYTEXLAB_CORE_UTF_UTILS_API_EXPORT
#include "CString.hpp"

CYTEXLAB_CORE_UTF_UTILS_API void cl::UTF::Utils::StrCat(LPECHAR To, LPCECHAR From)
{
  while (*From)
  {
    *To++ = *From++;
  }
  *To = U'\0';
}

CYTEXLAB_CORE_UTF_UTILS_API void cl::UTF::Utils::StrCpy(LPECHAR From, LPECHAR To)
{
  while (*From)
  {
    *To++ = *From++;
  }
  *To = U'\0';
}