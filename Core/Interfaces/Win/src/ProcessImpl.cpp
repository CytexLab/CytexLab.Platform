/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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

CytexLab::Interface::IProcessResult ProcessImpl::Terminate(UINT32 Code)
{
    BOOL result = ::TerminateProcess(this->pi.hProcess, Code);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IProcessError::SystemError,
            error
        };
    }
    else
    {
        return {
            TRUE,
            CytexLab::Interface::IProcessError::None,
            0
        };
    }
}

CytexLab::Interface::IProcessResult ProcessImpl::Join()
{
    UINT32 result = ::WaitForSingleObject(this->pi.hProcess, (UINT32)-1);

    if (result == WAIT_OBJECT_0)
    {
        return {
            TRUE,
            CytexLab::Interface::IProcessError::None,
            0
        };
    }
    else
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IProcessError::SystemError,
            error
        };
    }
}