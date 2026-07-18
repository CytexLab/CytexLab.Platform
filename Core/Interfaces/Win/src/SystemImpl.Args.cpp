/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "WinImports.hpp"

CytexLab::Interface::ISystemResult SystemImpl::GetArgs(LPUINT64 Out)
{
    if (!Out)
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

    LPWCHAR cmdLine = ::GetCommandLineW();

    INT32 args;
    LPWCHAR* argv = ::CommandLineToArgvW(cmdLine, &args);

    *Out = (UINT64)args;


    LPVOID result = ::LocalFree(argv);

    if (argv == result)
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

CytexLab::Interface::ISystemResult SystemImpl::GetArgv(LPECHAR *Out)
{
    if (!Out)
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

    LPWCHAR cmdLine = ::GetCommandLineW();

    INT32 args;
    LPWCHAR* argv = ::CommandLineToArgvW(cmdLine, &args);

    for (UINT32 i = 0; i < args; i++)
    {
        Unicode::ConvertStringResult convert_result = Unicode::ToUTF32String(argv[i], Out[i]);

        if (!convert_result.Success)
        {
            return {
                    FALSE,
                    CytexLab::Interface::ISystemError::FailConvert,
                    convert_result,
                    0
            };
        }
    }

    LPVOID result = ::LocalFree(argv);

    if (result == argv)
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