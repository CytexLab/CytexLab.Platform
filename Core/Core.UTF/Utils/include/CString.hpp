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

#ifdef CYTEXLAB_CORE_UTF_UTILS_API_EXPORT
#define CYTEXLAB_CORE_UTF_UTILS_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_UTF_UTILS_API __declspec(dllimport)
#endif

#include "Platform.hpp"

namespace cl
{
  namespace UTF
  {
    namespace Utils
    {
      CYTEXLAB_CORE_UTF_UTILS_API void StrCat(LPECHAR To, LPCECHAR From);
      CYTEXLAB_CORE_UTF_UTILS_API void StrCpy(LPECHAR From, LPECHAR To);
    } // namespace Utils
  } // namespace UTF
} // namespace cl