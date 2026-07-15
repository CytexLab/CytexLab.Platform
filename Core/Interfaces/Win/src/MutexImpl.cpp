/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#include "MutexImpl.hpp"
#include "WinImports.hpp"

MutexImpl::MutexImpl(HANDLE Handle)
{
    this->handle = Handle;
}

MutexImpl::~MutexImpl()
{

}

HANDLE MutexImpl::GetHandle()
{
    return this->handle;
}

CytexLab::Interface::IMutexResult MutexImpl::Lock()
{
    UINT32 result = ::WaitForSingleObject(this->handle, (UINT32)-1);

    if (result == WAIT_OBJECT_0)
        return {
            TRUE,
            CytexLab::Interface::IMutexError::None,
            0
        };
    else if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IMutexError::SystemError,
            0
        };
    }
    else
    {
        return {
            FALSE,
            CytexLab::Interface::IMutexError::UnknownError,
            0
        };
    }
}

CytexLab::Interface::IMutexResult MutexImpl::UnLock()
{
    BOOL result = ::ReleaseMutex(this->handle);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IMutexError::SystemError,
            error
        };
    }
    else
    {
        return {
            TRUE,
            CytexLab::Interface::IMutexError::None,
            0
        };
    }
}

CytexLab::Interface::IMutexResult MutexImpl::TryLock(BOOL& Out)
{
    UINT32 result = ::WaitForSingleObject(this->handle, 0);

    if (result == WAIT_OBJECT_0)
    {
        Out = TRUE;
        return {
            TRUE,
            CytexLab::Interface::IMutexError::None,
            0
        };
    }
    else if (result == WAIT_TIMEOUT)
    {
        Out = FALSE;
        return {
            TRUE,
            CytexLab::Interface::IMutexError::None,
            0
        };
    }
    else if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IMutexError::SystemError,
            error
        };
    }
    else
    {
        return {
            FALSE,
            CytexLab::Interface::IMutexError::UnknownError,
            0
        };
    }
}