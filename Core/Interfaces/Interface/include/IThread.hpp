#pragma once

#include "Types.hpp"

namespace CytexLab
{
    namespace Interface
    {
        enum class IThreadError : UINT8
        {
            None,
            SystemError,
            UnknownSystemError
        };

        struct IThreadResult
        {
            BOOL Success;
            IThreadError Error;
            UINT32 SystemError;
        };

        typedef UINT32 (*IThreadFunc)(LPVOID Arg);

        class IThread
        {
        public:
            virtual IThreadResult Start() = 0;
            virtual IThreadResult Join() = 0;
            virtual IThreadResult Terminate() = 0;
            virtual UINT64 GetID() = 0;
            virtual IThreadResult IsRunning(BOOL& Out) = 0;
        };
    }
}