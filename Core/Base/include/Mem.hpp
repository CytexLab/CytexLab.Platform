#pragma once

#include "Types.hpp"

extern "C"
{
    void memset(LPVOID Source, UINT8 Value, UINT64 Count);
    void memcpy(LPVOID To, LPCVOID From, UINT64 Count);
}