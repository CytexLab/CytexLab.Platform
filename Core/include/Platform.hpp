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

#pragma once

#ifdef __clang__

typedef __INT8_TYPE__ INT8;
typedef __INT16_TYPE__ INT16;
typedef __INT32_TYPE__ INT32;
typedef __INT64_TYPE__ INT64;
typedef __UINT8_TYPE__ UINT8;
typedef __UINT16_TYPE__ UINT16;
typedef __UINT32_TYPE__ UINT32;
typedef __UINT64_TYPE__ UINT64;
#else
#error "Unknown compiler. Use Сlang"
#endif

#if __SIZEOF_POINTER__ == 4
#error "CytexLab Platform not supported i686/x86-32"
#elif __SIZEOF_POINTER__ != 4 && __SIZEOF_POINTER__ != 8
#error "Unknown system (Invalid size pointer)"
#endif

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "CytexLab Platform supports only Little-Endian systems (x86_64, ARM64, AMD64)"
#endif

typedef INT8* LPINT8;
typedef INT16* LPINT16;
typedef INT32* LPINT32;
typedef INT64* LPINT64;
typedef UINT8* LPUINT8;
typedef UINT16* LPUINT16;
typedef UINT32* LPUINT32;
typedef UINT64* LPUINT64;

typedef const INT8* LPCINT8;
typedef const INT16* LPCINT16;
typedef const INT32* LPCINT32;
typedef const INT64* LPCINT64;
typedef const UINT8* LPCUINT8;
typedef const UINT16* LPCUINT16;
typedef const UINT32* LPCUINT32;
typedef const UINT64* LPCUINT64;

typedef UINT8 BOOL;
typedef BOOL* LPBOOL;
typedef const BOOL* LPCBOOL;

typedef char CHAR;
typedef wchar_t WCHAR;
typedef char32_t ECHAR;

typedef CHAR* LPCHAR;
typedef WCHAR* LPWCHAR;
typedef ECHAR* LPECHAR;

typedef const CHAR* LPCCHAR;
typedef const WCHAR* LPCWCHAR;
typedef const ECHAR* LPCECHAR;

typedef void* LPVOID;
typedef const void* LPCVOID;

#define UNSET (UINT64)(-1)
#define FALSE BOOL(0)
#define TRUE BOOL(1)

#ifdef CYTEXLAB_PLATFORM_EXPORT
#define CYTEXLAB_API __declspec(dllexport)
#else
#define CYTEXLAB_API __declspec(dllimport)
#endif