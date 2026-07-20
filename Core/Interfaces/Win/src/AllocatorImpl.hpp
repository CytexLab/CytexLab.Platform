/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#include "IAllocator.hpp"

#define MAX_ALLOCATED_ITEMS 512
#define MAX_ALLOCATED_BLOCK 128
#define INITIAL_SIZE (16 * 1024)
#define CACHE_SIZE 16

struct AllocatorItem
{
    UINT64 id;
    UINT64 size;
    UINT64 offset;
};

struct AllocatorBlock
{
    LPVOID base;
    AllocatorItem items[MAX_ALLOCATED_ITEMS];
    UINT64 allocated;
    UINT64 total;
    UINT64 used;
    UINT64 free;
};

struct AllocatorCache
{
    UINT64 id;
    LPVOID ptr;
};

class AllocatorImpl : public CytexLab::Interface::IAllocator
{
private:
    AllocatorBlock blocks[MAX_ALLOCATED_BLOCK];
    AllocatorCache cache[CACHE_SIZE];
    UINT64 total_block;
    UINT64 total_size;
    UINT64 total_used;
    UINT64 total_free;
    UINT64 total_allocates;

    UINT64 next_id;

    UINT64 findFreeBlock(UINT64 Size);
    UINT64 findHole(UINT64 Block, UINT64 Size);
    BOOL allocateNewBlock(UINT64 MinSize);
    void defragmentBlock(UINT64 Block);
    UINT64 insertItem(UINT64 Block, UINT64 Size, UINT64 Offset);
    BOOL freeItem(UINT64 Id);
public:
    AllocatorImpl();
    ~AllocatorImpl();

    CytexLab::Interface::IAllocatorResult Init();
    void DeInit();

    CytexLab::Interface::IAllocatorResult Allocate(CytexLab::Interface::IAllocatorHandle& Out, UINT64 Size) override;
    CytexLab::Interface::IAllocatorResult Free(CytexLab::Interface::IAllocatorHandle Handle) override;
    CytexLab::Interface::IAllocatorResult Reallocate(CytexLab::Interface::IAllocatorHandle& Handle, UINT64 NewSize) override;

    LPVOID Resolve(CytexLab::Interface::IAllocatorHandle Handle) override;

    UINT64 GetTotalSize() override;
    UINT64 GetFree() override;
    UINT64 GetUsed() override;
    UINT64 GetTotalAllocates() override;
    UINT64 GetTotalAllocatedBlocks() override;
};