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

#include "Types.hpp"

// 1.1 Legacy (через GetProcAddress от opengl32.dll)
typedef void (__stdcall * PFNGLCLEARPROC)(UINT32 mask);
typedef void (__stdcall * PFNGLCLEARCOLORPROC)(float red, float green, float blue, float alpha);
typedef void (__stdcall * PFNGLVIEWPORTPROC)(INT32 x, INT32 y, INT32 width, INT32 height);

// Шейдеры
typedef UINT32 (__stdcall * PFNGLCREATESHADERPROC)(UINT32 type);
typedef void (__stdcall * PFNGLSHADERSOURCEPROC)(UINT32 shader, INT32 count, LPCCHAR* string, const INT32* length);
typedef void (__stdcall * PFNGLCOMPILESHADERPROC)(UINT32 shader);
typedef void (__stdcall * PFNGLGETSHADERIVPROC)(UINT32 shader, UINT32 pname, INT32* params);
typedef void (__stdcall * PFNGLGETSHADERINFOLOGPROC)(UINT32 shader, INT32 bufSize, INT32* length, LPCHAR infoLog);
typedef void (__stdcall * PFNGLDELETESHADERPROC)(UINT32 shader);

// Программы
typedef UINT32 (__stdcall * PFNGLCREATEPROGRAMPROC)(void);
typedef void (__stdcall * PFNGLATTACHSHADERPROC)(UINT32 program, UINT32 shader);
typedef void (__stdcall * PFNGLDETACHSHADERPROC)(UINT32 program, UINT32 shader);
typedef void (__stdcall * PFNGLLINKPROGRAMPROC)(UINT32 program);
typedef void (__stdcall * PFNGLUSEPROGRAMPROC)(UINT32 program);
typedef void (__stdcall * PFNGLGETPROGRAMIVPROC)(UINT32 program, UINT32 pname, INT32* params);
typedef void (__stdcall * PFNGLGETPROGRAMINFOLOGPROC)(UINT32 program, INT32 bufSize, INT32* length, LPCHAR infoLog);
typedef void (__stdcall * PFNGLDELETEPROGRAMPROC)(UINT32 program);

// VAO/VBO/EBO
typedef void (__stdcall * PFNGLGENVERTEXARRAYSPROC)(INT32 n, UINT32* arrays);
typedef void (__stdcall * PFNGLBINDVERTEXARRAYPROC)(UINT32 array);
typedef void (__stdcall * PFNGLDELETEVERTEXARRAYSPROC)(INT32 n, const UINT32* arrays);
typedef void (__stdcall * PFNGLGENBUFFERSPROC)(INT32 n, UINT32* buffers);
typedef void (__stdcall * PFNGLBINDBUFFERPROC)(UINT32 target, UINT32 buffer);
typedef void (__stdcall * PFNGLBUFFERDATAPROC)(UINT32 target, INT64 size, LPCVOID data, UINT32 usage);
typedef void (__stdcall * PFNGLBUFFERSUBDATAPROC)(UINT32 target, INT64 offset, INT64 size, LPCVOID data);
typedef void (__stdcall * PFNGLDELETEBUFFERSPROC)(INT32 n, const UINT32* buffers);
typedef void (__stdcall * PFNGLVERTEXATTRIBPOINTERPROC)(UINT32 index, INT32 size, UINT32 type, BOOL normalized, INT32 stride, LPCVOID pointer);
typedef void (__stdcall * PFNGLENABLEVERTEXATTRIBARRAYPROC)(UINT32 index);
typedef void (__stdcall * PFNGLDISABLEVERTEXATTRIBARRAYPROC)(UINT32 index);

// Отрисовка
typedef void (__stdcall * PFNGLDRAWARRAYSPROC)(UINT32 mode, INT32 first, INT32 count);
typedef void (__stdcall * PFNGLDRAWELEMENTSPROC)(UINT32 mode, INT32 count, UINT32 type, LPCVOID indices);

