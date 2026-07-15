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
        enum class IPoolError : UINT8
        {
            None,
            NullPointer,
            SystemError,
            InvalidSize,        // Size == 0 при Allocate
            OutOfMemory,         // нет подходящего свободного промежутка
            TooManyAllocations,  // достигнут MAX_ALLOCATES
            NotFound              // Free: такого блока не найдено
        };

        struct IPoolResult
        {
            BOOL Success;
            IPoolError Error;
            UINT32 SystemError;
        };

        struct IPoolItem
        {
            UINT64 Size;
            LPVOID Pointer;
        };

        class IPool
        {
        public:
            virtual IPoolResult Allocate(UINT64 Size, IPoolItem& Out) = 0;
            virtual IPoolResult Free(IPoolItem Item) = 0;

            virtual UINT64 GetTotal() = 0;
            virtual UINT64 GetFree() = 0;
            virtual UINT64 GetUsed() = 0;
        };
    }
}