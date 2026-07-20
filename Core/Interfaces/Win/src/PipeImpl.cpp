/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "WinImports.hpp"
#include "PipeImpl.hpp"
#include "Unicode.hpp"

PipeImpl::PipeImpl(HANDLE Handle, BOOL Owner)
{
    this->handle = Handle;
    this->owner = Owner;
}

PipeImpl::~PipeImpl()
{

}

HANDLE PipeImpl::GetHandle()
{
    return this->handle;
}

BOOL PipeImpl::IsOwner()
{
    return this->owner;
}

void PipeImpl::Write(LPCECHAR Str)
{
    if (!Str)
        ::ExitProcess(-1);
    
    UINT64 len = Unicode::StrLen(Str);
    UINT64 written = 0;

    while (written < len)
    {   
        UINT64 write = len - written;

        if (write > (UINT32)-1)
            write = (UINT32)-1;

        UINT32 _written = 0;
        BOOL result = ::WriteFile(this->handle, Str, write * sizeof(ECHAR), &_written, NULLPTR);
        
        if (!result || _written == 0)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        Str += _written / sizeof(ECHAR);
        written += _written / sizeof(ECHAR);
    }
}

void PipeImpl::Write(LPCVOID Data, UINT64 Size)
{
    if (!Data)
        ::ExitProcess(-1);
    
    if (Size == 0)
        return;
    
    UINT64 written = 0;

    while (written < Size)
    {   
        UINT64 write = Size - written;

        if (write > (UINT32)-1)
            write = (UINT32)-1;

        UINT32 _written = 0;
        BOOL result = ::WriteFile(this->handle, Data, write, &_written, NULLPTR);
        
        if (!result || _written == 0)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        Data = (LPCVOID)((LPUINT8)Data + _written);
        written += _written;
    }
}

void PipeImpl::Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        ::ExitProcess(-1);
    
    if (BufferSize == 0)
        return;
    
    UINT64 readed = 0;

    while (readed < BufferSize - 1)
    {
        UINT64 read = BufferSize - readed;

        if (read > (UINT32)-1)
            read = (UINT32)-1;

        UINT32 _readed;
        BOOL result = ::ReadFile(this->handle, Buffer, read * sizeof(ECHAR), &_readed, NULLPTR);

        if (!result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (_readed == 0)
            break;

        Buffer += _readed / sizeof(ECHAR);
        readed += _readed / sizeof(ECHAR);

        if (_readed < read)
            break;
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;
}

void PipeImpl::Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return;
    
    if (BufferSize == 0)
        return;
    
    UINT64 readed = 0;

    while (readed < BufferSize)
    {
        UINT64 read = BufferSize - readed;

        if (read > (UINT32)-1)
            read = (UINT32)-1;

        UINT32 _readed;
        BOOL result = ::ReadFile(this->handle, Buffer, read, &_readed, NULLPTR);

        if (!result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        if (_readed == 0)
            break;

        Buffer = (LPVOID)((LPUINT8)Buffer + _readed);
        readed += _readed;
    }

    if (Readed)
        *Readed = readed;
}

void PipeImpl::Connect()
{
    if (this->owner)
    {
        BOOL connected = ::ConnectNamedPipe(this->handle, NULLPTR);
        
        if (!connected)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }
    }
    else 
    {
        ::ExitProcess(-1);
    }
}