#include "Unicode.hpp"

UINT64 Unicode::StrLen(LPCECHAR Str)
{
    if (!Str)
        return 0;

    LPCECHAR p = Str;
    while (*p) p++;
    return p - Str;
}

BOOL Unicode::StrCpy(LPCECHAR From, LPECHAR To)
{
    if (!From || !To)
        return FALSE;

    while (*From)
        *To++ = *From++;

    return TRUE;
}

BOOL Unicode::StrCmp(LPCECHAR Str1, LPCECHAR Str2)
{
    if (!Str1 && !Str2)
        return TRUE;
    else if (!Str1 || !Str2)
        return FALSE;

    while (*Str1)
    {
        if (!*Str2)
            return FALSE;

        if (*Str1++ != *Str2++)
            return FALSE;
    }

    return *Str2 == 0;
}

Unicode::ConvertResult2 Unicode::UIntToStr(UINT64 Int, LPECHAR Str, UINT64 StrSize)
{
    if (!Str)
        return {
            FALSE,
            ConvertError::NullPointer
        };
    
    ECHAR buf[21];
    UINT8 bufPos = 0;

    if (Int == 0)
    {
        if (StrSize < 2)
            return {
                FALSE,
                ConvertError::BufferTooSmall
            };
        
        Str[0] = U'0';
        Str[1] = U'\0';
            
        return {
            TRUE,
            ConvertError::None
        };
    }

    while (Int > 0)
    {
        ECHAR sym = U'0' + (Int % 10);
        buf[bufPos++] = sym;
        Int /= 10;
    }

    if (StrSize < bufPos)
        return {
            FALSE,
            ConvertError::BufferTooSmall
        };
    
    bufPos--;

    while (true)
    {
        *Str = buf[bufPos];
        Str++;

        if (bufPos == 0)
            break;
        else
            bufPos--;
    }

    *Str = U'\0';

    return {
        TRUE,
        ConvertError::None
    };
}

Unicode::ConvertResult2 Unicode::UIntToStr(INT64 Int, LPECHAR Str, UINT64 StrSize)
{
    if (!Str)
        return {
            FALSE,
            ConvertError::NullPointer
        };
    
    ECHAR buf[21];
    UINT8 bufPos = 0;

    if (Int == 0)
    {
        if (StrSize < 2)
            return {
                FALSE,
                ConvertError::BufferTooSmall
            };
        
        Str[0] = U'0';
        Str[1] = U'\0';
            
        return {
            TRUE,
            ConvertError::None
        };
    }

    BOOL isNegative = FALSE;

    if (Int < 0)
    {
        isNegative = TRUE;
        Int *= -1;
    }

    while (Int > 0)
    {
        ECHAR sym = U'0' + (Int % 10);
        buf[bufPos++] = sym;
        Int /= 10;
    }

    if (!isNegative)
    {
        if (StrSize < bufPos)
            return {
                FALSE,
                ConvertError::BufferTooSmall
            };
    }
    else
    {
        if (StrSize < bufPos + 1)
            return {
                FALSE,
                ConvertError::BufferTooSmall
            };
        
        *Str = U'-';
        Str++;
    }
    
    
    bufPos--;

    while (true)
    {
        *Str = buf[bufPos];
        Str++;

        if (bufPos == 0)
            break;
        else
            bufPos--;
    }

    *Str = U'\0';

    return {
        TRUE,
        ConvertError::None
    };
}

Unicode::ConvertResult2 Unicode::UStrToInt(LPCECHAR Str, LPUINT64 Int)
{
    if (!Str || !Int)
        return {
            FALSE,
            ConvertError::NullPointer
        };
    
    if (*Str == U'-')
    {
        return {
            FALSE,
            ConvertError::InvalidNumber
        };
    }

    ECHAR buf[21];
    UINT8 bufPos = 0;

    while (true)
    {
        ECHAR sym = *Str;

        if (sym >= U'0' && sym <= U'9')
        {
            buf[bufPos++] = sym;
        }
        else
        {
            break;
        }

        Str++;
    }

    if (bufPos == 0)
    {
        return {
            FALSE,
            ConvertError::InvalidNumber
        };
    }

    UINT64 i = 0;

    for (UINT8 j = 0; j < bufPos; j++)
    {
        if (i > (((UINT64)-1) - (buf[j] - U'0')) / 10) {
            return {FALSE, ConvertError::BufferOverflow};
        }
        i *= 10;
        i += buf[j] - U'0';
    }

    *Int = i;

    return {
        TRUE,
        ConvertError::None
    };
}

