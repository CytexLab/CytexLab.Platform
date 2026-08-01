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
#include "Panic.hpp"

extern "C" void startup()
{
  cl::SystemPlatform::Panic::Init();

  STACK_FRAME();

  cl::Interface::ISystem* system = cl::SystemPlatform::Fabric::Create();

  ASSERT(FALSE, U"Test");

  cl::SystemPlatform::Panic::StackPop();

  system->Exit(0);
}