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