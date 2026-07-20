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
        class IMutex
        {
        public:
            virtual void Lock() = 0;
            virtual void UnLock() = 0;
            virtual void TryLock(BOOL& Out) = 0;
        };
    }
}