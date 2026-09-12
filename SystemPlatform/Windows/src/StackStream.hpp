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

#include "Stack.hpp"
#include "StringStream.hpp"

class StackStream : public cl::SystemPlatform::StringStream
{
private:
  StackItem* stack = nullptr;
  UINT64 count = 0;

public:
  StackStream(StackItem* Stack, UINT64 Count);

  Stream& operator<<(LPCUINT8) override;
  Stream& operator>>(LPUINT8) override;
  StringStream& operator<<(LPCECHAR) override;
  StringStream& operator>>(LPECHAR) override;
};