// Uniform'ы
typedef INT32 (__stdcall * PFNGLGETUNIFORMLOCATIONPROC)(UINT32 program, LPCCHAR name);
typedef void (__stdcall * PFNGLUNIFORM1FPROC)(INT32 location, float v0);
typedef void (__stdcall * PFNGLUNIFORM2FPROC)(INT32 location, float v0, float v1);
typedef void (__stdcall * PFNGLUNIFORM3FPROC)(INT32 location, float v0, float v1, float v2);
typedef void (__stdcall * PFNGLUNIFORM4FPROC)(INT32 location, float v0, float v1, float v2, float v3);
typedef void (__stdcall * PFNGLUNIFORM1IPROC)(INT32 location, INT32 v0);
typedef void (__stdcall * PFNGLUNIFORM2IPROC)(INT32 location, INT32 v0, INT32 v1);
typedef void (__stdcall * PFNGLUNIFORM3IPROC)(INT32 location, INT32 v0, INT32 v1, INT32 v2);
typedef void (__stdcall * PFNGLUNIFORM4IPROC)(INT32 location, INT32 v0, INT32 v1, INT32 v2, INT32 v3);
typedef void (__stdcall * PFNGLUNIFORMMATRIX4FVPROC)(INT32 location, INT32 count, BOOL transpose, const float* value);

// Текстуры
typedef void (__stdcall * PFNGLGENTEXTURESPROC)(INT32 n, UINT32* textures);
typedef void (__stdcall * PFNGLBINDTEXTUREPROC)(UINT32 target, UINT32 texture);
typedef void (__stdcall * PFNGLTEXIMAGE2DPROC)(UINT32 target, INT32 level, INT32 internalformat, INT32 width, INT32 height, INT32 border, UINT32 format, UINT32 type, LPCVOID pixels);
typedef void (__stdcall * PFNGLTEXPARAMETERIPROC)(UINT32 target, UINT32 pname, INT32 param);
typedef void (__stdcall * PFNGLTEXPARAMETERFPROC)(UINT32 target, UINT32 pname, float param);
typedef void (__stdcall * PFNGLACTIVETEXTUREPROC)(UINT32 texture);
typedef void (__stdcall * PFNGLDELETETEXTURESPROC)(INT32 n, const UINT32* textures);

// Framebuffer'ы (опционально)
typedef void (__stdcall * PFNGLGENFRAMEBUFFERSPROC)(INT32 n, UINT32* framebuffers);
typedef void (__stdcall * PFNGLBINDFRAMEBUFFERPROC)(UINT32 target, UINT32 framebuffer);
typedef void (__stdcall * PFNGLFRAMEBUFFERTEXTURE2DPROC)(UINT32 target, UINT32 attachment, UINT32 textarget, UINT32 texture, INT32 level);
typedef UINT32 (__stdcall * PFNGLCHECKFRAMEBUFFERSTATUSPROC)(UINT32 target);
typedef void (__stdcall * PFNGLDELETEFRAMEBUFFERSPROC)(INT32 n, const UINT32* framebuffers);

// Состояние рендера
typedef void (__stdcall * PFNGLENABLEPROC)(UINT32 cap);
typedef void (__stdcall * PFNGLDISABLEPROC)(UINT32 cap);
typedef void (__stdcall * PFNGLDEPTHFUNCPROC)(UINT32 func);
typedef void (__stdcall * PFNGLDEPTHMASKPROC)(BOOL flag);
typedef void (__stdcall * PFNGLBLENDFUNCPROC)(UINT32 sfactor, UINT32 dfactor);
typedef void (__stdcall * PFNGLCULLFACEPROC)(UINT32 mode);
typedef void (__stdcall * PFNGLFRONTFACEPROC)(UINT32 mode);

// WGL расширения
typedef BOOL (__stdcall * PFNWGLSWAPINTERVALEXTPROC)(INT32 interval);