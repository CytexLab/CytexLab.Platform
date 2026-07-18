/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "ISystem.hpp"
#include "IConsole.hpp"

class SystemImpl : public CytexLab::Interface::ISystem
{
public:
    SystemImpl();
    ~SystemImpl();

    CytexLab::Interface::ISystemResult CreateConsole(CytexLab::Interface::IConsole*& Out) override;
    CytexLab::Interface::ISystemResult RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IFile* Out, CytexLab::Interface::IFile* In) override;
    CytexLab::Interface::ISystemResult RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IPipe* Pipe) override;
    CytexLab::Interface::ISystemResult DestroyConsole(CytexLab::Interface::IConsole* Console) override;

    CytexLab::Interface::ISystemResult OpenFile(CytexLab::Interface::IFile*& Out, LPCECHAR Path, CytexLab::Interface::IFileOpenMode Mode) override;
    CytexLab::Interface::ISystemResult CloseFile(CytexLab::Interface::IFile* File) override;

    CytexLab::Interface::ISystemResult CreatePool(CytexLab::Interface::IPool*& Out, UINT64 Size) override;
    CytexLab::Interface::ISystemResult DestroyPool(CytexLab::Interface::IPool* Pool) override;

    CytexLab::Interface::ISystemResult CreateThread(CytexLab::Interface::IThread*& Out, CytexLab::Interface::IThreadFunc Function, LPVOID Arg) override;
    CytexLab::Interface::ISystemResult DestroyThread(CytexLab::Interface::IThread* Thread) override;

    CytexLab::Interface::ISystemResult CreateMutex(CytexLab::Interface::IMutex*& Out) override;
    CytexLab::Interface::ISystemResult DestroyMutex(CytexLab::Interface::IMutex* Mutex) override;

    CytexLab::Interface::ISystemResult CreatePipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name) override;
    CytexLab::Interface::ISystemResult OpenPipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name) override;
    CytexLab::Interface::ISystemResult DestroyPipe(CytexLab::Interface::IPipe* Pipe) override;

    CytexLab::Interface::ISystemResult CreateAllacator(CytexLab::Interface::IAllacator*& Allacator) override;
    CytexLab::Interface::ISystemResult DestroyAllacator(CytexLab::Interface::IAllacator* Allacator) override;

    CytexLab::Interface::ISystemResult GetArgs(LPUINT64 Out) override;
    CytexLab::Interface::ISystemResult GetArgv(LPECHAR* Out) override;

    void ExitProcess(UINT32 Code) override;
};