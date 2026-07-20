/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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