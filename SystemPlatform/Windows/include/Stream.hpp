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

namespace cl
{
  namespace SystemPlatform
  {
    class Stream
    {
    public:
      virtual Stream& operator<<(LPCUINT8 Bytes) = 0;
      virtual Stream& operator>>(LPUINT8 Buffer) = 0;
    };
  }
}