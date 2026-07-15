/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "Types.hpp"

LPVOID operator new(UINT64, LPVOID ptr);
LPVOID operator new[](UINT64, LPVOID ptr);
void operator delete(LPVOID, LPVOID);
void operator delete[](LPVOID, LPVOID);