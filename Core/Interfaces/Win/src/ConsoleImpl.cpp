/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#include "ConsoleImpl.hpp"
#include "Unicode.hpp"
#include "Mem.hpp"
#include "WinImports.hpp"

void ConsoleImpl::SetLink(CytexLab::Interface::IConsoleLink Link)
{
    this->link = Link;
}

CytexLab::Interface::IConsoleResult ConsoleImpl::WriteConsole(LPCECHAR Str)
{
    if (!Str)
        return {
            FALSE, 
            CytexLab::Interface::IConsoleError::NullPointer, 
            {
                FALSE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    UINT64 len = Unicode::StrLen(Str);

    if (len == 0)
        return {
            TRUE,
            CytexLab::Interface::IConsoleError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    while (*Str)
    {
        WCHAR buf[2];

        Unicode::ConvertResult result = Unicode::ToUTF16(Str, &buf[0]);

        if (!result.Success)
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::FailConvert,
                result,
                0
            };
        
        BOOL w_result = ::WriteConsoleW(this->link.Handle.hOut, &buf[0], result.CountBytes / 2, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::SystemError,
                result,
                error
            };
        }

        Str++;
    }

    return {
        TRUE,
        CytexLab::Interface::IConsoleError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        }
    };
}

CytexLab::Interface::IConsoleResult ConsoleImpl::WriteFile(LPCECHAR Str)
{
    if (!Str)
        return {
            FALSE, 
            CytexLab::Interface::IConsoleError::NullPointer, 
            {
                FALSE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    UINT64 len = Unicode::StrLen(Str);

    if (len == 0)
        return {
            TRUE,
            CytexLab::Interface::IConsoleError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    while (*Str)
    {
        CHAR buf[4];

        Unicode::ConvertResult result = Unicode::ToUTF8(Str, &buf[0]);

        if (!result.Success)
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::FailConvert,
                result,
                0
            };
        
        BOOL w_result = ::WriteFile(this->link.Handle.hOut, &buf[0], result.CountBytes, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::SystemError,
                result,
                error
            };
        }

        Str++;
    }

    return {
        TRUE,
        CytexLab::Interface::IConsoleError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        }
    };
}

CytexLab::Interface::IConsoleResult ConsoleImpl::Write(LPCECHAR Str)
{
    if (this->link.Settings.hOutIsFile)
        return this->WriteFile(Str);
    else
        return this->WriteConsole(Str);
}

CytexLab::Interface::IConsoleResult ConsoleImpl::WriteLine (LPCECHAR Str)
{
    CytexLab::Interface::IConsoleResult result = this->Write(Str);

    if (!result.Success)
        return result;

    return this->Write((LPCECHAR) U"\r\n");
}

CytexLab::Interface::IConsoleResult ConsoleImpl::ReadConsole(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            FALSE,
            CytexLab::Interface::IConsoleError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            }
        };
    
    if (BufferSize == 0)
        return {
            TRUE,
            CytexLab::Interface::IConsoleError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            }
        };
    
    UINT64 readed = 0;
    UINT8 bufPos = 0;
    WCHAR buf[2];

    memset(buf, 0, 4);

    while (readed < BufferSize - 1)
    {
        UINT32 _;
        BOOL w_result = ::ReadConsoleW(this->link.Handle.hIn, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::SystemError,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                error
            };
        }

        if (buf[0] == L'\r')
            continue;

        if (buf[0] == L'\n')
            break;

        Unicode::ConvertResult result = Unicode::ToUTF32(&buf[0], Buffer);

        if (!result.Success)
        {
            if (bufPos < 1) bufPos++;
            else
                return {
                    FALSE,
                    CytexLab::Interface::IConsoleError::FailConvert,
                    result,
                    0
                };
        }
        else
        {
            readed++;
            Buffer++;

            memset(buf, 0, 4);
            bufPos = 0;
        }
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;

    return {
        TRUE,
        CytexLab::Interface::IConsoleError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        },
        0
    };
}

CytexLab::Interface::IConsoleResult ConsoleImpl::ReadFile(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            FALSE,
            CytexLab::Interface::IConsoleError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            }
        };
    
    if (BufferSize == 0)
        return {
            TRUE,
            CytexLab::Interface::IConsoleError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            }
        };
    
    UINT64 readed = 0;
    UINT8 bufPos = 0;
    CHAR buf[4];

    memset(buf, 0, 4);

    while (readed < BufferSize - 1)
    {
        UINT32 _;
        BOOL w_result = ::ReadFile(this->link.Handle.hIn, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IConsoleError::SystemError,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                error
            };
        }

        if (buf[0] == '\r')
            continue;

        if (buf[0] == '\n')
            break;

        Unicode::ConvertResult result = Unicode::ToUTF32(&buf[0], Buffer);

        if (!result.Success)
        {
            if (bufPos < 3) bufPos++;
            else
                return {
                    FALSE,
                    CytexLab::Interface::IConsoleError::FailConvert,
                    result,
                    0
                };
        }
        else
        {
            readed++;
            Buffer++;

            memset(buf, 0, 4);
            bufPos = 0;
        }
    }

    *Buffer = U'\0';

    if (Readed)
        *Readed = readed;

    return {
        TRUE,
        CytexLab::Interface::IConsoleError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        },
        0
    };
}

CytexLab::Interface::IConsoleResult ConsoleImpl::ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (this->link.Settings.hInIsFile)
        return this->ReadFile(Buffer, BufferSize, Readed);
    else
        return this->ReadConsole(Buffer, BufferSize, Readed);
}