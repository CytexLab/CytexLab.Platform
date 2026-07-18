/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "PoolImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

CytexLab::Interface::ISystemResult SystemImpl::CreatePool(CytexLab::Interface::IPool*& Out, UINT64 Size)
{
    if (Size == 0)
        return {
                FALSE,
                CytexLab::Interface::ISystemError::InvalidPoolSize,
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

    HANDLE heap = ::GetProcessHeap();
    LPVOID base = ::HeapAlloc(heap, 0, Size);

    if (!base)
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

    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(PoolImpl));

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

    PoolImpl* pi = new (mem) PoolImpl(base, Size);
    Out = (CytexLab::Interface::IPool*) pi;

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

CytexLab::Interface::ISystemResult SystemImpl::DestroyPool(CytexLab::Interface::IPool* Pool)
{
    if (!Pool)
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

    PoolImpl* pi = (PoolImpl*) Pool;

    LPVOID base = pi->GetBase();

    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, base);

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