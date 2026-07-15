/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "Types.hpp"
#include "Unicode.hpp"

namespace CytexLab
{
    namespace Interface
    {
        struct IConsoleHandle
        {
            HANDLE hIn;
            HANDLE hOut;
        };

        struct IConsoleSettings
        {
            BOOL hInIsFile;
            BOOL hOutIsFile;
        };

        struct IConsoleLink
        {
            IConsoleSettings Settings;
            IConsoleHandle Handle;
        };

        enum class IConsoleError : UINT8
        {
            None,
            NullPointer,
            FailConvert,
            SystemError
        };

        struct IConsoleResult
        {
            BOOL Success;
            IConsoleError Error;
            Unicode::ConvertResult ConvertResult;
            UINT32 SystemError;
        };

        class IConsole
        {
        public:
            virtual IConsoleResult Write(LPCECHAR Str) = 0;
            virtual IConsoleResult WriteLine(LPCECHAR Str) = 0;
            virtual IConsoleResult ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;
        };
    }
}