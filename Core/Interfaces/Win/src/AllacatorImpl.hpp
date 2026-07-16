/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#include "IAllacator.hpp"

#define MAX_ALLOCATED_ITEMS 512
#define MAX_ALLOCATED_BLOCK 128
#define INITIAL_SIZE (16 * 1024)

struct AllacatorItem
{
    UINT64 id;
    UINT64 size;
    UINT64 offset;
};

struct AllacatorBlock
{
    LPVOID base;
    AllacatorItem items[MAX_ALLOCATED_ITEMS];
    UINT64 allocated;
    UINT64 total;
    UINT64 used;
    UINT64 free;
};

class AllacatorImpl : public CytexLab::Interface::IAllacator
{
private:
    AllacatorBlock blocks[MAX_ALLOCATED_BLOCK];
    UINT64 total_block;
    UINT64 total_size;
    UINT64 total_used;
    UINT64 total_free;
    UINT64 total_allocates;

    UINT64 next_id;

    UINT64 GetFreeBlock(UINT64 Size);
    UINT64 FindHole(UINT64 Block, UINT64 Size);
    void DefragmentBlock(UINT64 Block);
    UINT64 AllocateAt(UINT64 Block, UINT64 Offset, UINT64 Size);
    BOOL FindItemById(UINT64 Id, UINT64& OutBlock, UINT64& OutIndex);
    CytexLab::Interface::IAllacatorResult AddBlock(UINT64 MinSize, UINT64& OutBlock);

public:
    AllacatorImpl();
    ~AllacatorImpl();

    CytexLab::Interface::IAllacatorResult Init();

    CytexLab::Interface::IAllacatorResult Allocate(CytexLab::Interface::IAllacatorHandle& Out, UINT64 Size) override;
    CytexLab::Interface::IAllacatorResult Free(CytexLab::Interface::IAllacatorHandle Handle) override;
    CytexLab::Interface::IAllacatorResult Reallocate(CytexLab::Interface::IAllacatorHandle Handle, UINT64 NewSize) override;

    LPVOID Resolve(CytexLab::Interface::IAllacatorHandle Handle) override;

    UINT64 GetTotalSize() override;
    UINT64 GetFree() override;
    UINT64 GetUsed() override;
    UINT64 GetTotalAllocates() override;
    UINT64 GetTotalAllocatedBlocks() override;
};