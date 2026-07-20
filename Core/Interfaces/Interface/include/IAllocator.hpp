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
        struct IAllocatorHandle
        {
            UINT64 id;
            UINT64 size;
        };

        enum class IAllocatorError : UINT8
        {
            None,
            NullPointer,
            InvalidHandle,
            InvalidSize,
            OutOfMemory,
            SystemError
        };

        struct IAllocatorResult
        {
            BOOL Success;
            IAllocatorError Error;
            UINT32 SystemError;
        };

        class IAllocator
        {
        public:
            virtual IAllocatorResult Allocate(IAllocatorHandle& Out, UINT64 Size)= 0;
            virtual IAllocatorResult Free(IAllocatorHandle Handle) = 0;
            virtual IAllocatorResult Reallocate(IAllocatorHandle& Handle, UINT64 NewSize) = 0;

            virtual LPVOID Resolve(CytexLab::Interface::IAllocatorHandle Handle) = 0;

            virtual UINT64 GetTotalSize() = 0;
            virtual UINT64 GetFree() = 0;
            virtual UINT64 GetUsed() = 0;
            virtual UINT64 GetTotalAllocates() = 0;
            virtual UINT64 GetTotalAllocatedBlocks() = 0;
        };
    }
}