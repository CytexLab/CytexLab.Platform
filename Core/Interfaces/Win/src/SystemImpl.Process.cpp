/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "Unicode.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"
#include "ProcessImpl.hpp"

void SystemImpl::CreateProcess(CytexLab::Interface::IProcess *&Out, LPCECHAR CmdLine)
{
    if (!CmdLine)
        ::ExitProcess(-1);

    UINT64 len = Unicode::StrLen(CmdLine);

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, len * 2 * sizeof(WCHAR));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    Unicode::ConvertStringResult result_convert = Unicode::ToUTF16String(CmdLine, (LPWCHAR) mem);

    if (!result_convert.Success)
    {
        ::ExitProcess(-1);
    }

    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFOW si = { sizeof(si) };

    BOOL result = ::CreateProcessW(
        NULLPTR,
        (LPWCHAR) mem,
        NULLPTR,
        NULLPTR,
        FALSE,
        CREATE_NO_WINDOW | DETACHED_PROCESS,
        NULLPTR,
        NULLPTR,
        &si,
        &pi
    );

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    LPVOID mem_obj = ::HeapAlloc(heap, 0, sizeof(ProcessImpl));

    if (!mem_obj)
    {
        UINT32 error = ::GetLastError();

        ::TerminateProcess(pi.hProcess, -1);
        ::CloseHandle(pi.hProcess);
        ::CloseHandle(pi.hThread);

        ::ExitProcess(-1);
    }

    ProcessImpl* pi_obj = (ProcessImpl*) new (mem_obj) ProcessImpl(pi);
    Out = (CytexLab::Interface::IProcess*) pi_obj;
}

void SystemImpl::DestroyProcess(CytexLab::Interface::IProcess *Process)
{
    ProcessImpl* pi_obj = (ProcessImpl*) Process;
    PROCESS_INFORMATION pi = pi_obj->GetPi();

    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, pi_obj);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    result = ::CloseHandle(pi.hThread);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    result = ::CloseHandle(pi.hProcess);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}