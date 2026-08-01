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

#define STACK_SIZE 50

namespace cl
{
  namespace SystemPlatform
  {
    namespace Panic
    {
      CYTEXLAB_API void Init();
      CYTEXLAB_API void StackPush(LPCECHAR Func, LPCECHAR File, UINT64 Line);
      CYTEXLAB_API void StackPop();
      CYTEXLAB_API void Panic(LPCECHAR Message, LPCECHAR File, UINT64 Line, UINT32 SystemError);
    }
  }
}