/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

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