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
        typedef UINT32 (*IThreadFunc)(LPVOID Arg);

        class IThread
        {
        public:
            virtual void Start() = 0;
            virtual void Join() = 0;
            virtual void Terminate() = 0;
            virtual UINT64 GetID() = 0;
            virtual void IsRunning(BOOL& Out) = 0;
        };
    }
}