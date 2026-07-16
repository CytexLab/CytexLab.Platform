/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "AllacatorImpl.hpp"
#include "WinImports.hpp"
#include "Mem.hpp"

AllacatorImpl::AllacatorImpl()
{
    this->total_block = 0;
    this->total_size = 0;
    this->total_used = 0;
    this->total_free = 0;
    this->total_allocates = 0;
    this->next_id = 0;
}

AllacatorImpl::~AllacatorImpl()
{
    HANDLE heap = ::GetProcessHeap();

    for (UINT64 i = 0; i < this->total_block; i++)
        ::HeapFree(heap, 0, this->blocks[i].base);
}

CytexLab::Interface::IAllacatorResult AllacatorImpl::Init()
{
    UINT64 index;
    return this->AddBlock(INITIAL_SIZE, index);
}

UINT64 AllacatorImpl::GetFree()
{
    return this->total_free;
}

UINT64 AllacatorImpl::GetUsed()
{
    return this->total_used;
}

UINT64 AllacatorImpl::GetTotalSize()
{
    return this->total_size;
}

UINT64 AllacatorImpl::GetTotalAllocates()
{
    return this->total_allocates;
}

UINT64 AllacatorImpl::GetTotalAllocatedBlocks()
{
    return this->total_block;
}

UINT64 AllacatorImpl::GetFreeBlock(UINT64 Size)
{
    for (UINT64 i = 0; i < this->total_block; i++)
    {
        if (this->blocks[i].free >= Size && this->blocks[i].allocated < MAX_ALLOCATED_ITEMS)
            return i;
    }

    return UNSET;
}

CytexLab::Interface::IAllacatorResult AllacatorImpl::AddBlock(UINT64 MinSize, UINT64& OutBlock)
{
    if (this->total_block >= MAX_ALLOCATED_BLOCK)
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::OutOfMemory,
            0
        };

    UINT64 size = MinSize * 2;

    if (size < INITIAL_SIZE)
        size = INITIAL_SIZE;

    HANDLE heap = ::GetProcessHeap();
    LPVOID mem = ::HeapAlloc(heap, 0, size);

    if (!mem)
    {
        UINT32 error = ::GetLastError();
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::SystemError,
            error
        };
    }

    UINT64 index = this->total_block;

    this->blocks[index].base = mem;
    this->blocks[index].allocated = 0;
    this->blocks[index].total = size;
    this->blocks[index].used = 0;
    this->blocks[index].free = size;

    this->total_block++;
    this->total_size += size;
    this->total_free += size;

    OutBlock = index;

    return {
        TRUE,
        CytexLab::Interface::IAllacatorError::None,
        0
    };
}

UINT64 AllacatorImpl::FindHole(UINT64 Block, UINT64 Size)
{
    AllacatorBlock* block = &this->blocks[Block];
    UINT64 currentOffset = 0;

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        AllacatorItem* item = &block->items[i];
        UINT64 freeSpace = item->offset - currentOffset;

        if (freeSpace >= Size)
            return currentOffset;

        currentOffset = item->offset + item->size;
    }

    if (block->total - currentOffset >= Size)
        return currentOffset;

    return UNSET;
}

void AllacatorImpl::DefragmentBlock(UINT64 Block)
{
    AllacatorBlock* block = &this->blocks[Block];
    UINT64 currentOffset = 0;

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        AllacatorItem* item = &block->items[i];

        if (item->offset != currentOffset)
        {
            LPVOID dst = (LPVOID)((UINT8*)block->base + currentOffset);
            LPVOID src = (LPVOID)((UINT8*)block->base + item->offset);

            memcpy(dst, src, item->size);
            item->offset = currentOffset;
        }

        currentOffset += item->size;
    }
}

UINT64 AllacatorImpl::AllocateAt(UINT64 Block, UINT64 Offset, UINT64 Size)
{
    AllacatorBlock* block = &this->blocks[Block];

    UINT64 insertIndex = block->allocated;

    for (UINT64 i = 0; i < block->allocated; i++)
    {
        if (block->items[i].offset > Offset)
        {
            insertIndex = i;
            break;
        }
    }

    for (UINT64 i = block->allocated; i > insertIndex; i--)
    {
        block->items[i] = block->items[i - 1];
    }

    AllacatorItem* item = &block->items[insertIndex];
    item->id = this->next_id++;
    item->size = Size;
    item->offset = Offset;

    block->allocated++;
    block->used += Size;
    block->free -= Size;

    return item->id;
}

BOOL AllacatorImpl::FindItemById(UINT64 Id, UINT64& OutBlock, UINT64& OutIndex)
{
    for (UINT64 b = 0; b < this->total_block; b++)
    {
        AllacatorBlock* block = &this->blocks[b];

        for (UINT64 i = 0; i < block->allocated; i++)
        {
            if (block->items[i].id == Id)
            {
                OutBlock = b;
                OutIndex = i;
                return TRUE;
            }
        }
    }

    return FALSE;
}

