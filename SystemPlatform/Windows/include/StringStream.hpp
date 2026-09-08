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

#include "Stream.hpp"

namespace cl
{
  namespace SystemPlatform
  {
    class StringStream : public Stream
    {
    public:
      virtual StringStream& operator<<(LPCECHAR String) = 0;
      virtual StringStream& operator>>(LPECHAR Buffer) = 0;
    };
  }
}