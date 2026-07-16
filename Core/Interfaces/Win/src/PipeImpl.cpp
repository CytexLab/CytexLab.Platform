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

CytexLab::Interface::IPipeResult PipeImpl::Write(LPCECHAR Str)
{
    if (!Str)
        return {
            FALSE,
            CytexLab::Interface::IPipeError::NullPointer,
            0
        };
    
    UINT64 len = Unicode::StrLen(Str);
    UINT64 written = 0;

    while (written < len)
    {   
        UINT64 write = len - written;

        if (write > (UINT32)-1)
            write = (UINT32)-1;

        UINT32 _written = 0;
        BOOL result = ::WriteFile(this->handle, Str, write / sizeof(ECHAR), &_written, NULLPTR);
        
        if (!result || _written == 0)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IPipeError::SystemError,
                error
            };
        }

        Str += _written / sizeof(ECHAR);
        written += _written / sizeof(ECHAR);
    }

    return {
        TRUE,
        CytexLab::Interface::IPipeError::None,
        0
    };
}

CytexLab::Interface::IPipeResult PipeImpl::Write(LPCVOID Data, UINT64 Size)
{
    if (!Data)
        return {
            FALSE,
            CytexLab::Interface::IPipeError::NullPointer,
            0
        };
    
    if (Size == 0)
        return {
            TRUE,
            CytexLab::Interface::IPipeError::None,
            0
        };
    
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
            return {
                FALSE,
                CytexLab::Interface::IPipeError::SystemError,
                error
            };
        }

        Data = (LPCVOID)((LPUINT8)Data + _written);
        written += _written;
    }

    return {
        TRUE,
        CytexLab::Interface::IPipeError::None,
        0
    };
}

CytexLab::Interface::IPipeResult PipeImpl::Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            FALSE,
            CytexLab::Interface::IPipeError::NullPointer,
            0
        };
    
    if (BufferSize == 0)
        return {
            TRUE,
            CytexLab::Interface::IPipeError::None,
            0
        };
    
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
            return {
                FALSE,
                CytexLab::Interface::IPipeError::SystemError,
                error
            };
        }

        if (_readed == 0)
            break;

        Buffer += _readed / sizeof(ECHAR);
        readed += _readed / sizeof(ECHAR);
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;

    return {
        TRUE,
        CytexLab::Interface::IPipeError::None,
        0
    };
}

CytexLab::Interface::IPipeResult PipeImpl::Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            TRUE,
            CytexLab::Interface::IPipeError::None,
            0
        };
    
    if (BufferSize == 0)
        return {
            TRUE,
            CytexLab::Interface::IPipeError::None,
            0
        };
    
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
            return {
                FALSE,
                CytexLab::Interface::IPipeError::SystemError,
                error
            };
        }

        if (_readed == 0)
            break;

        Buffer = (LPVOID)((LPUINT8)Buffer + _readed);
        readed += _readed;
    }

    if (Readed)
        *Readed = readed;

    return {
        TRUE,
        CytexLab::Interface::IPipeError::None,
        0
    };
}

CytexLab::Interface::IPipeResult PipeImpl::Connect()
{
    if (this->owner)
    {
        BOOL connected = ::ConnectNamedPipe(this->handle, NULLPTR);
        
        if (!connected)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IPipeError::SystemError,
                error
            };
        }
        else
        {
            return {
                TRUE,
                CytexLab::Interface::IPipeError::None,
                0
            };
        }
    }
    else 
    {
        return {
            FALSE,
            CytexLab::Interface::IPipeError::RequiredOwner,
            0
        };
    }
}