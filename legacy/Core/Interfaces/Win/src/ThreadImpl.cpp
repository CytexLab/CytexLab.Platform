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


#include "ThreadImpl.hpp"
#include "WinImports.hpp"

ThreadImpl::ThreadImpl(HANDLE hThread, UINT64 id)
{
    this->handle = hThread;
    this->id = id;
}

ThreadImpl::~ThreadImpl()
{

}

HANDLE ThreadImpl::GetHandle()
{
    return this->handle;
}

UINT64 ThreadImpl::GetID()
{
    return this->id;
}

void ThreadImpl::Start()
{
    UINT32 result = ::ResumeThread(this->handle);

    if (result == -1)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}

void ThreadImpl::Join()
{
    UINT32 result = ::WaitForSingleObject(this->handle, -1);

    if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
    else if (result == WAIT_OBJECT_0)
    {
        return;
    }
    else
    {
        ::ExitProcess(-1);
    }
}

void ThreadImpl::Terminate()
{
    BOOL result = ::TerminateThread(this->handle, -1);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}

void ThreadImpl::IsRunning(BOOL& Out)
{
    UINT32 result = ::WaitForSingleObject(this->handle, 0);

    if (result == WAIT_OBJECT_0)
    {
        Out = FALSE;
    }
    else if (result == WAIT_TIMEOUT)
    {
        Out = TRUE;
    }
    else
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}