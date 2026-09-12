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
    number *= 10;
    number += n;
    String++;
  }

  *Int = number;
  return result;
}