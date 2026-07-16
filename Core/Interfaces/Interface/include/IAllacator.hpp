/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "Types.hpp"

namespace CytexLab
{
    namespace Interface
    {
        struct IAllacatorHandle
        {
            UINT64 id;
            UINT64 size;
        };

        enum class IAllacatorError : UINT8
        {
            None,
            NullPointer,
            InvalidHandle,
            OutOfMemory,
            SystemError
        };

        struct IAllacatorResult
        {
            BOOL Success;
            IAllacatorError Error;
            UINT32 SystemError;
        };

        class IAllacator
        {
        public:
            virtual IAllacatorResult Allocate(UINT64 Size, IAllacatorHandle& Out) = 0;
            virtual IAllacatorResult Free(IAllacatorHandle Handle) = 0;

            virtual UINT64 GetTotalSize() = 0;
            virtual UINT64 GetFree() = 0;
            virtual UINT64 GetUsed() = 0;
            virtual UINT64 GetTotalAllocates() = 0;
            virtual UINT64 GetTotalAllocatedBlocks() = 0;
        };
    }
}