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

#define CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API_EXPORT
#include "UTF.Processor.String.hpp"

CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API cl::UTF::Processor::StringProcessor::Result cl::UTF::Processor::StringProcessor::GenerateEmptyResult()
{
  return {
      TRUE,
      Error::None,
      {TRUE,
       SymbolProcessor::Error::None,
       0,
       0},
      {{0, 0},
       {0, 0}}};
}

CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API cl::UTF::Processor::StringProcessor::Result cl::UTF::Processor::StringProcessor::ConvertUTF8oUTF32(LPCCHAR U8_String, LPECHAR U32_String)
{
  Result result = GenerateEmptyResult();

  if (!U8_String || !U32_String)
  {
    result.Success = FALSE;
    result.Error = Error::NullPointer;
    return result;
  }

  while (TRUE)
  {
    if (*U8_String == '\0')
      break;

    SymbolProcessor::Result convert_symbol = SymbolProcessor::ConvertU8oU32(U8_String, U32_String);

    result.LastSymbol = convert_symbol;
    result.Metrics.Input.BytesReaded += convert_symbol.ReadedInput;
    result.Metrics.Input.SymbolsReaded++;
    result.Metrics.Output.BytesWritten += convert_symbol.WrittenOutput;
    result.Metrics.Output.SymbolsWritten++;

    if (!convert_symbol.Success)
    {
      result.Success = FALSE;
      result.Error = Error::FailConvertSymbol;
      return result;
    }

    U8_String += convert_symbol.ReadedInput;
    U32_String += convert_symbol.WrittenOutput;
  }

  *U32_String = U'\0';

  return result;
}

CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API cl::UTF::Processor::StringProcessor::Result cl::UTF::Processor::StringProcessor::ConvertUTF16oUTF32(LPCWCHAR U16_String, LPECHAR U32_String)
{
  Result result = GenerateEmptyResult();

  if (!U16_String || !U32_String)
  {
    result.Success = FALSE;
    result.Error = Error::NullPointer;
    return result;
  }

  while (TRUE)
  {
    if (*U16_String == L'\0')
      break;

    SymbolProcessor::Result convert_symbol = SymbolProcessor::ConvertU16oU32(U16_String, U32_String);

    result.LastSymbol = convert_symbol;
    result.Metrics.Input.BytesReaded += convert_symbol.ReadedInput * 2;
    result.Metrics.Input.SymbolsReaded++;
    result.Metrics.Output.BytesWritten += convert_symbol.WrittenOutput;
    result.Metrics.Output.SymbolsWritten++;

    if (!convert_symbol.Success)
    {
      result.Success = FALSE;
      result.Error = Error::FailConvertSymbol;
      return result;
    }

    U16_String += convert_symbol.ReadedInput;
    U32_String += convert_symbol.WrittenOutput;
  }

  *U32_String = U'\0';

  return result;
}

CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API cl::UTF::Processor::StringProcessor::Result cl::UTF::Processor::StringProcessor::ConvertUTF32oUTF8(LPCECHAR U32_String, LPCHAR U8_String)
{
  Result result = GenerateEmptyResult();

  if (!U8_String || !U32_String)
  {
    result.Success = FALSE;
    result.Error = Error::NullPointer;
    return result;
  }

  while (TRUE)
  {
    if (*U32_String == U'\0')
      break;

    SymbolProcessor::Result convert_symbol = SymbolProcessor::ConvertU32oU8(U32_String, U8_String);

    result.LastSymbol = convert_symbol;
    result.Metrics.Input.BytesReaded += convert_symbol.ReadedInput;
    result.Metrics.Input.SymbolsReaded++;
    result.Metrics.Output.BytesWritten += convert_symbol.WrittenOutput;
    result.Metrics.Output.SymbolsWritten++;

    if (!convert_symbol.Success)
    {
      result.Success = FALSE;
      result.Error = Error::FailConvertSymbol;
      return result;
    }

    U8_String += convert_symbol.WrittenOutput;
    U32_String += convert_symbol.ReadedInput;
  }

  *U8_String = U'\0';

  return result;
}

CYTEXLAB_CORE_UTF_PROCESSOR_STRING_API cl::UTF::Processor::StringProcessor::Result cl::UTF::Processor::StringProcessor::ConvertUTF32oUTF16(LPCECHAR U32_String, LPWCHAR U16_String)
{
  Result result = GenerateEmptyResult();

  if (!U16_String || !U32_String)
  {
    result.Success = FALSE;
    result.Error = Error::NullPointer;
    return result;
  }

  while (TRUE)
  {
    if (*U32_String == U'\0')
      break;

    SymbolProcessor::Result convert_symbol = SymbolProcessor::ConvertU32oU16(U32_String, U16_String);

    result.LastSymbol = convert_symbol;
    result.Metrics.Input.BytesReaded += convert_symbol.ReadedInput * 2;
    result.Metrics.Input.SymbolsReaded++;
    result.Metrics.Output.BytesWritten += convert_symbol.WrittenOutput;
    result.Metrics.Output.SymbolsWritten++;

    if (!convert_symbol.Success)
    {
      result.Success = FALSE;
      result.Error = Error::FailConvertSymbol;
      return result;
    }

    U16_String += convert_symbol.WrittenOutput;
    U32_String += convert_symbol.ReadedInput;
  }

  *U16_String = L'\0';

  return result;
}