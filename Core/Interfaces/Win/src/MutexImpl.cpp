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

void MutexImpl::Lock()
{
    UINT32 result = ::WaitForSingleObject(this->handle, (UINT32)-1);

    if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
    else
    {
        ::ExitProcess(-1);
    }
}

void MutexImpl::UnLock()
{
    BOOL result = ::ReleaseMutex(this->handle);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}

void MutexImpl::TryLock(BOOL& Out)
{
    UINT32 result = ::WaitForSingleObject(this->handle, 0);

    if (result == WAIT_OBJECT_0)
    {
        Out = TRUE;
    }
    else if (result == WAIT_TIMEOUT)
    {
        Out = FALSE;
    }
    else if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
    else
    {
        ::ExitProcess(-1);
    }
}