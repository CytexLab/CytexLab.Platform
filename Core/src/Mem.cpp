/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
 */

#include "Mem.hpp"

__attribute__((target_clones("default,sse4.2,avx,avx2"))) void memcpy(LPVOID To, LPCVOID From, UINT64 Count)
{
    __builtin_memcpy(To, From, Count);
}

__attribute__((target_clones("default,sse4.2,avx,avx2"))) void memset(LPVOID To, UINT8 Byte, UINT64 Count)
{
    __builtin_memset(To, Byte, Count);
}

__attribute__((target_clones("default,sse4.2,avx,avx2"))) void memmove(LPVOID To, LPCVOID From, UINT64 Count)
{
    __builtin_memmove(To, From, Count);
}

__attribute__((target_clones("default,sse4.2,avx,avx2")))
BOOL
memcmp(LPCVOID Mem1, LPCVOID Mem2, UINT64 Count)
{
    if (__builtin_memcmp(Mem1, Mem2, Count) == 0)
        return TRUE;
    else
        return FALSE;
}
