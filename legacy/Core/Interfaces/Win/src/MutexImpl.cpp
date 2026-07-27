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