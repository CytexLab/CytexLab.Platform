/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * CytexLab (c) 2026
 */

#include "AllocatorImpl.hpp"
#include "WinImports.hpp"
#include "Mem.hpp"

AllocatorImpl::AllocatorImpl()
{
    this->total_used = 0;
    this->total_allocates = 0;
    this->total_block = 0;
    this->total_free = 0;
    this->total_size = 0;
}

AllocatorImpl::~AllocatorImpl()
{

}

CytexLab::Interface::IAllocatorResult AllocatorImpl::Init()
{
    this->total_block = 1;
    this->total_size = INITIAL_SIZE;
    this->total_free = INITIAL_SIZE;

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, INITIAL_SIZE);

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IAllocatorError::SystemError,
            error
        };
    }

    this->blocks[0].base = mem;
    this->blocks[0].total = INITIAL_SIZE;
    this->blocks[0].free = INITIAL_SIZE;
    this->blocks[0].allocated = 0;
    this->blocks[0].used = 0;

    return {
        TRUE,
        CytexLab::Interface::IAllocatorError::None,
        0
    };
}

void AllocatorImpl::DeInit()
{
    HANDLE heap = ::GetProcessHeap();

    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        ::HeapFree(heap, 0, block->base);
    }
}

UINT64 AllocatorImpl::findFreeBlock(UINT64 Size)
{
    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        if (block->free >= Size)
            return i;
    }

    return -1;
}

UINT64 AllocatorImpl::findHole(UINT64 Block, UINT64 Size)
{
    AllocatorBlock* block = &this->blocks[Block];

    UINT64 currentOffset = 0;

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        AllocatorItem* item = &block->items[i];

        if (item->offset - currentOffset >= Size)
            return currentOffset;

        currentOffset += item->offset + item->size;
    }

    if (block->free - currentOffset >= Size)
        return currentOffset;

    return -1;
}

BOOL AllocatorImpl::allocateNewBlock(UINT64 MinSize)
{
    UINT64 size = MinSize * 2;

    if (size < INITIAL_SIZE)
        size = INITIAL_SIZE;

    AllocatorBlock* block = &this->blocks[this->total_block];

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, size);

    if (!mem)
        return FALSE;

    block->base = mem;
    block->total = size;
    block->free = size;
    block->used = 0;
    block->allocated = 0;

    this->total_block++;
    this->total_free += size;
    this->total_size += size;

    return TRUE;
}

void AllocatorImpl::defragmentBlock(UINT64 Block)
{
    AllocatorBlock* block = &this->blocks[Block];

    UINT64 currentOffset = 0;

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        AllocatorItem* item = &block->items[i];

        if (item->offset != currentOffset)
        {
            LPVOID from = ((LPUINT8)block->base) + item->offset;
            LPVOID to = ((LPUINT8)block->base) + currentOffset;
            memcpy(to, from, item->size);

            item->offset = currentOffset;
        }

        currentOffset += item->size;
    }
}

UINT64 AllocatorImpl::insertItem(UINT64 Block, UINT64 Size, UINT64 Offset)
{
    AllocatorBlock* block = &this->blocks[Block];

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        AllocatorItem* item = &block->items[i];

        if (item->offset > Offset)
        {
            for (UINT64 j = block->allocated; j > i; j--)
            {
                block->items[j] = block->items[j-1];
            }

            item->offset = Offset;
            item->size = Size;
            item->id = this->next_id;

            this->next_id++;

            block->allocated++;
            block->free -= Size;
            block->used += Size;

            return item->id;
        }
    }

    AllocatorItem* item = &block->items[block->allocated];

    item->offset = Offset;
    item->size = Size;
    item->id = this->next_id;

    this->next_id++;

    block->allocated++;
    block->free -= Size;
    block->used += Size;

    return item->id;
}

UINT64 AllocatorImpl::GetFree()
{
    return this->total_free;
}

UINT64 AllocatorImpl::GetUsed()
{
    return this->total_used;
}

UINT64 AllocatorImpl::GetTotalSize()
{
    return this->total_size;
}

UINT64 AllocatorImpl::GetTotalAllocates()
{
    return this->total_allocates;
}

UINT64 AllocatorImpl::GetTotalAllocatedBlocks()
{
    return this->total_block;
}