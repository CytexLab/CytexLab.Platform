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

void memcpy(LPVOID To, LPCVOID From, UINT64 Count)
{
    __asm__ volatile (
        "rep movsb"
        : "+D"(To), "+S"(From), "+c"(Count)
        :
        : "memory"
    );
}

void memset(LPVOID To, UINT8 Byte, UINT64 Count)
{
    __asm__ volatile (
        "rep stosb"
        : "+D"(To), "+c"(Count)
        : "a"(Byte)
        : "memory"
    );
}

void memmove(LPVOID To, LPCVOID From, UINT64 Count)
{
    __asm__ volatile (
        "cmp %0, %1\n\t"
        "jae 1f\n\t"          // Если To >= From, используем обычный rep movsb
        "mov %2, %%rcx\n\t"
        "lea 0x1(%%rsi,%%rcx,1), %%rsi\n\t"
        "lea 0x1(%%rdi,%%rcx,1), %%rdi\n\t"
        "std\n\t"              // Направление назад
        "rep movsb\n\t"
        "cld\n\t"              // Вернуть направление вперёд
        "jmp 2f\n\t"
        "1:\n\t"
        "rep movsb\n\t"
        "2:\n\t"
        : "+D"(To), "+S"(From), "+c"(Count)
        :
        : "memory", "cc"
    );
}

BOOL memcmp(LPCVOID Mem1, LPCVOID Mem2, UINT64 Count)
{
    int result = 0;
    __asm__ volatile (
        "repe cmpsb\n\t"
        "mov $0, %0\n\t"
        "je 1f\n\t"
        "mov $1, %0\n\t"      // Не равны
        "1:\n\t"
        : "=r"(result)
        : "D"(Mem1), "S"(Mem2), "c"(Count)
        : "memory", "cc"
    );
    return (result == 0) ? TRUE : FALSE;
}
