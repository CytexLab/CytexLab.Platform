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


#include "ConsoleImpl.hpp"
#include "Unicode.hpp"
#include "Mem.hpp"
#include "WinImports.hpp"

void ConsoleImpl::SetLink(CytexLab::Interface::IConsoleLink Link)
{
    this->link = Link;
}

void ConsoleImpl::WriteConsole(LPCECHAR Str)
{
    if (!Str)
        ::ExitProcess(-1);
    
    UINT64 len = Unicode::StrLen(Str);

    if (len == 0)
        ::ExitProcess(-1);
    
    while (*Str)
    {
        WCHAR buf[2];

        Unicode::ConvertResult result = Unicode::ToUTF16(Str, &buf[0]);

        if (!result.Success)
            ::ExitProcess(-1);
        
        BOOL w_result = ::WriteConsoleW(this->link.Handle.hOut, &buf[0], result.CountBytes / 2, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        Str++;
    }
}

void ConsoleImpl::WriteFile(LPCECHAR Str)
{
    if (!Str)
        ::ExitProcess(-1);
    
    UINT64 len = Unicode::StrLen(Str);

    if (len == 0)
        ::ExitProcess(-1);
    
    while (*Str)
    {
        CHAR buf[4];

        Unicode::ConvertResult result = Unicode::ToUTF8(Str, &buf[0]);

        if (!result.Success)
            ::ExitProcess(-1);
        
        BOOL w_result = ::WriteFile(this->link.Handle.hOut, &buf[0], result.CountBytes, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        Str++;
    }
}

void ConsoleImpl::Write(LPCECHAR Str)
{
    if (this->link.Settings.hOutIsFile)
        this->WriteFile(Str);
    else
        this->WriteConsole(Str);
}

void ConsoleImpl::WriteLine (LPCECHAR Str)
{
    this->Write(Str);
    this->Write((LPCECHAR) U"\r\n");
}

void ConsoleImpl::ReadConsole(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        ::ExitProcess(-1);
    
    if (BufferSize == 0)
        return;
    
    UINT64 readed = 0;
    UINT8 bufPos = 0;
    WCHAR buf[2];

    memset(buf, 0, 4);

    while (readed < BufferSize - 1)
    {
        UINT32 _;
        BOOL w_result = ::ReadConsoleW(this->link.Handle.hIn, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (buf[0] == L'\r')
            continue;

        if (buf[0] == L'\n')
            break;

        Unicode::ConvertResult result = Unicode::ToUTF32(&buf[0], Buffer);

        if (!result.Success)
        {
            if (bufPos < 1) bufPos++;
            else
                ::ExitProcess(-1);
        }
        else
        {
            readed++;
            Buffer++;

            memset(buf, 0, 4);
            bufPos = 0;
        }
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;
}

void ConsoleImpl::ReadFile(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        ::ExitProcess(-1);
    
    if (BufferSize == 0)
        return;
    
    UINT64 readed = 0;
    UINT8 bufPos = 0;
    CHAR buf[4];

    memset(buf, 0, 4);

    while (readed < BufferSize - 1)
    {
        UINT32 _;
        BOOL w_result = ::ReadFile(this->link.Handle.hIn, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (buf[0] == '\r')
            continue;

        if (buf[0] == '\n')
            break;

        Unicode::ConvertResult result = Unicode::ToUTF32(&buf[0], Buffer);

        if (!result.Success)
        {
            if (bufPos < 3) bufPos++;
            else
                ::ExitProcess(-1);
        }
        else
        {
            readed++;
            Buffer++;

            memset(buf, 0, 4);
            bufPos = 0;
        }
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;
}

void ConsoleImpl::ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (this->link.Settings.hInIsFile)
        this->ReadFile(Buffer, BufferSize, Readed);
    else
        this->ReadConsole(Buffer, BufferSize, Readed);
}