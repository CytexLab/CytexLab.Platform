/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "PipeImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"
#include "Mem.hpp"

CytexLab::Interface::ISystemResult SystemImpl::CreatePipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name)
{
    if (!Name)
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

    UINT64 size = (Unicode::StrLen(Name) * 2 + 9) * sizeof(WCHAR);

    HANDLE heap = ::GetProcessHeap();
    LPWCHAR buf = (LPWCHAR) ::HeapAlloc(heap, 0, size);

    if (!buf)
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

    memcpy(buf, L"\\\\.\\pipe\\", 9 * sizeof(WCHAR));

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Name, buf + 9);

    if (!convert_result.Success)
    {
        return {
                FALSE,
                CytexLab::Interface::ISystemError::FailConvert,
                convert_result,
                0
        };
    }

    HANDLE hPipe = ::CreateNamedPipeW(buf, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_WAIT, 2, 4096, 4096, 0, NULLPTR);

    if (!hPipe || hPipe == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                convert_result,
                error
        };
    }

    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(PipeImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                convert_result,
                error
        };
    }

    PipeImpl* pi = new (mem) PipeImpl(hPipe, TRUE);
    Out = (CytexLab::Interface::IPipe*) pi;

    return {
            TRUE,
            CytexLab::Interface::ISystemError::None,
            convert_result,
            0
    };
}

CytexLab::Interface::ISystemResult SystemImpl::OpenPipe(CytexLab::Interface::IPipe*& Out, LPCECHAR Name)
{
    if (!Name)
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

    UINT64 size = (Unicode::StrLen(Name) * 2 + 9) * sizeof(WCHAR);

    HANDLE heap = ::GetProcessHeap();
    LPWCHAR buf = (LPWCHAR) ::HeapAlloc(heap, 0, size);

    if (!buf)
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

    memcpy(buf, L"\\\\.\\pipe\\", 9 * sizeof(WCHAR));

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Name, buf + 9);

    if (!convert_result.Success)
    {
        return {
                FALSE,
                CytexLab::Interface::ISystemError::FailConvert,
                convert_result,
                0
        };
    }

    BOOL result = ::WaitNamedPipeW(buf, NMPWAIT_WAIT_FOREVER);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                convert_result,
                error
        };
    }

    HANDLE hPipe = ::CreateFileW(buf, GENERIC_READ | GENERIC_WRITE, 0, NULLPTR, OPEN_EXISTING, 0, NULLPTR);

    if (!hPipe || hPipe == (HANDLE) UNSET)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                convert_result,
                error
        };
    }

    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(PipeImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
                FALSE,
                CytexLab::Interface::ISystemError::SystemError,
                convert_result,
                error
        };
    }

    PipeImpl* pi = new (mem) PipeImpl(hPipe, FALSE);
    Out = (CytexLab::Interface::IPipe*) pi;

    return {
            TRUE,
            CytexLab::Interface::ISystemError::None,
            convert_result,
            0
    };
}

CytexLab::Interface::ISystemResult SystemImpl::DestroyPipe(CytexLab::Interface::IPipe* Pipe)
{
    if (!Pipe)
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

    PipeImpl* pi = (PipeImpl*) Pipe;

    HANDLE hPipe = pi->GetHandle();
    BOOL isOwner = pi->IsOwner();

    if (isOwner)
    {
        BOOL result = ::DisconnectNamedPipe(hPipe);

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
    }

    BOOL result = ::CloseHandle(hPipe);

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
    result = ::HeapFree(heap, 0, pi);

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