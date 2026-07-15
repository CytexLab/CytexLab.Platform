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
        enum class IFileError : UINT8
        {
            None,
            NullPointer,
            FailConvert,
            SystemError,
            InvalidMoveMethod
        };

        struct IFileResult
        {
            BOOL Success;
            IFileError Error;
            Unicode::ConvertResult ConvertResult;
            UINT32 SystemError;
        };

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
            virtual IFileResult Write(LPCECHAR Str) = 0;
            virtual IFileResult WriteLine(LPCECHAR Str) = 0;
            virtual IFileResult Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;

            virtual IFileResult Write(LPCVOID Data, UINT64 Size) = 0;
            virtual IFileResult Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;

            virtual IFileResult GetFileSize(LPUINT64 Out) = 0;
            virtual IFileResult Seek(IFileSeekMode Mode, INT64 Offset, LPUINT64 NewPos) = 0;
        };
    }
}