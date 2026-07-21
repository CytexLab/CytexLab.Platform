/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "Types.hpp"

typedef void (__stdcall * PFNGLCLEARPROC)(UINT32 mask);
typedef void (__stdcall * PFNGLCLEARCOLORPROC)(float red, float green, float blue, float alpha);
typedef void (__stdcall * PFNGLVIEWPORTPROC)(INT32 x, INT32 y, INT32 width, INT32 height);
typedef UINT32 (__stdcall * PFNGLCREATESHADERPROC)(UINT32 type);
typedef void (__stdcall * PFNGLSHADERSOURCEPROC)(UINT32 shader, INT32 count, LPCCHAR* string, const INT32* length);
typedef void (__stdcall * PFNGLCOMPILESHADERPROC)(UINT32 shader);
typedef void (__stdcall * PFNGLGETSHADERIVPROC)(UINT32 shader, UINT32 pname, INT32* params);
typedef void (__stdcall * PFNGLGETSHADERINFOLOGPROC)(UINT32 shader, INT32 bufSize, INT32* length, LPCHAR infoLog);
typedef UINT32 (__stdcall * PFNGLCREATEPROGRAMPROC)(void);
typedef void (__stdcall * PFNGLATTACHSHADERPROC)(UINT32 program, UINT32 shader);
typedef void (__stdcall * PFNGLLINKPROGRAMPROC)(UINT32 program);
typedef void (__stdcall * PFNGLUSEPROGRAMPROC)(UINT32 program);
typedef void (__stdcall * PFNGLGENVERTEXARRAYSPROC)(INT32 n, UINT32* arrays);
typedef void (__stdcall * PFNGLBINDVERTEXARRAYPROC)(UINT32 array);
typedef void (__stdcall * PFNGLGENBUFFERSPROC)(INT32 n, UINT32* buffers);
typedef void (__stdcall * PFNGLBINDBUFFERPROC)(UINT32 target, UINT32 buffer);
typedef void (__stdcall * PFNGLBUFFERDATAPROC)(UINT32 target, INT64 size, LPCVOID data, UINT32 usage);
typedef void (__stdcall * PFNGLVERTEXATTRIBPOINTERPROC)(UINT32 index, INT32 size, UINT32 type, BOOL normalized, INT32 stride, LPCVOID pointer);
typedef void (__stdcall * PFNGLENABLEVERTEXATTRIBARRAYPROC)(UINT32 index);
typedef void (__stdcall * PFNGLDRAWARRAYSPROC)(UINT32 mode, INT32 first, INT32 count);