#include "UTF.hpp"

static inline UINT8 UTF8ByteLength(UINT8 byte)
{
    if ((byte & 0x80) == 0x00)
        return 1;
    if ((byte & 0xE0) == 0xC0)
        return 2;
    if ((byte & 0xF0) == 0xE0)
        return 3;
    if ((byte & 0xF8) == 0xF0)
        return 4;
    return 0;
}

static inline BOOL IsUTF8Continuation(UINT8 byte)
{
    return (byte & 0xC0) == 0x80;
}

static inline UINT32 DecodeUTF8Continuation(UINT8 byte)
{
    return byte & 0x3F;
}

cl::UTF::SConvertSymbolResult
cl::UTF::ConvertUTF8ToUTF32(LPCCHAR From, LPECHAR To)
{
    SConvertSymbolResult result = {TRUE, EConvertSymbolError::None, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::NullPointer;
        return result;
    }

    UINT8 first = static_cast<UINT8>(*From);
    UINT8 len = UTF8ByteLength(first);

    if (len == 0)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::InvalidByte;
        return result;
    }

    result.BytesCount = len;
    UINT32 codepoint = 0;

    switch (len)
    {
        case 1:
        {
            codepoint = first;
            break;
        }
        case 2:
        {
            UINT8 second = static_cast<UINT8>(*(From + 1));
            if (!IsUTF8Continuation(second))
            {
                result.Success = FALSE;
                result.Error = EConvertSymbolError::InvalidContinueByte;
                return result;
            }
            codepoint = (first & 0x1F) << 6;
            codepoint |= DecodeUTF8Continuation(second);
            break;
        }
        case 3:
        {
            UINT8 second = static_cast<UINT8>(*(From + 1));
            UINT8 third = static_cast<UINT8>(*(From + 2));
            if (!IsUTF8Continuation(second) || !IsUTF8Continuation(third))
            {
                result.Success = FALSE;
                result.Error = EConvertSymbolError::InvalidContinueByte;
                return result;
            }
            codepoint = (first & 0x0F) << 12;
            codepoint |= DecodeUTF8Continuation(second) << 6;
            codepoint |= DecodeUTF8Continuation(third);
            break;
        }
        case 4:
        {
            UINT8 second = static_cast<UINT8>(*(From + 1));
            UINT8 third = static_cast<UINT8>(*(From + 2));
            UINT8 fourth = static_cast<UINT8>(*(From + 3));
            if (!IsUTF8Continuation(second) || !IsUTF8Continuation(third) || !IsUTF8Continuation(fourth))
            {
                result.Success = FALSE;
                result.Error = EConvertSymbolError::InvalidContinueByte;
                return result;
            }
            codepoint = (first & 0x07) << 18;
            codepoint |= DecodeUTF8Continuation(second) << 12;
            codepoint |= DecodeUTF8Continuation(third) << 6;
            codepoint |= DecodeUTF8Continuation(fourth);
            break;
        }
        default:
        {
            result.Success = FALSE;
            result.Error = EConvertSymbolError::InvalidByte;
            return result;
        }
    }

    *To = static_cast<ECHAR>(codepoint);
    result.BytesCount = len;
    return result;
}

cl::UTF::SConvertSymbolResult
cl::UTF::ConvertUTF16ToUTF32(LPCWCHAR From, LPECHAR To)
{
    SConvertSymbolResult result = {TRUE, EConvertSymbolError::None, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::NullPointer;
        return result;
    }

    UINT16 first = static_cast<UINT16>(*From);
    UINT32 codepoint = 0;

    if (first >= 0xD800 && first <= 0xDBFF)
    {
        UINT16 second = static_cast<UINT16>(*(From + 1));
        if (second >= 0xDC00 && second <= 0xDFFF)
        {
            codepoint = ((first - 0xD800) << 10) + (second - 0xDC00) + 0x10000;
            result.BytesCount = 4;
        }
        else
        {
            result.Success = FALSE;
            result.Error = EConvertSymbolError::InvalidContinueByte;
            return result;
        }
    }
    else if (first >= 0xDC00 && first <= 0xDFFF)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::InvalidContinueByte;
        return result;
    }
    else
    {
        codepoint = first;
        result.BytesCount = 2;
    }

    *To = static_cast<ECHAR>(codepoint);
    return result;
}

