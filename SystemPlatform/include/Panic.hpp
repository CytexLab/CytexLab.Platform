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
      CYTEXLAB_API void StackPush(LPCCHAR Func, LPCCHAR File, UINT64 Line);
      CYTEXLAB_API void StackPop();
      CYTEXLAB_API void Panic(LPCECHAR Message, LPCCHAR Function, LPCCHAR File, UINT64 Line, UINT32 SystemError);

      class StackItem
      {
      public:
        StackItem(LPCCHAR Function, LPCCHAR File, UINT64 Line)
        {
          StackPush(Function, File, Line);
        }

        ~StackItem()
        {
          StackPop();
        }
      };
    } // namespace Panic
  } // namespace SystemPlatform
} // namespace cl

#ifdef CYTEXLAB_DEBUG
#define STACK_FRAME() cl::SystemPlatform::Panic::StackItem ___stack_item(__PRETTY_FUNCTION__, __FILE__, __LINE__)
#define ASSERT(cond, msg) \
  if (!(cond))            \
  cl::SystemPlatform::Panic::Panic(msg, __PRETTY_FUNCTION__, __FILE__, __LINE__, 0)
#else
#define STACK_FRAME() ()
#define ASSERT(cond, msg) ()
#endif

#define PANIC(msg) cl::SystemPlatform::Panic::Panic(msg, __PRETTY_FUNCTION__, __FILE__, __LINE__, 0)