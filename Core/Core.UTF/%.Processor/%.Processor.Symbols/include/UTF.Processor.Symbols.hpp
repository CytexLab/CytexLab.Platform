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

#ifdef CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API_EXPORT
#define CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API __declspec(dllimport)
#endif

namespace cl
{
  namespace UTF
  {
    namespace Processor
    {
      class SymbolProcessor
      {
      public:
        enum class Error : UINT8
        {
          None = 0,
          NullPointer = 1,
          InvalidByte = 2,
          InvalidContinueByte = 3
        };

        struct Result
        {
          BOOL Success;
          Error Error;
          UINT8 ReadedInput;
          UINT8 WrittenOutput;
        };

        CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API static Result ConvertU8oU32(LPCCHAR U8_Char, LPECHAR U32_Char);
        CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API static Result ConvertU16oU32(LPCWCHAR U16_Char, LPECHAR U32_Char);
        CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API static Result ConvertU32oU8(LPCECHAR U32_Char, LPCHAR U8_Char);
        CYTEXLAB_CORE_UTF_PROCESSOR_SYMBOLS_API static Result ConvertU32oU16(LPCECHAR U32_Char, LPWCHAR U16_Char);
      };
    };
  }
}