cl::UTF::SConvertSymbolResult
cl::UTF::ConvertUTF32ToUTF8(LPCECHAR From, LPCHAR To)
{
    SConvertSymbolResult result = {TRUE, EConvertSymbolError::None, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::NullPointer;
        return result;
    }

    UINT32 codepoint = static_cast<UINT32>(*From);
    UINT8 len = 0;

    if (codepoint <= 0x7F)
        len = 1;
    else if (codepoint <= 0x7FF)
        len = 2;
    else if (codepoint <= 0xFFFF)
        len = 3;
    else if (codepoint <= 0x10FFFF)
        len = 4;
    else
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::InvalidByte;
        return result;
    }

    result.BytesCount = len;

    switch (len)
    {
        case 1:
        {
            To[0] = static_cast<CHAR>(codepoint);
            break;
        }
        case 2:
        {
            To[0] = static_cast<CHAR>(0xC0 | ((codepoint >> 6) & 0x1F));
            To[1] = static_cast<CHAR>(0x80 | (codepoint & 0x3F));
            break;
        }
        case 3:
        {
            To[0] = static_cast<CHAR>(0xE0 | ((codepoint >> 12) & 0x0F));
            To[1] = static_cast<CHAR>(0x80 | ((codepoint >> 6) & 0x3F));
            To[2] = static_cast<CHAR>(0x80 | (codepoint & 0x3F));
            break;
        }
        case 4:
        {
            To[0] = static_cast<CHAR>(0xF0 | ((codepoint >> 18) & 0x07));
            To[1] = static_cast<CHAR>(0x80 | ((codepoint >> 12) & 0x3F));
            To[2] = static_cast<CHAR>(0x80 | ((codepoint >> 6) & 0x3F));
            To[3] = static_cast<CHAR>(0x80 | (codepoint & 0x3F));
            break;
        }
        default:
        {
            result.Success = FALSE;
            result.Error = EConvertSymbolError::InvalidByte;
            return result;
        }
    }

    return result;
}

cl::UTF::SConvertSymbolResult
cl::UTF::ConvertUTF32ToUTF16(LPCECHAR From, LPWCHAR To)
{
    SConvertSymbolResult result = {TRUE, EConvertSymbolError::None, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertSymbolError::NullPointer;
        return result;
    }

    UINT32 codepoint = static_cast<UINT32>(*From);

    if (codepoint <= 0xFFFF)
    {
        *To = static_cast<WCHAR>(codepoint);
        result.BytesCount = 2;
        return result;
    }

    if (codepoint >= 0x10000 && codepoint <= 0x10FFFF)
    {
        UINT32 adjusted = codepoint - 0x10000;
        To[0] = static_cast<WCHAR>(0xD800 | ((adjusted >> 10) & 0x3FF));
        To[1] = static_cast<WCHAR>(0xDC00 | (adjusted & 0x3FF));
        result.BytesCount = 4;
        return result;
    }

    result.Success = FALSE;
    result.Error = EConvertSymbolError::InvalidByte;
    return result;
}

cl::UTF::SConvertStringResult
cl::UTF::ConvertStringUTF8ToUTF32(LPCCHAR From, LPECHAR To)
{
    SConvertStringResult result = {TRUE, {TRUE, EConvertSymbolError::None, 0}, EConvertStringError::None, 0, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertStringError::NullPointer;
        return result;
    }

    LPCCHAR ptr = From;
    while (*ptr)
        ptr++;
    UINT64 len = ptr - From;

    UINT64 i = 0;
    while (i < len)
    {
        SConvertSymbolResult convert = ConvertUTF8ToUTF32(From, To);
        result.LastConvertSymbol = convert;

        if (!convert.Success)
        {
            result.Success = FALSE;
            result.Error = EConvertStringError::FailConvertSymbol;
            return result;
        }

        i += convert.BytesCount;

        From += convert.BytesCount;
        To++;

        result.SymbolsCount++;
        result.BytesCount += convert.BytesCount;
    }

    *To = U'\0';

    return result;
}

cl::UTF::SConvertStringResult
cl::UTF::ConvertStringUTF16ToUTF32(LPCWCHAR From, LPECHAR To)
{
    SConvertStringResult result = {TRUE, {TRUE, EConvertSymbolError::None, 0}, EConvertStringError::None, 0, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertStringError::NullPointer;
        return result;
    }

    LPCWCHAR ptr = From;
    while (*ptr)
        ptr++;
    UINT64 len = ptr - From;

    UINT64 i = 0;
    while (i < len)
    {
        SConvertSymbolResult convert = ConvertUTF16ToUTF32(From, To);
        result.LastConvertSymbol = convert;

        if (!convert.Success)
        {
            result.Success = FALSE;
            result.Error = EConvertStringError::FailConvertSymbol;
            return result;
        }

        i += convert.BytesCount / 2;

        From += convert.BytesCount / 2;
        To++;

        result.BytesCount += convert.BytesCount;
        result.SymbolsCount++;
    }

    *To = U'\0';

    return result;
}

cl::UTF::SConvertStringResult
cl::UTF::ConvertStringUTF32ToUTF8(LPCECHAR From, LPCHAR To)
{
    SConvertStringResult result = {TRUE, {TRUE, EConvertSymbolError::None, 0}, EConvertStringError::None, 0, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertStringError::NullPointer;
        return result;
    }

    LPCECHAR ptr = From;
    while (*ptr)
        ptr++;
    UINT64 len = ptr - From;

    UINT64 i = 0;

    while (i < len)
    {
        SConvertSymbolResult convert = ConvertUTF32ToUTF8(From, To);
        result.LastConvertSymbol = convert;

        if (!convert.Success)
        {
            result.Error = EConvertStringError::FailConvertSymbol;
            result.Success = FALSE;
            return result;
        }

        i++;

        From++;
        To += convert.BytesCount;

        result.BytesCount += convert.BytesCount;
        result.SymbolsCount++;
    }

    *To = '\0';

    return result;
}

