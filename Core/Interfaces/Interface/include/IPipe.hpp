/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "Types.hpp"

namespace CytexLab
{
    namespace Interface
    {
        enum class IPipeError : UINT8
        {
            None,
            NullPointer,
            SystemError
        };

        struct IPipeResult
        {
            BOOL Success;
            IPipeError Error;
            UINT32 SystemError;
        };

        class IPipe
        {
        public:
            virtual IPipeResult Write(LPCECHAR Str) = 0;
            virtual IPipeResult Write(LPCVOID Data, UINT64 Size) = 0;

            virtual IPipeResult Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;
            virtual IPipeResult Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;
        };
    }
}