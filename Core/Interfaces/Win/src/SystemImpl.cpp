#include "SystemImpl.hpp"
#include "ConsoleImpl.hpp"
#include "WinImports.hpp"
#include "Placement.hpp"
#include "FileImpl.hpp"
#include "PoolImpl.hpp"
#include "ThreadImpl.hpp"
#include "MutexImpl.hpp"

SystemImpl::SystemImpl()
{}

SystemImpl::~SystemImpl()
{}

void SystemImpl::ExitProcess(UINT32 Code)
{
    ::ExitProcess(Code);
}

CytexLab::Interface::ISystemResult SystemImpl::CreateConsole(CytexLab::Interface::IConsole*& Out)
{
    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(ConsoleImpl));
    
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

    ConsoleImpl* ci = new (mem) ConsoleImpl();

    CytexLab::Interface::IConsoleSettings s;
    s = {FALSE, FALSE};

    CytexLab::Interface::IConsoleHandle h;
    h = {::GetStdHandle(STD_INPUT_HANDLE), 
        ::GetStdHandle(STD_OUTPUT_HANDLE)
    };

    CytexLab::Interface::IConsoleLink l;
    l = {s, h};

    ci->SetLink(l);

    Out = (CytexLab::Interface::IConsole*) ci;

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

CytexLab::Interface::ISystemResult SystemImpl::RedirectConsole(CytexLab::Interface::IConsole* Console, CytexLab::Interface::IFile* Out, CytexLab::Interface::IFile* In)
{
    if (!Console)
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

    CytexLab::Interface::IConsoleSettings s;
    CytexLab::Interface::IConsoleHandle h;

    if (Out)
    {
        s.hOutIsFile = TRUE;

        FileImpl* fi = (FileImpl*)Out;
        h.hOut = fi->GetHandle();
    }
    else
    {
        s.hOutIsFile = FALSE;
        h.hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    }

    if (In)
    {
        s.hInIsFile = TRUE;

        FileImpl* fi = (FileImpl*)In;
        h.hIn = fi->GetHandle();
    }
    else
    {
        s.hInIsFile = FALSE;
        h.hIn = ::GetStdHandle(STD_INPUT_HANDLE);
    }

    CytexLab::Interface::IConsoleLink l = {s, h};

    ConsoleImpl* ci = (ConsoleImpl*) Console;
    ci->SetLink(l);

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

CytexLab::Interface::ISystemResult SystemImpl::DestroyConsole(CytexLab::Interface::IConsole* Console)
{
    if (!Console)
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

    ConsoleImpl* ci = (ConsoleImpl*) Console;
    HANDLE heap = ::GetProcessHeap();
    BOOL result = ::HeapFree(heap, 0, ci);

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

CytexLab::Interface::ISystemResult SystemImpl::OpenFile(CytexLab::Interface::IFile*& Out, LPCECHAR Path, CytexLab::Interface::IFileOpenMode Mode)
{
    if (!Path)
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

    UINT32 dwDesiredAccess;
    UINT32 dwCreationDisposition;

    switch (Mode) {
        case CytexLab::Interface::IFileOpenMode::Read:
            dwDesiredAccess = GENERIC_READ;
            dwCreationDisposition = OPEN_EXISTING;
            break;
        case CytexLab::Interface::IFileOpenMode::Write:
            dwDesiredAccess = GENERIC_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
            break;
        case CytexLab::Interface::IFileOpenMode::ReadWrite:
            dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
            break;
        default:
            return {
                FALSE,
                CytexLab::Interface::ISystemError::InvalidOpenMode,
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

    WCHAR buf[256 * 2];

    Unicode::ConvertStringResult convert_result = Unicode::ToUTF16String(Path, &buf[0]);

    if (!convert_result.Success)
        return {
            FALSE,
            CytexLab::Interface::ISystemError::FailConvert,
            convert_result,
            0
        };

    HANDLE hFile = ::CreateFileW(&buf[0], dwDesiredAccess, FILE_SHARE_READ, NULLPTR, dwCreationDisposition, 0, NULLPTR);

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(FileImpl));

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::ISystemError::SystemError,
            convert_result,
            error
        };

    }

   FileImpl* fi = new (mem) FileImpl(hFile);
   Out = (CytexLab::Interface::IFile*) fi;

   return {
        TRUE,
        CytexLab::Interface::ISystemError::None,
        convert_result,
        0
    };
}

CytexLab::Interface::ISystemResult SystemImpl::CloseFile(CytexLab::Interface::IFile* File)
{
    if (!File)
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
    
    FileImpl* fi = (FileImpl*) File;
    BOOL result = ::CloseHandle(fi->GetHandle());
    
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

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, fi);

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

CytexLab::Interface::ISystemResult SystemImpl::CreateThread(CytexLab::Interface::IThread*& Thread, CytexLab::Interface::IThreadFunc Function, LPVOID Arg)
{
    if (!Function)
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

    UINT32 id;
    HANDLE hThread = ::CreateThread(NULLPTR, 1*1024*1024, Function, Arg, CREATE_SUSPENDED, &id);

    if (!hThread || hThread == (HANDLE) UNSET)
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

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(ThreadImpl));

    ThreadImpl* th = new (mem) ThreadImpl(hThread, id);
    
    Thread = (CytexLab::Interface::IThread*) th;

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
        }
    };
}

CytexLab::Interface::ISystemResult SystemImpl::DestroyThread(CytexLab::Interface::IThread* Thread)
{
    if (!Thread)
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
    
    ThreadImpl* ti = (ThreadImpl*) Thread;

    BOOL result = ::CloseHandle(ti->GetHandle());

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

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, ti);

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

CytexLab::Interface::ISystemResult SystemImpl::CreateMutex(CytexLab::Interface::IMutex*& Out)
{
    HANDLE hMutex = ::CreateMutexW(NULLPTR, FALSE, NULLPTR);

    if (!hMutex || hMutex == (HANDLE) UNSET)
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

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, sizeof(MutexImpl));

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

    MutexImpl* mi = new (mem) MutexImpl(hMutex);
    Out = (CytexLab::Interface::IMutex*) mi;

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

CytexLab::Interface::ISystemResult SystemImpl::DestroyMutex(CytexLab::Interface::IMutex* Mutex)
{
    if (!Mutex)
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
    
    MutexImpl* mi = (MutexImpl*) Mutex;
    HANDLE hMutex = mi->GetHandle();

    BOOL result = ::CloseHandle(hMutex);

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

    HANDLE heap = ::GetProcessHeap();
    result = ::HeapFree(heap, 0, mi);

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