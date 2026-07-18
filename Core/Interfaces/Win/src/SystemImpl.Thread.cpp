/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "ThreadImpl.hpp"
#include "MutexImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

CytexLab::Interface::ISystemResult SystemImpl::CreateThread(CytexLab::Interface::IThread*& Thread, CytexLab::Interface::IThreadFunc Function, LPVOID Arg)
{
    if (!Function)
        return {
                FALSE,
                CytexLab::Interface::ISystemError::NullPointer,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                0
        };

    UINT32 id;
    HANDLE hThread = ::CreateThread(NULLPTR, 1*1024*1024, Function, Arg, CREATE_SUSPENDED, &id);

    if (!hThread || hThread == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(ThreadImpl));

    ThreadImpl* th = new (mem) ThreadImpl(hThread, id);

    Thread = (CytexLab::Interface::IThread*) th;

    return {
            TRUE,
            CytexLab::Interface::ISystemError::None,
            {
                    TRUE,
                    Unicode::ConvertError::None,
                    {
                            TRUE,
                            Unicode::ConvertError::None,
                            0
                    },
                    0,
                    0
            }
    };
}

CytexLab::Interface::ISystemResult SystemImpl::DestroyThread(CytexLab::Interface::IThread* Thread)
{
    if (!Thread)
        return {
                FALSE,
                CytexLab::Interface::ISystemError::NullPointer,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                0
        };

    ThreadImpl* ti = (ThreadImpl*) Thread;

    BOOL result = ::CloseHandle(ti->GetHandle());

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, ti);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }
    else
    {
        return {
                TRUE,
                CytexLab::Interface::ISystemError::None,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                0
        };
    }
}

CytexLab::Interface::ISystemResult SystemImpl::CreateMutex(CytexLab::Interface::IMutex*& Out)
{
    HANDLE hMutex = ::CreateMutexW(NULLPTR, FALSE, NULLPTR);

    if (!hMutex || hMutex == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(MutexImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }

    MutexImpl* mi = new (mem) MutexImpl(hMutex);
    Out = (CytexLab::Interface::IMutex*) mi;

    return {
            TRUE,
            CytexLab::Interface::ISystemError::None,
            {
                    TRUE,
                    Unicode::ConvertError::None,
                    {
                            TRUE,
                            Unicode::ConvertError::None,
                            0
                    },
                    0,
                    0
            },
            0
    };
}

CytexLab::Interface::ISystemResult SystemImpl::DestroyMutex(CytexLab::Interface::IMutex* Mutex)
{
    if (!Mutex)
        return {
                FALSE,
                CytexLab::Interface::ISystemError::NullPointer,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                0
        };

    MutexImpl* mi = (MutexImpl*) Mutex;
    HANDLE hMutex = mi->GetHandle();

    BOOL result = ::CloseHandle(hMutex);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, mi);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                error
        };
    }
    else
    {
        return {
                TRUE,
                CytexLab::Interface::ISystemError::None,
                {
                        TRUE,
                        Unicode::ConvertError::None,
                        {
                                TRUE,
                                Unicode::ConvertError::None,
                                0
                        },
                        0,
                        0
                },
                0
        };
    }
}