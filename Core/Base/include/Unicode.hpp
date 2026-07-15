/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "Types.hpp"

namespace Unicode
{
    // ====================== [Удобные функции] ======================
    UINT64 StrLen(LPCECHAR Str);
    BOOL StrCpy(LPCECHAR From, LPECHAR To);
    BOOL StrCmp(LPCECHAR Str1, LPCECHAR Str2);

    // ====================== [Конвертация] ======================

    enum class ConvertError : UINT8 {
        None,
        NullPointer,
        InvalidContinueByte,
        InvalidByte,
        FailConvertSymbol,
        BufferOverflow,
        BufferTooSmall,
        InvalidNumber
    };

    struct ConvertResult {
        BOOL Success;
        ConvertError Error;
        UINT8 CountBytes = 0;
    };

    struct ConvertStringResult {
        BOOL Success;
        ConvertError Error;
        ConvertResult ResultSymbolConvert;
        UINT64 SymError;
        UINT64 Len;
    };

    struct ConvertResult2 {
        BOOL Success;
        ConvertError Error;
    };

    ConvertResult2 UIntToStr(UINT64 Int, LPECHAR Str, UINT64 StrSize);
    ConvertResult2 UIntToStr(INT64 Int, LPECHAR Str, UINT64 StrSize);
    ConvertResult2 UStrToInt(LPCECHAR Str, LPUINT64 Int);
    ConvertResult2 UStrToInt(LPCECHAR Str, LPINT64 Int);

    ConvertResult ToUTF32(LPCCHAR From, LPECHAR To);
    ConvertResult ToUTF32(LPCWCHAR From, LPECHAR To);
    ConvertResult ToUTF16(LPCECHAR From, LPWCHAR To);
    ConvertResult ToUTF8(LPCECHAR From, LPCHAR To);

    ConvertStringResult ToUTF32String(LPCCHAR From, LPECHAR To);
    ConvertStringResult ToUTF32String(LPCWCHAR From, LPECHAR To);
    ConvertStringResult ToUTF16String(LPCECHAR From, LPWCHAR To);
    ConvertStringResult ToUTF8String(LPCECHAR From, LPCHAR To);
}