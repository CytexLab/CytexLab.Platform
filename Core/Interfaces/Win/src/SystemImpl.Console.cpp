/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "WinImports.hpp"
#include "ConsoleImpl.hpp"
#include "FileImpl.hpp"
#include "PipeImpl.hpp"
#include "Placement.hpp"

void SystemImpl::CreateConsole(CytexLab::Interface::IConsole*& Out)
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(ConsoleImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    ConsoleImpl* ci = new (mem) ConsoleImpl();

    CytexLab::Interface::IConsoleSettings s;
    s = {FALSE, FALSE};

    CytexLab::Interface::IConsoleHandle h;
    h = {::GetStdHandle(STD_INPUT_HANDLE),
         ::GetStdHandle(STD_OUTPUT_HANDLE)
    };

    CytexLab::Interface::IConsoleLink l;
    l = {s, h};

    ci->SetLink(l);

    Out = (CytexLab::Interface::IConsole*) ci;
}

void SystemImpl::RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IFile* Out, CytexLab::Interface::IFile* In)
{
    if (!Console)
        ::ExitProcess(-1);

    CytexLab::Interface::IConsoleSettings s;
    CytexLab::Interface::IConsoleHandle h;

    if (Out)
    {
        s.hOutIsFile = TRUE;

        FileImpl* fi = (FileImpl*)Out;
        h.hOut = fi->GetHandle();
    }
    else
    {
        s.hOutIsFile = FALSE;
        h.hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    }

    if (In)
    {
        s.hInIsFile = TRUE;

        FileImpl* fi = (FileImpl*)In;
        h.hIn = fi->GetHandle();
    }
    else
    {
        s.hInIsFile = FALSE;
        h.hIn = ::GetStdHandle(STD_INPUT_HANDLE);
    }

    CytexLab::Interface::IConsoleLink l = {s, h};

    ConsoleImpl* ci = (ConsoleImpl*) Console;
    ci->SetLink(l);
}

void SystemImpl::RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IPipe* Pipe)
{
    if (!Console)
        ::ExitProcess(-1);

    CytexLab::Interface::IConsoleSettings s;
    CytexLab::Interface::IConsoleHandle h;

    if (!Pipe)
    {
        s.hOutIsFile = FALSE;
        s.hInIsFile = FALSE;

        h.hIn = ::GetStdHandle(STD_INPUT_HANDLE);
        h.hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    }
    else
    {
        PipeImpl* pi = (PipeImpl*) Pipe;

        s.hOutIsFile = TRUE;
        s.hInIsFile = TRUE;

        h.hIn = pi->GetHandle();
        h.hOut = pi->GetHandle();
    }

    CytexLab::Interface::IConsoleLink l = {s, h};

    ConsoleImpl* ci = (ConsoleImpl*) Console;
    ci->SetLink(l);
}

void SystemImpl::DestroyConsole(CytexLab::Interface::IConsole* Console)
{
    if (!Console)
        ::ExitProcess(-1);

    ConsoleImpl* ci = (ConsoleImpl*) Console;
    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, ci);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}