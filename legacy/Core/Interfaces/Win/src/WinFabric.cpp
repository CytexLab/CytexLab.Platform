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


#include "SystemImpl.hpp"
#include "WinImports.hpp"
#include "SystemFabric.hpp"
#include "Placement.hpp"

CytexLab::Interface::ISystem* CytexLab::Interface::Fabric::SystemFabric::Create()
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(SystemImpl));
    return (ISystem*)(new (mem) SystemImpl());
}

void CytexLab::Interface::Fabric::SystemFabric::Destroy(CytexLab::Interface::ISystem* Interface)
{
    SystemImpl* si = (SystemImpl*) Interface;
    HANDLE heap = ::GetProcessHeap();
    ::HeapFree(heap, 0, si);
}