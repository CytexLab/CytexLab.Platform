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
#include "UTF.Processor.Symbols.hpp"

#ifdef CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API_EXPORT
#define CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API __declspec(dllexport)
#else
#define CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API __declspec(dllimport)
#endif

namespace cl
{
  namespace UTF
  {
    namespace Processor
    {
      class StringProcessor
      {
      public:
        enum class Error : UINT8
        {
          None = 0,
          NullPointer = 1,
          FailConvertSymbol = 2,
        };

        struct InputReaded
        {
          UINT64 SymbolsReaded;
          UINT64 BytesReaded;
        };

        struct OutputWritten
        {
          UINT64 SymbolsWritten;
          UINT64 BytesWritten;
        };

        struct Metrics
        {
          InputReaded Input;
          OutputWritten Output;
        };

        struct Result
        {
          BOOL Success;
          Error Error;
          SymbolProcessor::Result LastSymbol;
          Metrics Metrics;
        };

        CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API static Result GenerateEmptyResult();
        CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API static Result ConvertUTF8oUTF32(LPCCHAR U8_String, LPECHAR U32_String);
        CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API static Result ConvertUTF16oUTF32(LPCWCHAR U16_String, LPECHAR U32_String);
        CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API static Result ConvertUTF32oUTF8(LPCECHAR U32_String, LPCHAR U8_String);
        CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API static Result ConvertUTF32oUTF16(LPCECHAR U32_String, LPWCHAR U16_String);
      };
    }
  }
}