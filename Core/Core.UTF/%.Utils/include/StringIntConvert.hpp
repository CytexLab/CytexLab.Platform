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

        Result ConvertStringToInt(LPCECHAR String, LPUINT64 Int);
        Result ConvertStringToInt(LPCECHAR String, LPINT64 Int);
        Result ConvertIntToString(LPUINT64 Int, LPECHAR String);
        Result ConvertIntToString(LPINT64 Int, LPECHAR String);
      };
    }
  } // namespace UTF
} // namespace cl