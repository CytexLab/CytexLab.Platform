#pragma once

#include "IPool.hpp"

#define MAX_ALLOCATES 250

struct PoolBlock
{
    UINT64 Offset;
    UINT64 Size;
};

class PoolImpl : public CytexLab::Interface::IPool
{
private:
    LPVOID base;
    PoolBlock allocated[MAX_ALLOCATES];
    UINT64 total;
    UINT64 used;
    UINT64 free;
    UINT64 alloc;

public:
    PoolImpl(LPVOID Base, UINT64 Size);
    ~PoolImpl();

    LPVOID GetBase();

    CytexLab::Interface::IPoolResult Allocate(UINT64 Size, CytexLab::Interface::IPoolItem& Out) override;
    CytexLab::Interface::IPoolResult Free(CytexLab::Interface::IPoolItem Item) override;

    UINT64 GetTotal() override;
    UINT64 GetFree() override;
    UINT64 GetUsed() override;
};