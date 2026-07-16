/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "Types.hpp"
#include "IConsole.hpp"
#include "IFile.hpp"
#include "IPool.hpp"
#include "IThread.hpp"
#include "IMutex.hpp"
#include "IPipe.hpp"

namespace CytexLab
{
    namespace Interface
    {
        enum class ISystemError
        {
            None,
            SystemError,
            FailConvert,
            NullPointer,
            InvalidOpenMode,
            InvalidPoolSize
        };

        struct ISystemResult
        {
            BOOL Success;
            ISystemError Error;
            Unicode::ConvertStringResult ConvertResult;
            UINT32 SystemError;
        };

        class ISystem
        {
        public:
            virtual ISystemResult CreateConsole(IConsole*& Out) = 0;
            virtual ISystemResult RedirectConsole(IConsole* Console, IFile* Out, IFile* In) = 0;
            virtual ISystemResult DestroyConsole(IConsole* Console) = 0;

            virtual ISystemResult OpenFile(IFile*& Out, LPCECHAR Path, IFileOpenMode Mode) = 0;
            virtual ISystemResult CloseFile(IFile* File) = 0;

            virtual ISystemResult CreatePool(IPool*& Out, UINT64 Size) = 0;
            virtual ISystemResult DestroyPool(IPool* Pool) = 0;

            virtual ISystemResult CreateThread(IThread*& Out, IThreadFunc Function, LPVOID Arg) = 0;
            virtual ISystemResult DestroyThread(IThread* Thread) = 0;

            virtual ISystemResult CreateMutex(IMutex*& Out) = 0;
            virtual ISystemResult DestroyMutex(IMutex* Mutex) = 0;

            virtual ISystemResult CreatePipe(IPipe*& Out, LPCECHAR Name) = 0;
            virtual ISystemResult DestroyPipe(IPipe* Pipe) = 0;

            virtual void ExitProcess(UINT32 Code) = 0;
        };
    }
}