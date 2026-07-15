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

CytexLab::Interface::IThreadResult ThreadImpl::Start()
{
    UINT32 result = ::ResumeThread(this->handle);

    if (result == -1)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IThreadError::SystemError,
            error
        };
    }
    else
    {
        return {
            TRUE,
            CytexLab::Interface::IThreadError::None,
            0
        };
    }
}

CytexLab::Interface::IThreadResult ThreadImpl::Join()
{
    UINT32 result = ::WaitForSingleObject(this->handle, -1);

    if (result == WAIT_FAILED)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IThreadError::SystemError,
            error
        };
    }
    else if (result == WAIT_OBJECT_0)
    {
        return {
            TRUE,
            CytexLab::Interface::IThreadError::None,
            0
        }; 
    }
    else
    {
        return {
            FALSE,
            CytexLab::Interface::IThreadError::UnknownSystemError,
            result
        };
    }
}

CytexLab::Interface::IThreadResult ThreadImpl::Terminate()
{
    BOOL result = ::TerminateThread(this->handle, -1);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IThreadError::SystemError,
            error
        };
    }
    else
    {
        return {
            TRUE,
            CytexLab::Interface::IThreadError::None,
            0
        };
    }
}

CytexLab::Interface::IThreadResult ThreadImpl::IsRunning(BOOL& Out)
{
    UINT32 result = ::WaitForSingleObject(this->handle, 0);

    if (result == WAIT_OBJECT_0)
    {
        Out = FALSE;
        return {
            TRUE,
            CytexLab::Interface::IThreadError::None,
            0
        };
    }
    else if (result == WAIT_TIMEOUT)
    {
        Out = TRUE;
        return {
            TRUE,
            CytexLab::Interface::IThreadError::None,
            0
        };
    }
    else
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IThreadError::SystemError,
            error
        };
    }
}