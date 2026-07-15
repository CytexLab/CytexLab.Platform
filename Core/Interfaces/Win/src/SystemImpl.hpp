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
    CytexLab::Interface::ISystemResult DestroyConsole(CytexLab::Interface::IConsole* Console) override;

    CytexLab::Interface::ISystemResult OpenFile(CytexLab::Interface::IFile*& Out, LPCECHAR Path, CytexLab::Interface::IFileOpenMode Mode) override;
    CytexLab::Interface::ISystemResult CloseFile(CytexLab::Interface::IFile* File) override;

    CytexLab::Interface::ISystemResult CreatePool(CytexLab::Interface::IPool*& Out, UINT64 Size) override;
    CytexLab::Interface::ISystemResult DestroyPool(CytexLab::Interface::IPool* Pool) override;

    CytexLab::Interface::ISystemResult CreateThread(CytexLab::Interface::IThread*& Out, CytexLab::Interface::IThreadFunc Function, LPVOID Arg) override;
    CytexLab::Interface::ISystemResult DestroyThread(CytexLab::Interface::IThread* Thread) override;

    CytexLab::Interface::ISystemResult CreateMutex(CytexLab::Interface::IMutex*& Out) override;
    CytexLab::Interface::ISystemResult DestroyMutex(CytexLab::Interface::IMutex* Mutex) override;

    void ExitProcess(UINT32 Code) override;
};