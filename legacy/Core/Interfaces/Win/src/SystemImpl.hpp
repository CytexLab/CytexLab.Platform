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

    void CreateWindow(CytexLab::Interface::IWindow*& Out, LPCECHAR Title, UINT64 x, UINT64 y, UINT64 Width, UINT64 Height) override;
    void DestroyWindow(CytexLab::Interface::IWindow* Window) override;

    void CreateRenderWindow(CytexLab::Interface::IRenderWindow*& Out, CytexLab::Interface::IWindow* Window) override;
    void DestroyRenderWindow(CytexLab::Interface::IRenderWindow* Window) override;

    void ExitProcess(UINT32 Code) override;
};