/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "Mem.hpp"

extern "C"
{
    void memset(LPVOID Source, UINT8 Value, UINT64 Count)
    {
        for (UINT64 i = 0; i < Count; i++)
            ((LPUINT8) Source)[i] = Value;
    }

    void memcpy(LPVOID To, LPCVOID From, UINT64 Count)
    {
        for (UINT64 i = 0; i < Count; i++)
            ((LPUINT8) To)[i] = ((LPUINT8) From)[i];
    }
}