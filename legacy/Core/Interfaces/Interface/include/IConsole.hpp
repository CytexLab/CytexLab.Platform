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

#include "Platform.hpp"
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

        class IConsole
        {
        public:
            virtual void Write(LPCECHAR Str) = 0;
            virtual void WriteLine(LPCECHAR Str) = 0;
            virtual void ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) = 0;
        };
    }
}