/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
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

        class IAllocator
        {
        public:
            virtual void Allocate(IAllocatorHandle& Out, UINT64 Size)= 0;
            virtual void Free(IAllocatorHandle Handle) = 0;
            virtual void Reallocate(IAllocatorHandle& Handle, UINT64 NewSize) = 0;

            virtual LPVOID Resolve(CytexLab::Interface::IAllocatorHandle Handle) = 0;

            virtual UINT64 GetTotalSize() = 0;
            virtual UINT64 GetFree() = 0;
            virtual UINT64 GetUsed() = 0;
            virtual UINT64 GetTotalAllocates() = 0;
            virtual UINT64 GetTotalAllocatedBlocks() = 0;
        };
    }
}