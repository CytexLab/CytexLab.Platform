#pragma once

#include "Types.hpp"

LPVOID operator new(UINT64, LPVOID ptr);
LPVOID operator new[](UINT64, LPVOID ptr);
void operator delete(LPVOID, LPVOID);
void operator delete[](LPVOID, LPVOID);