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
#include "ProcessImpl.hpp"

ProcessImpl::ProcessImpl(PROCESS_INFORMATION PI)
{
    this->pi = PI;
}

ProcessImpl::~ProcessImpl()
{

}

PROCESS_INFORMATION ProcessImpl::GetPi()
{
    return this->pi;
}

void ProcessImpl::Terminate(UINT32 Code)
{
    BOOL result = ::TerminateProcess(this->pi.hProcess, Code);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}

void ProcessImpl::Join()
{
    UINT32 result = ::WaitForSingleObject(this->pi.hProcess, (UINT32)-1);

    if (result == WAIT_OBJECT_0)
    {
        return;
    }
    else
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}