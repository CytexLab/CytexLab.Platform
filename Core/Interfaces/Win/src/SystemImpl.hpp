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

    void CreateConsole(CytexLab::Interface::IConsole*& Out) override;
    void RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IFile* Out, CytexLab::Interface::IFile* In) override;
    void RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IPipe* Pipe) override;
    void DestroyConsole(CytexLab::Interface::IConsole* Console) override;

    void OpenFile(CytexLab::Interface::IFile*& Out, LPCECHAR Path, CytexLab::Interface::IFileOpenMode Mode) override;
    void CloseFile(CytexLab::Interface::IFile* File) override;

    void CreateThread(CytexLab::Interface::IThread*& Out, CytexLab::Interface::IThreadFunc Function, LPVOID Arg) override;
    void DestroyThread(CytexLab::Interface::IThread* Thread) override;

    void CreateMutex(CytexLab::Interface::IMutex*& Out) override;
    void DestroyMutex(CytexLab::Interface::IMutex* Mutex) override;

    void CreatePipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name) override;
    void OpenPipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name) override;
    void DestroyPipe(CytexLab::Interface::IPipe* Pipe) override;

    void CreateAllocator(CytexLab::Interface::IAllocator *&Allacator) override;
    void DestroyAllocator(CytexLab::Interface::IAllocator *Allacator) override;

    void GetArgs(LPUINT64 Out) override;
    void GetArgv(LPECHAR* Out) override;

    void CreateProcess(CytexLab::Interface::IProcess*& Out, LPCECHAR CmdLine) override;
    void DestroyProcess(CytexLab::Interface::IProcess* Process) override;

    void ExitProcess(UINT32 Code) override;
};