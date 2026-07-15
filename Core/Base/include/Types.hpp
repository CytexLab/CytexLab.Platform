#pragma once

typedef char INT8;
typedef short INT16;
typedef int INT32;
typedef long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;

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

typedef UINT8 CHAR;
typedef UINT16 WCHAR;
typedef UINT32 ECHAR;

typedef CHAR* LPCHAR;
typedef WCHAR* LPWCHAR;
typedef ECHAR* LPECHAR;

typedef const CHAR* LPCCHAR;
typedef const WCHAR* LPCWCHAR;
typedef const ECHAR* LPCECHAR;

typedef INT32 BOOL;
typedef BOOL* LPBOOL;
typedef const BOOL* LPCBOOL;

typedef void* LPVOID;
typedef const void* LPCVOID;
typedef LPVOID HANDLE;

#define TRUE BOOL(1)
#define FALSE BOOL(0)
#define NULLPTR 0
#define UNSET UINT64(-1)

#define INT64_MAX ((INT64)0x7FFFFFFFFFFFFFFFLL)