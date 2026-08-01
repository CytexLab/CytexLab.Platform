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

#include "Fabric.hpp"

#ifdef Windows

#include "Placement.hpp"
#include "Win32.SystemImpl.hpp"
#include "Win32.WinImports.hpp"

cl::Interface::ISystem* cl::SystemPlatform::Fabric::Create()
{
  HANDLE heap = ::GetProcessHeap();
  LPVOID mem = ::HeapAlloc(heap, 0, sizeof(SystemImpl));

  if (!mem)
  {
    // TODO: Сделать panic
  }

  SystemImpl* si = new (mem) SystemImpl();
  return (Interface::ISystem*)si;
}

void cl::SystemPlatform::Fabric::Destroy(Interface::ISystem* System)
{
  SystemImpl* si = (SystemImpl*)System;

  HANDLE heap = ::GetProcessHeap();
  INT32 result = ::HeapFree(heap, 0, si);

  if (result != 1)
  {
    // TODO: Сделать panic
  }
}
#endif