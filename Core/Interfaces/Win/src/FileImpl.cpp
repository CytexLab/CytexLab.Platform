/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#include "FileImpl.hpp"
#include "WinImports.hpp"
#include "Mem.hpp"

FileImpl::FileImpl(HANDLE Handle)
{
    this->handle = Handle;
}

FileImpl::~FileImpl()
{
    
}

HANDLE FileImpl::GetHandle()
{
    return this->handle;
}

void FileImpl::Write(LPCECHAR Str)
{
    if (!Str)
        ::ExitProcess(-1);
    
    UINT64 len = Unicode::StrLen(Str);

    if (len == 0)
        return;
    
    while (*Str)
    {
        CHAR buf[4];

        /*
         * Писать UTF-32 в файл?
         * Ну, а кто запрещает
         * Главное потом это открыть редактором
         * :)
        */

        Unicode::ConvertResult result = Unicode::ToUTF8(Str, &buf[0]);

        if (!result.Success)
            ::ExitProcess(-1);
        
        BOOL w_result = ::WriteFile(this->handle, &buf[0], result.CountBytes, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        Str++;
    }
}

void FileImpl::WriteLine(LPCECHAR Str)
{
    this->Write(Str);
    this->Write((LPCECHAR) U"\r\n");
}

void FileImpl::Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
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
        BOOL w_result = ::ReadFile(this->handle, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (_ == 0)
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

void FileImpl::Write(LPCVOID Data, UINT64 Size)
{
    if (!Data)
        ::ExitProcess(-1);
    
    UINT64 written = 0;

    while (written < Size)
    {
        UINT64 write = Size - written;
        UINT32 _written = 0;

        if (write > (UINT32)-1)
            write = (UINT32)-1;

        BOOL result_w = ::WriteFile(this->handle, Data, write, &_written, NULLPTR);
        
        if (!result_w)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (_written == 0) // Мы больше не можем писать??? Не должно быть, но оставим
            break;
        
        written += _written;
    }
}

void FileImpl::Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        ::ExitProcess(-1);

    UINT64 readed = 0;

    while (readed < BufferSize)
    {
        UINT64 read = BufferSize - readed;
        UINT32 _readed = 0;

        if (read > (UINT32)-1)
            read = (UINT32)-1;

        BOOL result_w = ::ReadFile(this->handle, (LPVOID)((LPCHAR)Buffer + readed), read, &_readed, NULLPTR);

        if (!result_w)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (_readed == 0) // Конец файла?
            break;        // Ну тогда выходим
        
        readed += _readed;
    }

    if (Readed)
        *Readed = readed;
}

void FileImpl::GetFileSize(LPUINT64 Out)
{
    if (!Out)
        ::ExitProcess(-1);
    
    LARGE_INTEGER li;
    BOOL result = ::GetFileSizeEx(this->handle, &li);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
    else
    {
        *Out = (UINT64)li.QuadPart;
    }
}

void FileImpl::Seek(CytexLab::Interface::IFileSeekMode Mode, INT64 Offset, LPUINT64 NewPos)
{
    if (!NewPos)
        ::ExitProcess(-1);

    UINT32 dwMoveMethod;

    switch (Mode)
    {
        case CytexLab::Interface::IFileSeekMode::Start:
            dwMoveMethod = FILE_BEGIN;
            break;
        case CytexLab::Interface::IFileSeekMode::CurrentPos:
            dwMoveMethod = FILE_CURRENT;
            break;
        case CytexLab::Interface::IFileSeekMode::End:
            dwMoveMethod = FILE_END;
            break;
        default:
            ::ExitProcess(-1);
            break;
    }

    LARGE_INTEGER offset;
    offset.QuadPart = Offset;

    LARGE_INTEGER new_pos;

    BOOL result = ::SetFilePointerEx(this->handle, offset, &new_pos, dwMoveMethod);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
    else
    {
        *NewPos = (UINT64) new_pos.QuadPart;
    }
}