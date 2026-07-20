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
        enum class IProcessError : UINT8
        {
            None,
            SystemError
        };

        struct IProcessResult
        {
            BOOL Success;
            IProcessError Error;
            UINT32 SystemError;
        };

        class IProcess
        {
        public:
            virtual IProcessResult Terminate(UINT32 Code) = 0;
            virtual IProcessResult Join() = 0;
        };
    }
}