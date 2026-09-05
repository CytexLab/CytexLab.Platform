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

#define CYTEXLAB_PLATFORM_EXPORT
#include "UTF.Processor.hpp"

CYTEXLAB_API cl::UTF::Processor::SymbolProcessor::Result cl::UTF::Processor::SymbolProcessor::ConvertU8oU32(LPCCHAR U8_Char, LPECHAR U32_Char)
{
  Result result = {TRUE, Error::None, 0, 0};

  if (!U8_Char || !U32_Char)
  {
    result = {FALSE, Error::NullPointer, 0, 0};
    return result;
  }

  CHAR one = *U8_Char++;

  if ((one & 0x80) == 0x00)
  {
    ECHAR out = one;
    *U32_Char = out;
    result.ReadedInput = 1;
    result.WrittenOutput = 1;
    return result;
  }
  else if ((one & 0xE0) == 0xC0)
  {
    CHAR two = *U8_Char++;
    if ((two & 0xC0) != 0x80)
    {
      result = {FALSE, Error::InvalidContinueByte, 0, 0};
      return result;
    }

    ECHAR out = (((ECHAR)(one & 0x1F)) << 6) | ((ECHAR)(two & 0x3F));
    *U32_Char = out;
    result.ReadedInput = 2;
    result.WrittenOutput = 1;
    return result;
  }
  else if ((one & 0xF0) == 0xE0)
  {
    CHAR two = *U8_Char++;
    CHAR three = *U8_Char++;
    if ((two & 0xC0) != 0x80 || (three & 0xC0) != 0x80)
    {
      result = {FALSE, Error::InvalidContinueByte, 0, 0};
      return result;
    }

    ECHAR out = (((ECHAR)(one & 0x0F)) << 12) | (((ECHAR)(two & 0x3F)) << 6) | ((ECHAR)(three & 0x3F));
    *U32_Char = out;
    result.ReadedInput = 3;
    result.WrittenOutput = 1;
    return result;
  }
  else if ((one & 0xF8) == 0xF0)
  {
    CHAR two = *U8_Char++;
    CHAR three = *U8_Char++;
    CHAR four = *U8_Char++;
    if ((two & 0xC0) != 0x80 || (three & 0xC0) != 0x80 || (four & 0xC0) != 0x80)
    {
      result = {FALSE, Error::InvalidContinueByte, 0, 0};
      return result;
    }

    ECHAR out = (((ECHAR)(one & 0x07)) << 18) | (((ECHAR)(two & 0x3F)) << 12) | (((ECHAR)(three & 0x3F)) << 6) | ((ECHAR)(four & 0x3F));
    *U32_Char = out;
    result.ReadedInput = 4;
    result.WrittenOutput = 1;
    return result;
  }
  else
  {
    result = {FALSE, Error::InvalidByte, 0, 0};
    return result;
  }
}

CYTEXLAB_API cl::UTF::Processor::SymbolProcessor::Result cl::UTF::Processor::SymbolProcessor::ConvertU16oU32(LPCWCHAR U16_Char, LPECHAR U32_Char)
{
  Result result = {TRUE, Error::None, 0, 0};

  if (!U16_Char || !U32_Char)
  {
    result = {FALSE, Error::NullPointer, 0, 0};
    return result;
  }

  WCHAR one = *U16_Char++;

  if (one <= 0xD7FF || (one >= 0xE000 && one <= 0xFFFF))
  {
    ECHAR out = one;
    *U32_Char = out;
    result.ReadedInput = 1; result.WrittenOutput = 1;
    return result;
  }
  else if ((one & 0xFC00) == 0xD800)
  {
    WCHAR two = *U16_Char++;
    if ((two & 0xFC00) != 0xDC00)
    {
      result = {FALSE, Error::InvalidContinueByte, 0, 0};
      return result;
    }

    ECHAR out = ((ECHAR)(one & 0x3FF) << 10 | (ECHAR)(two & 0x3FF)) + 0x10000;
    *U32_Char = out;

    result.ReadedInput = 2; result.WrittenOutput = 1;
    return result;
  }
  else
  {
    result = {FALSE, Error::InvalidByte, 0, 0};
    return result;
  }
}