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

#include "SystemImpl.hpp"
#include "WinImports.hpp"

void SystemImpl::GetArgs(LPUINT64 Out)
{
    if (!Out)
        ::ExitProcess(-1);

    LPWCHAR cmdLine = ::GetCommandLineW();

    INT32 args;
    LPWCHAR* argv = ::CommandLineToArgvW(cmdLine, &args);

    *Out = (UINT64)args;


    LPVOID result = ::LocalFree(argv);

    if (argv == result)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}

void SystemImpl::GetArgv(LPECHAR *Out)
{
    if (!Out)
        ::ExitProcess(-1);

    LPWCHAR cmdLine = ::GetCommandLineW();

    INT32 args;
    LPWCHAR* argv = ::CommandLineToArgvW(cmdLine, &args);

    for (UINT32 i = 0; i < args; i++)
    {
        Unicode::ConvertStringResult convert_result = Unicode::ToUTF32String(argv[i], Out[i]);

        if (!convert_result.Success)
        {
            ::ExitProcess(-1);
        }
    }

    LPVOID result = ::LocalFree(argv);

    if (result == argv)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }
}