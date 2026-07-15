/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


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