#include "Placement.hpp"

LPVOID operator new(UINT64, LPVOID ptr) noexcept
{
    return ptr;
}

LPVOID operator new[](UINT64, LPVOID ptr) noexcept
{
    return ptr;
}

void operator delete(LPVOID, LPVOID) noexcept
{
    // Ничего не делаем
}

void operator delete[](LPVOID, LPVOID) noexcept
{
    // Ничего не делаем
}