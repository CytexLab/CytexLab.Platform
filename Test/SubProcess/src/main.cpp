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

#include "SystemFabric.hpp"
#include "ISystem.hpp"

using namespace CytexLab::Interface;

extern "C" void startup()
{
    ISystem* system = Fabric::SystemFabric::Create();

    IPipe* pipe;
    system->OpenPipe(pipe, U"MyTestPipe");

    pipe->Write(U"Hello, World! Subprocess.");

    system->DestroyPipe(pipe);
    system->ExitProcess(0);
}