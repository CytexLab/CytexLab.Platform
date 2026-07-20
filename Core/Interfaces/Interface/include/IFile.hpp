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
        enum class IFileOpenMode : UINT8
        {
            Read,
            Write,
            ReadWrite
        };

        enum class IFileSeekMode : UINT8
        {
            Start,
            CurrentPos,
            End
        };

        class IFile
        {
        public:
            virtual void Write(LPCECHAR Str) = 0;
            virtual void WriteLine(LPCECHAR Str) = 0;
            virtual void Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;

            virtual void Write(LPCVOID Data, UINT64 Size) = 0;
            virtual void Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;

            virtual void GetFileSize(LPUINT64 Out) = 0;
            virtual void Seek(IFileSeekMode Mode, INT64 Offset, LPUINT64 NewPos) = 0;
        };
    }
}