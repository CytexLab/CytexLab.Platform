#include "FileImpl.hpp"
#include "WinImports.hpp"
#include "Mem.hpp"

FileImpl::FileImpl(HANDLE Handle)
{
    this->handle = Handle;
}

FileImpl::~FileImpl()
{
    
}

HANDLE FileImpl::GetHandle()
{
    return this->handle;
}

CytexLab::Interface::IFileResult FileImpl::Write(LPCECHAR Str)
{
    if (!Str)
        return {
            FALSE, 
            CytexLab::Interface::IFileError::NullPointer, 
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
            CytexLab::Interface::IFileError::None,
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

        /*
         * Писать UTF-32 в файл?
         * Ну, а кто запрещает
         * Главное потом это открыть редактором
         * :)
        */

        Unicode::ConvertResult result = Unicode::ToUTF8(Str, &buf[0]);

        if (!result.Success)
            return {
                FALSE,
                CytexLab::Interface::IFileError::FailConvert,
                result,
                0
            };
        
        BOOL w_result = ::WriteFile(this->handle, &buf[0], result.CountBytes, NULLPTR, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IFileError::SystemError,
                result,
                error
            };
        }

        Str++;
    }

    return {
        TRUE,
        CytexLab::Interface::IFileError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        }
    };
}

CytexLab::Interface::IFileResult FileImpl::WriteLine(LPCECHAR Str)
{
    CytexLab::Interface::IFileResult result = this->Write(Str);

    if (!result.Success)
        return result;

    return this->Write((LPCECHAR) U"\r\n");
}

CytexLab::Interface::IFileResult FileImpl::Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            FALSE,
            CytexLab::Interface::IFileError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            }
        };
    
    if (BufferSize == 0)
        return {
            TRUE,
            CytexLab::Interface::IFileError::None,
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
        BOOL w_result = ::ReadFile(this->handle, &buf[bufPos], 1, &_, NULLPTR);
        
        if (!w_result)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IFileError::SystemError,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                error
            };
        }

        if (_ == 0)
            break;

        Unicode::ConvertResult result = Unicode::ToUTF32(&buf[0], Buffer);

        if (!result.Success)
        {
            if (bufPos < 3) bufPos++;
            else
                return {
                    FALSE,
                    CytexLab::Interface::IFileError::FailConvert,
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
        CytexLab::Interface::IFileError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        },
        0
    };
}

CytexLab::Interface::IFileResult FileImpl::Write(LPCVOID Data, UINT64 Size)
{
    if (!Data)
        return {
            FALSE,
            CytexLab::Interface::IFileError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    UINT64 written = 0;

    while (written < Size)
    {
        UINT64 write = Size - written;
        UINT32 _written = 0;

        if (write > (UINT32)-1)
            write = (UINT32)-1;

        BOOL result_w = ::WriteFile(this->handle, Data, write, &_written, NULLPTR);
        
        if (!result_w)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IFileError::SystemError,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                error
            };
        }

        if (_written == 0) // Мы больше не можем писать??? Не должно быть, но оставим
            break;
        
        written += _written;
    }

    return {
        TRUE,
        CytexLab::Interface::IFileError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        },
        0
    };
}

CytexLab::Interface::IFileResult FileImpl::Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed)
{
    if (!Buffer)
        return {
            FALSE,
            CytexLab::Interface::IFileError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };

    UINT64 readed = 0;

    while (readed < BufferSize)
    {
        UINT64 read = BufferSize - readed;
        UINT32 _readed = 0;

        if (read > (UINT32)-1)
            read = (UINT32)-1;

        BOOL result_w = ::ReadFile(this->handle, (LPVOID)((LPCHAR)Buffer + readed), read, &_readed, NULLPTR);

        if (!result_w)
        {
            UINT32 error = ::GetLastError();
            return {
                FALSE,
                CytexLab::Interface::IFileError::SystemError,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                error
            };
        }

        if (_readed == 0) // Конец файла?
            break;        // Ну тогда выходим
        
        readed += _readed;
    }

    if (Readed)
        *Readed = readed;

    return {
        TRUE,
        CytexLab::Interface::IFileError::None,
        {
            TRUE,
            Unicode::ConvertError::None,
            0
        },
        0
    };
}

CytexLab::Interface::IFileResult FileImpl::GetFileSize(LPUINT64 Out)
{
    if (!Out)
        return {
            FALSE,
            CytexLab::Interface::IFileError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    
    LARGE_INTEGER li;
    BOOL result = ::GetFileSizeEx(this->handle, &li);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IFileError::SystemError,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            error
        };
    }
    else
    {
        *Out = (UINT64)li.QuadPart;

        return {
            TRUE,
            CytexLab::Interface::IFileError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    }
}

CytexLab::Interface::IFileResult FileImpl::Seek(CytexLab::Interface::IFileSeekMode Mode, INT64 Offset, LPUINT64 NewPos)
{
    if (!NewPos)
        return {
            FALSE,
            CytexLab::Interface::IFileError::NullPointer,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };

    UINT32 dwMoveMethod;

    switch (Mode)
    {
        case CytexLab::Interface::IFileSeekMode::Start:
            dwMoveMethod = FILE_BEGIN;
            break;
        case CytexLab::Interface::IFileSeekMode::CurrentPos:
            dwMoveMethod = FILE_CURRENT;
            break;
        case CytexLab::Interface::IFileSeekMode::End:
            dwMoveMethod = FILE_END;
            break;
        default:
            return { // Хер знает как такое возможно, но пусть будет
                FALSE,
                CytexLab::Interface::IFileError::InvalidMoveMethod,
                {
                    TRUE,
                    Unicode::ConvertError::None,
                    0
                },
                0
            };
            break;
    }

    LARGE_INTEGER offset;
    offset.QuadPart = Offset;

    LARGE_INTEGER new_pos;

    BOOL result = ::SetFilePointerEx(this->handle, offset, &new_pos, dwMoveMethod);

    if (!result)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IFileError::SystemError,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            error
        };
    }
    else
    {
        *NewPos = (UINT64) new_pos.QuadPart;
        return {
            TRUE,
            CytexLab::Interface::IFileError::None,
            {
                TRUE,
                Unicode::ConvertError::None,
                0
            },
            0
        };
    }
}