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
#include "Panic.hpp"

cl::Interface::ISystem* cl::SystemPlatform::Fabric::Create()
{
  Panic::StackPush(__PRETTY_FUNCTION__, "CytexLab.Platform.SystemPlatform", __LINE__);

  HANDLE heap = ::GetProcessHeap();
  LPVOID mem = ::HeapAlloc(heap, 0, sizeof(SystemImpl));

  if (!mem)
  {
    Panic::Panic(U"Fail allocate memory for new object", __PRETTY_FUNCTION__, "CytexLab.Platform.SystemPlatform", __LINE__, ::GetLastError());
  }

  SystemImpl* si = new (mem) SystemImpl();

  Panic::StackPop();

  return (Interface::ISystem*)si;
}

void cl::SystemPlatform::Fabric::Destroy(Interface::ISystem* System)
{
  Panic::StackPush(__PRETTY_FUNCTION__, "CytexLab.Platform.SystemPlatform", __LINE__);

  SystemImpl* si = (SystemImpl*)System;

  HANDLE heap = ::GetProcessHeap();
  INT32 result = ::HeapFree(heap, 0, si);

  if (result != 1)
  {
    Panic::Panic(U"Fail free memory for object", __PRETTY_FUNCTION__, "CytexLab.Platform.SystemPlatform", __LINE__, ::GetLastError());
  }

  Panic::StackPop();
}
#endif