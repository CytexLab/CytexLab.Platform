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

#include "StackStream.hpp"
#include "Imports.hpp"

void strcat(LPECHAR To, LPCECHAR From)
{
  while (*From)
  {
    *To++ = *From++;
  }
  *To = U'\0';
}

StackStream::StackStream(StackItem* Stack, UINT64 Count)
{
  this->stack = Stack;
  this->count = Count;
}

cl::SystemPlatform::Stream& StackStream::operator<<(LPCUINT8)
{
  ExitProcess(-8);
}

cl::SystemPlatform::Stream& StackStream::operator>>(LPUINT8)
{
  return *this;
}

cl::SystemPlatform::StringStream& StackStream::operator<<(LPCECHAR)
{
  ExitProcess(-8);
}

cl::SystemPlatform::StringStream& StackStream::operator>>(LPECHAR Buffer)
{
  strcat(Buffer, U"============ [ Stack trace ] ============");

  return *this;
}