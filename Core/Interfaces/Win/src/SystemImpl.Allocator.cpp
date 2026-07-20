/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "AllocatorImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"

CytexLab::Interface::ISystemResult SystemImpl::CreateAllocator(CytexLab::Interface::IAllocator *&Out)
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(AllocatorImpl));

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

    AllocatorImpl* ai = new (mem) AllocatorImpl();
    CytexLab::Interface::IAllacatorResult init_result = ai->Init();

    if (!init_result.Success)
    {
        // Init мог упасть только из-за HeapAlloc внутри AddBlock -
        // блоков нет, чистить нечего, просто освобождаем сам объект
        ::HeapFree(heap, 0, ai);

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
                init_result.SystemError
        };
    }

    Out = (CytexLab::Interface::IAllocator*) ai;

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

CytexLab::Interface::ISystemResult SystemImpl::DestroyAllocator(CytexLab::Interface::IAllocator *Allacator)
{
    if (!Allacator)
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

    AllocatorImpl* ai = (AllocatorImpl*) Allacator;
    ai->DeInit();

    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, ai);

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