CytexLab::Interface::IAllacatorResult AllacatorImpl::Allocate(CytexLab::Interface::IAllacatorHandle& Out, UINT64 Size)
{
    if (Size == 0)
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::InvalidSize,
            0
        };

    UINT64 block = this->GetFreeBlock(Size);

    if (block == UNSET)
    {
        CytexLab::Interface::IAllacatorResult growResult = this->AddBlock(Size, block);

        if (!growResult.Success)
            return growResult;
    }

    UINT64 offset = this->FindHole(block, Size);

    if (offset == UNSET)
    {
        this->DefragmentBlock(block);
        offset = this->blocks[block].used;
    }

    UINT64 id = this->AllocateAt(block, offset, Size);

    Out.id = id;
    Out.size = Size;

    this->total_used += Size;
    this->total_free -= Size;
    this->total_allocates++;

    return {
        TRUE,
        CytexLab::Interface::IAllacatorError::None,
        0
    };
}

CytexLab::Interface::IAllacatorResult AllacatorImpl::Free(CytexLab::Interface::IAllacatorHandle Handle)
{
    UINT64 blockIdx, itemIdx;

    if (!this->FindItemById(Handle.id, blockIdx, itemIdx))
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::InvalidHandle,
            0
        };

    AllacatorBlock* block = &this->blocks[blockIdx];
    UINT64 size = block->items[itemIdx].size;

    block->used -= size;
    block->free += size;

    for (UINT64 j = itemIdx; j < block->allocated - 1; j++)
    {
        block->items[j] = block->items[j + 1];
    }

    block->allocated--;

    this->total_used -= size;
    this->total_free += size;

    return {
        TRUE,
        CytexLab::Interface::IAllacatorError::None,
        0
    };
}

CytexLab::Interface::IAllacatorResult AllacatorImpl::Reallocate(CytexLab::Interface::IAllacatorHandle Handle, UINT64 NewSize)
{
    if (NewSize == 0)
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::InvalidSize,
            0
        };

    UINT64 oldBlockIdx, oldItemIdx;

    if (!this->FindItemById(Handle.id, oldBlockIdx, oldItemIdx))
        return {
            FALSE,
            CytexLab::Interface::IAllacatorError::InvalidHandle,
            0
        };


    AllacatorBlock* oldBlock = &this->blocks[oldBlockIdx];
    UINT64 oldSize = oldBlock->items[oldItemIdx].size;

    if (NewSize <= oldSize)
    {
        UINT64 delta = oldSize - NewSize;

        oldBlock->items[oldItemIdx].size = NewSize;
        oldBlock->used -= delta;
        oldBlock->free += delta;
        this->total_used -= delta;
        this->total_free += delta;

        return {
            TRUE,
            CytexLab::Interface::IAllacatorError::None,
            0
        };
    }

    UINT64 growBy = NewSize - oldSize;

    UINT64 itemEnd = oldBlock->items[oldItemIdx].offset + oldSize;
    UINT64 boundary = (oldItemIdx + 1 < oldBlock->allocated)
        ? oldBlock->items[oldItemIdx + 1].offset
        : oldBlock->total;

    if (boundary - itemEnd >= growBy)
    {
        oldBlock->items[oldItemIdx].size = NewSize;
        oldBlock->used += growBy;
        oldBlock->free -= growBy;
        this->total_used += growBy;
        this->total_free -= growBy;

        return {
            TRUE,
            CytexLab::Interface::IAllacatorError::None,
            0
        };
    }

    UINT64 newBlockIdx = this->GetFreeBlock(NewSize);

    if (newBlockIdx == UNSET)
    {
        CytexLab::Interface::IAllacatorResult growResult = this->AddBlock(NewSize, newBlockIdx);

        if (!growResult.Success)
            return growResult;
    }

    UINT64 newOffset = this->FindHole(newBlockIdx, NewSize);

    if (newOffset == UNSET)
    {
        this->DefragmentBlock(newBlockIdx);
        newOffset = this->blocks[newBlockIdx].used;
    }

    LPVOID oldPtr = (LPVOID)((UINT8*)this->blocks[oldBlockIdx].base + this->blocks[oldBlockIdx].items[oldItemIdx].offset);
    LPVOID newPtr = (LPVOID)((UINT8*)this->blocks[newBlockIdx].base + newOffset);

    memcpy(newPtr, oldPtr, oldSize);

    AllacatorBlock* rb = &this->blocks[oldBlockIdx];

    rb->used -= oldSize;
    rb->free += oldSize;

    for (UINT64 j = oldItemIdx; j < rb->allocated - 1; j++)
        rb->items[j] = rb->items[j + 1];

    rb->allocated--;

    AllacatorBlock* nb = &this->blocks[newBlockIdx];
    UINT64 insertIndex = nb->allocated;

    for (UINT64 i = 0; i < nb->allocated; i++)
    {
        if (nb->items[i].offset > newOffset)
        {
            insertIndex = i;
            break;
        }
    }

    for (UINT64 i = nb->allocated; i > insertIndex; i--)
        nb->items[i] = nb->items[i - 1];

    nb->items[insertIndex].id = Handle.id;
    nb->items[insertIndex].size = NewSize;
    nb->items[insertIndex].offset = newOffset;

    nb->allocated++;
    nb->used += NewSize;
    nb->free -= NewSize;

    this->total_used += growBy;
    this->total_free -= growBy;

    return {
        TRUE,
        CytexLab::Interface::IAllacatorError::None,
        0
    };
}

LPVOID AllacatorImpl::Resolve(CytexLab::Interface::IAllacatorHandle Handle)
{
    UINT64 blockIdx, itemIdx;

    if (!this->FindItemById(Handle.id, blockIdx, itemIdx))
        return NULLPTR;

    AllacatorBlock* block = &this->blocks[blockIdx];
    return (LPVOID)((UINT8*)block->base + block->items[itemIdx].offset);
}