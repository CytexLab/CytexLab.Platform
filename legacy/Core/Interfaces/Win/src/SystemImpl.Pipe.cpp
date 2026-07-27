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
#include "PipeImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"
#include "Mem.hpp"

void SystemImpl::CreatePipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name)
{
    if (!Name)
        ::ExitProcess(-1);

    UINT64 size = (Unicode::StrLen(Name) * 2 + 9) * sizeof(WCHAR);

    HANDLE heap = ::GetProcessHeap();
    LPWCHAR buf = (LPWCHAR) ::HeapAlloc(heap, 0, size);

    if (!buf)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    memcpy(buf, L"\\\\.\\pipe\\", 9 * sizeof(WCHAR));

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Name, buf + 9);

    if (!convert_result.Success)
    {
        ::ExitProcess(-1);
    }

    HANDLE hPipe = ::CreateNamedPipeW(buf, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_WAIT, 2, 4096, 4096, 0, NULLPTR);

    if (!hPipe || hPipe == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(PipeImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    PipeImpl* pi = new (mem) PipeImpl(hPipe, TRUE);
    Out = (CytexLab::Interface::IPipe*) pi;
}

void SystemImpl::OpenPipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name)
{
    if (!Name)
        ::ExitProcess(-1);

    UINT64 size = (Unicode::StrLen(Name) * 2 + 9) * sizeof(WCHAR);

    HANDLE heap = ::GetProcessHeap();
    LPWCHAR buf = (LPWCHAR) ::HeapAlloc(heap, 0, size);

    if (!buf)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    memcpy(buf, L"\\\\.\\pipe\\", 9 * sizeof(WCHAR));

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Name, buf + 9);

    if (!convert_result.Success)
    {
        ::ExitProcess(-1);
    }

    BOOL result = ::WaitNamedPipeW(buf, NMPWAIT_WAIT_FOREVER);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    HANDLE hPipe = ::CreateFileW(buf, GENERIC_READ | GENERIC_WRITE, 0, NULLPTR, OPEN_EXISTING, 0, NULLPTR);

    if (!hPipe || hPipe == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(PipeImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    PipeImpl* pi = new (mem) PipeImpl(hPipe, FALSE);
    Out = (CytexLab::Interface::IPipe*) pi;
}

void SystemImpl::DestroyPipe(CytexLab::Interface::IPipe* Pipe)
{
    if (!Pipe)
        ::ExitProcess(-1);

    PipeImpl* pi = (PipeImpl*) Pipe;

    HANDLE hPipe = pi->GetHandle();
    BOOL isOwner = pi->IsOwner();

    if (isOwner)
    {
        BOOL result = ::DisconnectNamedPipe(hPipe);

        if (!result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }
    }

    BOOL result = ::CloseHandle(hPipe);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, pi);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}