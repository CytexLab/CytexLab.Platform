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

#ifdef CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API_EXPORT
#define CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API __declspec(dllimport)
#endif

#include "Platform.hpp"

namespace cl
{
  namespace UTF
  {
    namespace Utils
    {
      class StringIntConvert
      {
      public:
        enum class Error : UINT8
        {
          None = 0,
          NullPointer = 1,
          BufferOverflow = 2,
          InvalidNumber = 3,
        };

        struct Result
        {
          BOOL Success;
          Error Error;
        };

        CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API static Result ConvertStringToInt(LPCECHAR String, LPUINT64 Int);
        CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API static Result ConvertStringToInt(LPCECHAR String, LPINT64 Int);
        CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API static Result ConvertIntToString(LPCUINT64 Int, LPECHAR String);
        // CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API static Result ConvertIntToString(LPCINT64 Int, LPECHAR String);
      };
    } // namespace Utils
  } // namespace UTF
} // namespace cl