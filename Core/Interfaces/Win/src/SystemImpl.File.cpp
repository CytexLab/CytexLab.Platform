/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "FileImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

void SystemImpl::OpenFile(CytexLab::Interface::IFile*& Out, LPCECHAR Path, CytexLab::Interface::IFileOpenMode Mode)
{
    if (!Path)
        ::ExitProcess(-1);

    UINT32 dwDesiredAccess;
    UINT32 dwCreationDisposition;

    switch (Mode) {
        case CytexLab::Interface::IFileOpenMode::Read:
            dwDesiredAccess = GENERIC_READ;
            dwCreationDisposition = OPEN_EXISTING;
            break;
        case CytexLab::Interface::IFileOpenMode::Write:
            dwDesiredAccess = GENERIC_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
            break;
        case CytexLab::Interface::IFileOpenMode::ReadWrite:
            dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
            break;
        default:
            ::ExitProcess(-1);
    }

    WCHAR buf[256 * 2];

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Path, &buf[0]);

    if (!convert_result.Success)
        ::ExitProcess(-1);

    HANDLE hFile = ::CreateFileW(&buf[0], dwDesiredAccess, FILE_SHARE_READ, NULLPTR, dwCreationDisposition, 0, NULLPTR);

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(FileImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    FileImpl* fi = new (mem) FileImpl(hFile);
    Out = (CytexLab::Interface::IFile*) fi;
}

void SystemImpl::CloseFile(CytexLab::Interface::IFile* File)
{
    if (!File)
        ::ExitProcess(-1);

    FileImpl* fi = (FileImpl*) File;
    BOOL result = ::CloseHandle(fi->GetHandle());

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, fi);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}