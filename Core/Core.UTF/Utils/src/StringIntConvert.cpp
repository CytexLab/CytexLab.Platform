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

#define CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API_EXPORT
#include "StringIntConvert.hpp"

#define INT64_MIN -9223372036854775808LL
#define INT64_MINU 9223372036854775808ULL
#define INT64_MAX 9223372036854775807LL
#define INT64_MAX_DIV10 INT64_MAX / 10
#define INT64_MAX_MOD10 INT64_MAX % 10
#define UINT64_MAX 18446744073709551615ULL
#define UINT64_MAX_DIV10 UINT64_MAX / 10
#define UINT64_MAX_MOD10 UINT64_MAX % 10

CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API cl::UTF::Utils::StringIntConvert::Result cl::UTF::Utils::StringIntConvert::ConvertStringToInt(LPCECHAR String, LPUINT64 Int)
{
  Result result = {TRUE, Error::None};

  if (String == nullptr || Int == nullptr)
  {
    result = {FALSE, Error::NullPointer};
    return result;
  }

  if (*String == U'-')
  {
    result = {FALSE, Error::InvalidNumber};
    return result;
  }

  if (*String == U'0')
  {
    *Int = 0;
    return result;
  }

  UINT64 number = 0;

  while (*String)
  {
    UINT64 n = *String - U'0';

    if (n < 0 || n > 9)
    {
      result = {FALSE, Error::InvalidNumber};
      return result;
    }

    if (number > UINT64_MAX_DIV10 || (number == UINT64_MAX_DIV10 && n > UINT64_MAX_MOD10))
    {
      result = {FALSE, Error::BufferOverflow};
      return result;
    }

    number *= 10;
    number += n;
    String++;
  }

  *Int = number;
  return result;
}

CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API cl::UTF::Utils::StringIntConvert::Result cl::UTF::Utils::StringIntConvert::ConvertStringToInt(LPCECHAR String, LPINT64 Int)
{
  Result result = {TRUE, Error::None};

  if (!String || !Int)
  {
    result = {FALSE, Error::NullPointer};
    return result;
  }

  BOOL isNegative = FALSE;

  if (*String == U'-')
  {
    isNegative = TRUE;
    String++;
  }

  if (*String == U'0')
  {
    *Int = 0;
    return result;
  }

  INT64 number = 0;

  while (*String)
  {
    INT64 n = *String - U'0';

    if (n < 0 || n > 9)
    {
      result = {FALSE, Error::InvalidNumber};
      return result;
    }

    if (number > INT64_MAX_DIV10 || (number == INT64_MAX_DIV10 && n > INT64_MAX_MOD10))
    {
      result = {FALSE, Error::BufferOverflow};
      return result;
    }

    number *= 10;
    number += n;
    String++;
  }

  if (isNegative == TRUE)
  {
    if (number > INT64_MINU)
    {
      result = {FALSE, Error::BufferOverflow};
      return result;
    }

    number = -number;
  }

  *Int = number;
  return result;
}

CYTEXLAB_CORE_UTF_UTILS_STRINGINTCONVERT_API cl::UTF::Utils::StringIntConvert::Result cl::UTF::Utils::StringIntConvert::ConvertIntToString(LPCUINT64 Int, LPECHAR String)
{
  Result result = {TRUE, Error::None};

  if (!String || !Int)
  {
    result = {FALSE, Error::None};
    return result;
  }

  ECHAR buf[21];
  UINT8 count = 0;
  UINT64 number = *Int;

  while (number > 0)
  {
    buf[count++] = U'0' + number % 10;
    number /= 10;
  }

  for (UINT8 i = count; i > 0; i--)
  {
    *String = buf[i - 1];
    String++;
  }

  *String = U'\0';

  return result;
}