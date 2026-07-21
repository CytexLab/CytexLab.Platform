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
        class IWindow
        {
        public:
            virtual void Process() = 0;
            virtual BOOL IsOpen() = 0;
            virtual UINT64 GetWidth() = 0;
            virtual UINT64 GetHeight() = 0;
        };
    }
}