Unicode::ConvertResult2 Unicode::UStrToInt(LPCECHAR Str, LPINT64 Int)
{
    if (!Str || !Int)
        return {
            FALSE,
            ConvertError::NullPointer
        };
    
    BOOL isNegative = FALSE;

    if (*Str == U'-')
    {
        isNegative = TRUE;
        Str++;
    }

    ECHAR buf[21];
    UINT8 bufPos = 0;

    while (true)
    {
        ECHAR sym = *Str;

        if (sym >= U'0' && sym <= U'9')
        {
            buf[bufPos++] = sym;
        }
        else
        {
            break;
        }

        Str++;
    }

    if (bufPos == 0)
    {
        return {
            FALSE,
            ConvertError::InvalidNumber
        };
    }

    INT64 i = 0;

    for (UINT8 j = 0; j < bufPos; j++)
    {
        if (i > (INT64_MAX - (buf[j] - U'0')) / 10) {
            return {FALSE, ConvertError::BufferOverflow};
        }
        i *= 10;
        i += buf[j] - U'0';
    }

    if (isNegative) i *= -1;

    *Int = i;

    return {
        TRUE,
        ConvertError::None
    };
}

Unicode::ConvertResult Unicode::ToUTF32(LPCCHAR From, LPECHAR To)
{
    if (!From || !To)
        return {FALSE, Unicode::ConvertError::NullPointer};

    UINT8 byte = (UINT8)*From;
    UINT32 code_point = 0;
    UINT8 bytes_count = 0;

    if ((byte & 0x80) == 0x00) {
        code_point = byte;
        bytes_count = 1;
    }
    else if ((byte & 0xE0) == 0xC0) {
        code_point = (byte & 0x1F) << 6;
        bytes_count = 2;
    }
    else if ((byte & 0xF0) == 0xE0) {
        code_point = (byte & 0x0F) << 12;
        bytes_count = 3;
    }
    else if ((byte & 0xF8) == 0xF0) {
        code_point = (byte & 0x07) << 18;
        bytes_count = 4;
    }
    else {
        return {FALSE, Unicode::ConvertError::InvalidByte};
    }

    for (UINT8 i = 1; i < bytes_count; i++) {
        From++;
        if (!*From)
            return {FALSE, Unicode::ConvertError::InvalidByte};

        byte = (UINT8)*From;
        if ((byte & 0xC0) != 0x80)
            return {FALSE, Unicode::ConvertError::InvalidContinueByte};

        code_point |= (byte & 0x3F) << (6 * (bytes_count - i - 1));
    }

    *To = (ECHAR)code_point;
    return {TRUE, Unicode::ConvertError::None, bytes_count};
}

Unicode::ConvertResult Unicode::ToUTF32(LPCWCHAR From, LPECHAR To)
{
    if (!From || !To)
        return {FALSE, Unicode::ConvertError::NullPointer, 0};

    UINT32 code_point = 0;
    UINT16 first = (UINT16)*From;

    if (first < 0xD800 || first > 0xDFFF) {
        // BMP символ (не суррогат)
        code_point = first;
        From++;
        *To = (ECHAR)code_point;
        return {TRUE, Unicode::ConvertError::None, 2}; // 2 байта (WCHAR)
    }
    else if (first >= 0xD800 && first <= 0xDBFF) {
        // High-суррогат — читаем low-суррогат
        From++;
        if (!*From)
            return {FALSE, Unicode::ConvertError::InvalidByte, 0};

        UINT16 second = (UINT16)*From;
        if (second < 0xDC00 || second > 0xDFFF)
            return {FALSE, Unicode::ConvertError::InvalidContinueByte, 0};

        code_point = ((first - 0xD800) << 10) + (second - 0xDC00) + 0x10000;
        From++;
        *To = (ECHAR)code_point;
        return {TRUE, Unicode::ConvertError::None, 4}; // 4 байта (2 WCHAR)
    }
    else {
        // Low-суррогат без high-суррогата
        return {FALSE, Unicode::ConvertError::InvalidByte, 0};
    }
}

Unicode::ConvertResult Unicode::ToUTF16(LPCECHAR From, LPWCHAR To)
{
    if (!From || !To)
        return {FALSE, Unicode::ConvertError::NullPointer};

    UINT32 code_point = (UINT32)*From;

    if (code_point <= 0xFFFF) {
        // BMP символ
        *To = (WCHAR)code_point;
        return {TRUE, Unicode::ConvertError::None, 2};
    }
    else if (code_point >= 0x10000 && code_point <= 0x10FFFF) {
        // Суррогатная пара
        UINT32 offset = code_point - 0x10000;
        To[0] = (WCHAR)(0xD800 | (offset >> 10));
        To[1] = (WCHAR)(0xDC00 | (offset & 0x3FF));
        return {TRUE, Unicode::ConvertError::None, 4};
    }
    else {
        return {FALSE, Unicode::ConvertError::InvalidByte};
    }
}

