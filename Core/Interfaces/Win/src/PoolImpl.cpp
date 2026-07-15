#include "PoolImpl.hpp"
#include "WinImports.hpp"
#include "Mem.hpp"

PoolImpl::PoolImpl(LPVOID Base, UINT64 Size)
{
    this->base = Base;
    this->total = Size;
    this->free = Size;
    this->used = 0;
    this->alloc = 0;

    for (UINT64 i = 0; i < MAX_ALLOCATES; i++)
    {
        this->allocated[i].Offset = 0;
        this->allocated[i].Size = 0;
    }
}

PoolImpl::~PoolImpl()
{
    
}

LPVOID PoolImpl::GetBase()
{
    return this->base;
}

CytexLab::Interface::IPoolResult PoolImpl::Allocate(UINT64 Size, CytexLab::Interface::IPoolItem& Out)
{
    if (Size == 0)
        return {
            FALSE,
            CytexLab::Interface::IPoolError::InvalidSize,
            0
        };

    if (this->alloc >= MAX_ALLOCATES)
        return {
            FALSE,
            CytexLab::Interface::IPoolError::TooManyAllocations,
            0
        };

    // allocated[] хранится отсортированным по Offset.
    // Ищем первый достаточно большой промежуток между блоками (first-fit).
    UINT64 offset = 0;
    UINT64 insertIndex = this->alloc;

    for (UINT64 i = 0; i < this->alloc; i++)
    {
        UINT64 blockStart = this->allocated[i].Offset;

        if (blockStart - offset >= Size)
        {
            insertIndex = i;
            break;
        }

        offset = blockStart + this->allocated[i].Size;
    }

    if (insertIndex == this->alloc)
    {
        // промежутка между существующими блоками не нашлось -
        // пробуем разместить в хвосте пула
        if (this->total - offset < Size)
            return {
                FALSE,
                CytexLab::Interface::IPoolError::OutOfMemory,
                0
            };
    }

    // сдвигаем хвост массива, чтобы вставить новый блок и сохранить сортировку
    for (UINT64 i = this->alloc; i > insertIndex; i--)
    {
        this->allocated[i] = this->allocated[i - 1];
    }

    this->allocated[insertIndex].Offset = offset;
    this->allocated[insertIndex].Size = Size;
    this->alloc++;

    this->used += Size;
    this->free -= Size;

    Out.Size = Size;
    Out.Pointer = (LPVOID)((UINT8*)this->base + offset);

    return {
        TRUE,
        CytexLab::Interface::IPoolError::None,
        0
    };
}

CytexLab::Interface::IPoolResult PoolImpl::Free(CytexLab::Interface::IPoolItem Item)
{
    if (!Item.Pointer)
        return {
            FALSE,
            CytexLab::Interface::IPoolError::NullPointer,
            0
        };

    UINT64 offset = (UINT64)((UINT8*)Item.Pointer - (UINT8*)this->base);

    for (UINT64 i = 0; i < this->alloc; i++)
    {
        if (this->allocated[i].Offset == offset && this->allocated[i].Size == Item.Size)
        {
            this->used -= this->allocated[i].Size;
            this->free += this->allocated[i].Size;

            // убираем блок из массива, сдвигая хвост, сохраняя сортировку
            for (UINT64 j = i; j < this->alloc - 1; j++)
            {
                this->allocated[j] = this->allocated[j + 1];
            }

            this->alloc--;

            return {
                TRUE,
                CytexLab::Interface::IPoolError::None,
                0
            };
        }
    }

    return {
        FALSE,
        CytexLab::Interface::IPoolError::NotFound,
        0
    };
}

UINT64 PoolImpl::GetTotal()
{
    return this->total;
}

UINT64 PoolImpl::GetFree()
{
    return this->free;
}

UINT64 PoolImpl::GetUsed()
{
    return this->used;
}