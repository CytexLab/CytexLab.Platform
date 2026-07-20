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
    this->next_id = 0;
}

AllocatorImpl::~AllocatorImpl()
{

}

void AllocatorImpl::Init()
{
    this->total_block = 1;
    this->total_size = INITIAL_SIZE;
    this->total_free = INITIAL_SIZE;

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, INITIAL_SIZE);

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        ::ExitProcess(-1);
    }

    this->blocks[0].base = mem;
    this->blocks[0].total = INITIAL_SIZE;
    this->blocks[0].free = INITIAL_SIZE;
    this->blocks[0].allocated = 0;
    this->blocks[0].used = 0;
}

void AllocatorImpl::DeInit()
{
    HANDLE heap = ::GetProcessHeap();

    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        if (!::HeapFree(heap, 0, block->base))
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }
    }
}

UINT64 AllocatorImpl::findFreeBlock(UINT64 Size)
{
    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        if (block->free >= Size && block->allocated < MAX_ALLOCATED_ITEMS)
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

        currentOffset = item->offset + item->size;
    }

    if (block->total - currentOffset >= Size)
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

    for (UINT64 i = 0; i < CACHE_SIZE; i++)
    {
        this->cache[i] = {UNSET, NULLPTR};
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

LPVOID AllocatorImpl::Resolve(CytexLab::Interface::IAllocatorHandle Handle)
{
    for (UINT64 i = 0; i < CACHE_SIZE; i++)
    {
        if (this->cache[i].id == Handle.id)
            return this->cache[i].ptr;
    }

    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        for (UINT64 j = 0; j < block->allocated; j++)
        {
            AllocatorItem* item = &block->items[j];

            if (item->id == Handle.id)
            {
                LPVOID ptr = (LPVOID)((LPUINT8)block->base + item->offset);

                for (UINT64 i = CACHE_SIZE-1; i > 0; i--)
                {
                    this->cache[i] = this->cache[i-1];
                }
                this->cache[0].id = Handle.id;
                this->cache[0].ptr = ptr;

                return ptr;
            }
        }
    }

    return NULLPTR;
}

BOOL AllocatorImpl::freeItem(UINT64 Id)
{
    for (UINT64 i = 0; i < this->total_block; i++)
    {
        AllocatorBlock* block = &this->blocks[i];

        for (UINT64 j = 0; j < block->allocated; j++)
        {
            AllocatorItem* item = &block->items[j];

            if (item->id == Id)
            {
                UINT64 freedSize = item->size;

                for (UINT64 k = j; k < block->allocated - 1; k++) {
                    block->items[k] = block->items[k + 1];
                }

                block->allocated--;
                block->free += freedSize;
                block->used -= freedSize;

                this->total_used -= freedSize;
                this->total_free += freedSize;
                this->total_allocates--;

                return TRUE;
            }
        }
    }

    for (UINT64 c = 0; c < CACHE_SIZE; c++) {
        if (this->cache[c].id == Id) {
            this->cache[c] = {UNSET, NULLPTR};
            break;
        }
    }

    return FALSE;
}

void AllocatorImpl::Allocate(CytexLab::Interface::IAllocatorHandle &Out, UINT64 Size)
{
    if (Size == 0)
        ::ExitProcess(-1);

    UINT64 block = this->findFreeBlock(Size);

    if (block != -1)
    {
        UINT64 offset = this->findHole(block, Size);

        if (offset == -1)
        {
            this->defragmentBlock(block);
            offset = this->findHole(block, Size);
        }

        UINT64 id = this->insertItem(block, Size, offset);

        Out = {
                id,
                Size
        };

        this->total_allocates++;
        this->total_used += Size;
        this->total_free -= Size;
    }
    else
    {
        if (this->total_block == MAX_ALLOCATED_BLOCK)
            ::ExitProcess(-1);

        BOOL result = this->allocateNewBlock(Size);

        if (!result)
        {
            UINT32 error = ::GetLastError();
            ::ExitProcess(-1);
        }

        return this->Allocate(Out, Size);
    }
}

void AllocatorImpl::Free(CytexLab::Interface::IAllocatorHandle Handle)
{
    BOOL result = this->freeItem(Handle.id);

    if (!result)
    {
        ::ExitProcess(-1);
    }
}

void AllocatorImpl::Reallocate(CytexLab::Interface::IAllocatorHandle& Handle, UINT64 NewSize)
{
    this->Free(Handle);
    this->Allocate(Handle, NewSize);
}