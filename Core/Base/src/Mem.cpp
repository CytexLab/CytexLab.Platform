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