Unicode::ConvertResult Unicode::ToUTF8(LPCECHAR From, LPCHAR To)
{
    if (!From || !To)
        return {FALSE, Unicode::ConvertError::NullPointer, 0};

    UINT32 code_point = (UINT32)*From;

    if (code_point < 0x80) {
        To[0] = (CHAR)code_point;
        return {TRUE, Unicode::ConvertError::None, 1};
    }
    else if (code_point < 0x800) {
        To[0] = (CHAR)(0xC0 | (code_point >> 6));
        To[1] = (CHAR)(0x80 | (code_point & 0x3F));
        return {TRUE, Unicode::ConvertError::None, 2};
    }
    else if (code_point < 0x10000) {
        To[0] = (CHAR)(0xE0 | (code_point >> 12));
        To[1] = (CHAR)(0x80 | ((code_point >> 6) & 0x3F));
        To[2] = (CHAR)(0x80 | (code_point & 0x3F));
        return {TRUE, Unicode::ConvertError::None, 3};
    }
    else if (code_point < 0x110000) {
        To[0] = (CHAR)(0xF0 | (code_point >> 18));
        To[1] = (CHAR)(0x80 | ((code_point >> 12) & 0x3F));
        To[2] = (CHAR)(0x80 | ((code_point >> 6) & 0x3F));
        To[3] = (CHAR)(0x80 | (code_point & 0x3F));
        return {TRUE, Unicode::ConvertError::None, 4};
    }
    else {
        return {FALSE, Unicode::ConvertError::InvalidByte};
    }
}

Unicode::ConvertStringResult Unicode::ToUTF32String(LPCCHAR From, LPECHAR To)
{
    if (!From || !To)
        return {
            FALSE, 
            Unicode::ConvertError::NullPointer, 
            {FALSE, Unicode::ConvertError::None, 0},
            0, 
            0
        };

    UINT64 c = 0;

    while (*From)
    {
        ConvertResult result = Unicode::ToUTF32(From, To);

        if (!result.Success)
        {
            return {FALSE, Unicode::ConvertError::FailConvertSymbol, result, c, 0};
        }

        c++;
        To++;
        From += result.CountBytes;
    }

    return {
        TRUE, 
        Unicode::ConvertError::None, 
        {TRUE, Unicode::ConvertError::None, 0}, 
        0, 
        c
    };
}

Unicode::ConvertStringResult Unicode::ToUTF32String(LPCWCHAR From, LPECHAR To)
{
    if (!From || !To)
        return {
            FALSE, 
            Unicode::ConvertError::NullPointer, 
            {FALSE, Unicode::ConvertError::None, 0},
            0, 
            0
        };

    UINT64 c = 0;

    while (*From)
    {
        ConvertResult result = Unicode::ToUTF32(From, To);

        if (!result.Success)
        {
            return {FALSE, Unicode::ConvertError::FailConvertSymbol, result, c, 0};
        }

        c++;
        To++;
        From += result.CountBytes / 2;
    }

    return {
        TRUE, 
        Unicode::ConvertError::None, 
        {TRUE, Unicode::ConvertError::None, 0}, 
        0, 
        c
    };
}

Unicode::ConvertStringResult Unicode::ToUTF16String(LPCECHAR From, LPWCHAR To)
{
    if (!From || !To)
        return {
            FALSE, 
            Unicode::ConvertError::NullPointer, 
            {FALSE, Unicode::ConvertError::None, 0},
            0, 
            0
        };

    UINT64 c = 0;

    while (*From)
    {
        ConvertResult result = Unicode::ToUTF16(From, To);

        if (!result.Success)
        {
            return {FALSE, Unicode::ConvertError::FailConvertSymbol, result, c, 0};
        }

        c++;
        To += result.CountBytes / 2;
        From++;
    }

    return {
        TRUE, 
        Unicode::ConvertError::None, 
        {TRUE, Unicode::ConvertError::None, 0}, 
        0, 
        c
    };
}

Unicode::ConvertStringResult Unicode::ToUTF8String(LPCECHAR From, LPCHAR To)
{
    if (!From || !To)
        return {
            FALSE, 
            Unicode::ConvertError::NullPointer, 
            {FALSE, Unicode::ConvertError::None, 0},
            0, 
            0
        };

    UINT64 c = 0;

    while (*From)
    {
        ConvertResult result = Unicode::ToUTF8(From, To);

        if (!result.Success)
        {
            return {FALSE, Unicode::ConvertError::FailConvertSymbol, result, c, 0};
        }

        c++;
        To += result.CountBytes;
        From++;
    }

    return {
        TRUE, 
        Unicode::ConvertError::None, 
        {TRUE, Unicode::ConvertError::None, 0}, 
        0, 
        c
    };
}