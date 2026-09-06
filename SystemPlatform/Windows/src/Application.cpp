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

#define CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API_EXPORT

#include "Application.hpp"
#include "Imports.hpp"

CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void cl::SystemPlatform::Application::Init()
{
  if (this->inited == TRUE)
    this->Exit(-1);

  this->inited = TRUE;
}

CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void cl::SystemPlatform::Application::Exit(UINT32 Code)
{
  RtlExitUserProcess(Code);
}