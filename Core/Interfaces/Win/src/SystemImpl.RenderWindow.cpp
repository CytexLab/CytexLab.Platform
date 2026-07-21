/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "WinImports.hpp"
#include "WindowImpl.hpp"
#include "Placement.hpp"
#include "RenderWindowImpl.hpp"

void SystemImpl::CreateRenderWindow(CytexLab::Interface::IRenderWindow *&Out, CytexLab::Interface::IWindow *Window)
{
    if (!Window)
        ::ExitProcess(-1);

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(RenderWindowImpl));

    WindowImpl* wi = (WindowImpl*) Window;

    RenderWindowImpl* rwi = new (mem) RenderWindowImpl(wi);
    Out = rwi;
}

void SystemImpl::DestroyRenderWindow(CytexLab::Interface::IRenderWindow *Window)
{
    if (!Window)
        ::ExitProcess(-1);

    RenderWindowImpl* rwi = (RenderWindowImpl*) Window;
    rwi->~RenderWindowImpl();

    HANDLE heap = ::GetProcessHeap();

    if (!::HeapFree(heap, 0, rwi))
        ::ExitProcess(-1);
}