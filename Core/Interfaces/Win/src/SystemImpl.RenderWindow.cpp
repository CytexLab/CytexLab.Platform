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