cl::UTF::SConvertStringResult
cl::UTF::ConvertStringUTF32ToUTF16(LPCECHAR From, LPWCHAR To)
{
    SConvertStringResult result = {TRUE, {TRUE, EConvertSymbolError::None, 0}, EConvertStringError::None, 0, 0};

    if (From == nullptr || To == nullptr)
    {
        result.Success = FALSE;
        result.Error = EConvertStringError::NullPointer;
        return result;
    }

    LPCECHAR ptr = From;
    while (*ptr)
        ptr++;
    UINT64 len = ptr - From;

    UINT64 i = 0;

    while (i < len)
    {
        SConvertSymbolResult convert = ConvertUTF32ToUTF16(From, To);
        result.LastConvertSymbol = convert;

        if (!convert.Success)
        {
            result.Success = FALSE;
            result.Error = EConvertStringError::FailConvertSymbol;
            return result;
        }

        i++;

        From++;
        To += convert.BytesCount / 2;

        result.SymbolsCount++;
        result.BytesCount += convert.BytesCount;
    }

    *To = L'\0';

    return result;
}

cl::UTF::SStringFunctionsResult cl::UTF::UIntToString(UINT64 Number, LPECHAR Buffer)
{
    SStringFunctionsResult result = {TRUE, EStringFunctionsError::None};

    if (Buffer == nullptr)
    {
        result.Success = FALSE;
        result.Error = EStringFunctionsError::NullPointer;
        return result;
    }

    if (Number == 0)
    {
        *Buffer++ = U'0';
        *Buffer = U'\0';
    }

    ECHAR buf[21];
    UINT8 i = 0;

    while (Number > 0)
    {
        UINT64 dig = Number % 10;
        buf[i++] = U'0' + dig;
        Number /= 10;
    }

    for (UINT8 j = i; j > 0; j--)
        *Buffer++ = buf[j - 1];

    *Buffer = U'\0';

    return result;
}

cl::UTF::SStringFunctionsResult cl::UTF::SIntToString(INT64 Number, LPECHAR Buffer)
{
    SStringFunctionsResult result = {TRUE, EStringFunctionsError::None};

    if (Buffer == nullptr)
    {
        result.Success = FALSE;
        result.Error = EStringFunctionsError::None;
        return result;
    }

    if (Number == 0)
    {
        *Buffer++ = U'0';
        *Buffer = U'\0';
        return result;
    }

    BOOL negative = FALSE;

    if (Number < 0)
    {
        negative = TRUE;
        Number = -Number;
    }

    ECHAR buf[21];
    UINT8 i = 0;

    while (Number > 0)
    {
        INT64 dig = Number % 10;
        buf[i++] = U'0' + dig;
        Number /= 10;
    }

    if (negative)
        *Buffer++ = U'-';

    for (UINT8 j = i; j > 0; j--)
        *Buffer++ = buf[j-1];

    *Buffer = U'\0';

    return result;
}

cl::UTF::SStringFunctionsResult cl::UTF::StringToUInt(LPCECHAR String, LPUINT64 Number)
{
    SStringFunctionsResult result = {TRUE, EStringFunctionsError::None};

    if (String == nullptr || Number == nullptr)
    {
        result.Success = FALSE;
        result.Error = EStringFunctionsError::NullPointer;
        return result;
    }

    if (*String == '-')
    {
        result.Success = FALSE;
        result.Error = EStringFunctionsError::InvalidString;
        return result;
    }

    UINT64 num = 0;

    if (*String == U'0')
    {
        *Number = num;
        return result;
    }

    while (true)
    {
        if (*String == U'\0' || *String < U'0' || *String > U'9')
            break;

        num *= 10;
        num += *String++ - U'0';
    }

    *Number = num;
    return result;
}

cl::UTF::SStringFunctionsResult cl::UTF::StringToSInt(LPCECHAR String, LPINT64 Number)
{
    SStringFunctionsResult result = {TRUE, EStringFunctionsError::None};

    if (String == nullptr || Number == nullptr)
    {
        result.Success = FALSE;
        result.Error = EStringFunctionsError::NullPointer;
        return result;
    }

    BOOL negative = FALSE;

    if (*String == U'-')
    {
        String++;
        negative = TRUE;
    }

    INT64 num = 0;

    if (*String == U'0')
    {
        *Number = num;
        return result;
    }

    while (true)
    {
        if (*String == U'\0' || *String < U'0' || *String > U'9')
            break;

        num *= 10;
        num += *String++ - U'0';
    }

    if (negative)
        num = -num;

    *Number = num;
    return result;
}
