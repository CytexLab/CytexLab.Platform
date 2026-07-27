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

#include "Types.hpp"
#include "IConsole.hpp"
#include "IFile.hpp"
#include "IThread.hpp"
#include "IMutex.hpp"
#include "IPipe.hpp"
#include "IAllocator.hpp"
#include "IProcess.hpp"
#include "IWindow.hpp"
#include "IRenderWindow.hpp"

namespace CytexLab
{
    namespace Interface
    {
        class ISystem
        {
        public:
            virtual void CreateConsole(IConsole*& Out) = 0;
            virtual void RedirectConsole(IConsole* Console, IFile* Out, IFile* In) = 0;
            virtual void RedirectConsole(IConsole* Console, IPipe* Pipe) = 0;
            virtual void DestroyConsole(IConsole* Console) = 0;

            virtual void OpenFile(IFile*& Out, LPCECHAR Path, IFileOpenMode Mode) = 0;
            virtual void CloseFile(IFile* File) = 0;

            virtual void CreateThread(IThread*& Out, IThreadFunc Function, LPVOID Arg) = 0;
            virtual void DestroyThread(IThread* Thread) = 0;

            virtual void CreateMutex(IMutex*& Out) = 0;
            virtual void DestroyMutex(IMutex* Mutex) = 0;

            virtual void CreatePipe(IPipe*& Out, LPCECHAR Name) = 0;
            virtual void OpenPipe(IPipe*& Out, LPCECHAR Name) = 0;
            virtual void DestroyPipe(IPipe* Pipe) = 0;

            virtual void CreateAllocator(IAllocator*& Out) = 0;
            virtual void DestroyAllocator(IAllocator* Allocator) = 0;

            virtual void GetArgs(LPUINT64 Out) = 0;
            virtual void GetArgv(LPECHAR* Buffer) = 0;

            virtual void CreateProcess(IProcess*& Out, LPCECHAR CmdLine) = 0;
            virtual void DestroyProcess(IProcess* Process) = 0;

            virtual void CreateWindow(IWindow*& Out, LPCECHAR Title, UINT64 x, UINT64 y, UINT64 Width, UINT64 Height) = 0;
            virtual void DestroyWindow(IWindow* Window) = 0;

            virtual void CreateRenderWindow(IRenderWindow*& Out, IWindow* Window) = 0;
            virtual void DestroyRenderWindow(IRenderWindow* RenderWindow) = 0;

            virtual void ExitProcess(UINT32 Code) = 0;
        };
    }
}