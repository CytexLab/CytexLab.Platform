#pragma once

#include "Types.hpp"

namespace CytexLab
{
    namespace Interface
    {
        enum class IMutexError : UINT8
        {
            None,
            SystemError,
            UnknownError
        };

        struct IMutexResult
        {
            BOOL Success;
            IMutexError Error;
            UINT32 SystemError;
        };

        class IMutex
        {
        public:
            virtual IMutexResult Lock() = 0;
            virtual IMutexResult UnLock() = 0;
            virtual IMutexResult TryLock(BOOL& Out) = 0;
        };
    }
}