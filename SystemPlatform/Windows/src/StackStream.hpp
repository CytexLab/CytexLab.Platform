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

#define MAX_WRITE 128

class StackStream : public cl::SystemPlatform::StringStream
{
private:
  StackItem* stack = nullptr;
  UINT64 count = 0;
  LPCECHAR writes[MAX_WRITE] = {nullptr};
  UINT64 count_writes = 0;
  LPECHAR read_buf = nullptr;

public:
  StackStream(StackItem* Stack, UINT64 Count);

  StringStream& operator<<(LPCUINT8) override;
  StringStream& operator>>(LPUINT8) override;
  StringStream& operator<<(LPCECHAR) override;
  StringStream& operator>>(LPECHAR) override;
  // StringStream& operator<<(const Stream& Other) override;
  // StringStream& operator>>(Stream& Other) override;
  // StringStream& operator<<(const StringStream& Other) override;
  // StringStream& operator>>(StringStream& Other) override;
};