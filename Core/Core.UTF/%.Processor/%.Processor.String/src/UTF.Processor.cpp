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
    {
      TRUE,
      SymbolProcessor::Error::None,
      0,
      0
    },
    {
      {
        0, 0
      },
      {
        0, 0
      }
    }
  };
}