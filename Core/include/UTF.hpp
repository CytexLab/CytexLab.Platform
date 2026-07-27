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

#pragma once

#include "Platform.hpp"

namespace cl
{
    namespace UTF
    {
        enum class EConvertSymbolError : UINT8
        {
            None = 0,
            InvalidByte = 1,
            InvalidContinueByte = 2,
            NullPointer = 3
        };

        enum class EConvertStringError : UINT8
        {
            None = 0,
            FailConvertSymbol = 1,
            NullPointer = 2,
        };

        struct SConvertSymbolResult
        {
            BOOL Success;
            EConvertSymbolError Error;
            UINT8 BytesCount;
        };

        struct SConvertStringResult
        {
            BOOL Success;
            SConvertSymbolResult LastConvertSymbol;
            EConvertStringError Error;
            UINT8 BytesCount;
            UINT8 SymbolsCount;
        };

        SConvertSymbolResult ConvertUTF8ToUTF32(LPCCHAR From, LPECHAR To);
        SConvertSymbolResult ConvertUTF16ToUTF32(LPCWCHAR From, LPECHAR To);
        SConvertSymbolResult ConvertUTF32ToUTF8(LPCECHAR From, LPCHAR To);
        SConvertSymbolResult ConvertUTF32ToUTF16(LPCECHAR From, LPWCHAR To);

        SConvertStringResult ConvertStringUTF8ToUTF32(LPCCHAR From, LPECHAR To);
        SConvertStringResult ConvertStringUTF16ToUTF32(LPCWCHAR From, LPECHAR To);
        SConvertStringResult ConvertStringUTF32ToUTF8(LPCECHAR From, LPCHAR To);
        SConvertStringResult ConvertStringUTF32ToUTF16(LPCECHAR From, LPWCHAR To);
    }
}