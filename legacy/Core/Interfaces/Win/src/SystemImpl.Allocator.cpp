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
#include "AllocatorImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

void SystemImpl::CreateAllocator(CytexLab::Interface::IAllocator *&Out)
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(AllocatorImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    AllocatorImpl* ai = new (mem) AllocatorImpl();
    ai->Init();

    Out = (CytexLab::Interface::IAllocator*) ai;
}

void SystemImpl::DestroyAllocator(CytexLab::Interface::IAllocator *Allacator)
{
    if (!Allacator)
        ::ExitProcess(-1);

    AllocatorImpl* ai = (AllocatorImpl*) Allacator;
    ai->DeInit();

    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, ai);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}