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

#include "GLFunctionsTypes.hpp"

struct GLFunctions
{
    // 1.1
    PFNGLCLEARPROC glClear;
    PFNGLCLEARCOLORPROC glClearColor;
    PFNGLVIEWPORTPROC glViewport;

    // Шейдеры
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLDELETESHADERPROC glDeleteShader;

    // Программы
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLDETACHSHADERPROC glDetachShader;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLGETPROGRAMIVPROC glGetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
    PFNGLDELETEPROGRAMPROC glDeleteProgram;

    // VAO/VBO
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLBUFFERSUBDATAPROC glBufferSubData;
    PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

    // Отрисовка
    PFNGLDRAWARRAYSPROC glDrawArrays;
    PFNGLDRAWELEMENTSPROC glDrawElements;

    // Uniform'ы
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLUNIFORM1FPROC glUniform1f;
    PFNGLUNIFORM2FPROC glUniform2f;
    PFNGLUNIFORM3FPROC glUniform3f;
    PFNGLUNIFORM4FPROC glUniform4f;
    PFNGLUNIFORM1IPROC glUniform1i;
    PFNGLUNIFORM2IPROC glUniform2i;
    PFNGLUNIFORM3IPROC glUniform3i;
    PFNGLUNIFORM4IPROC glUniform4i;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

    // Текстуры
    PFNGLGENTEXTURESPROC glGenTextures;
    PFNGLBINDTEXTUREPROC glBindTexture;
    PFNGLTEXIMAGE2DPROC glTexImage2D;
    PFNGLTEXPARAMETERIPROC glTexParameteri;
    PFNGLTEXPARAMETERFPROC glTexParameterf;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLDELETETEXTURESPROC glDeleteTextures;

    // Framebuffer'ы
    PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
    PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

    // Состояние
    PFNGLENABLEPROC glEnable;
    PFNGLDISABLEPROC glDisable;
    PFNGLDEPTHFUNCPROC glDepthFunc;
    PFNGLDEPTHMASKPROC glDepthMask;
    PFNGLBLENDFUNCPROC glBlendFunc;
    PFNGLCULLFACEPROC glCullFace;
    PFNGLFRONTFACEPROC glFrontFace;

    // WGL
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
};

// Буферы
#define GL_COLOR_BUFFER_BIT         0x00004000
#define GL_DEPTH_BUFFER_BIT         0x00000100
#define GL_STENCIL_BUFFER_BIT       0x00000400

// Типы примитивов
#define GL_TRIANGLES                0x0004
#define GL_TRIANGLE_STRIP           0x0005
#define GL_TRIANGLE_FAN             0x0006
#define GL_LINES                    0x0001
#define GL_LINE_STRIP               0x0003
#define GL_POINTS                   0x0000

// Шейдеры
#define GL_VERTEX_SHADER            0x8B31
#define GL_FRAGMENT_SHADER          0x8B30
#define GL_GEOMETRY_SHADER          0x8DD9

// Статусы компиляции/линковки
#define GL_COMPILE_STATUS           0x8B81
#define GL_LINK_STATUS              0x8B82
#define GL_INFO_LOG_LENGTH          0x8B84

// Буферы (VBO/EBO)
#define GL_ARRAY_BUFFER             0x8892
#define GL_ELEMENT_ARRAY_BUFFER     0x8893
#define GL_STATIC_DRAW              0x88E4
#define GL_DYNAMIC_DRAW             0x88E8
#define GL_STREAM_DRAW              0x88E0

// Типы данных вершин
#define GL_FLOAT                    0x1406
#define GL_INT                      0x1404
#define GL_UNSIGNED_INT             0x1405
#define GL_UNSIGNED_BYTE            0x1401
#define GL_BYTE                     0x1400
#define GL_SHORT                    0x1402
#define GL_UNSIGNED_SHORT           0x1403

// VAO атрибуты
#define GL_FALSE                    0
#define GL_TRUE                     1

// Текстуры
#define GL_TEXTURE_2D               0x0DE1
#define GL_TEXTURE0                 0x84C0
#define GL_TEXTURE1                 0x84C1
#define GL_TEXTURE2                 0x84C2
#define GL_TEXTURE_MIN_FILTER       0x2801
#define GL_TEXTURE_MAG_FILTER       0x2800
#define GL_TEXTURE_WRAP_S           0x2802
#define GL_TEXTURE_WRAP_T           0x2803
#define GL_NEAREST                  0x2600
#define GL_LINEAR                   0x2601
#define GL_NEAREST_MIPMAP_NEAREST   0x2700
#define GL_LINEAR_MIPMAP_LINEAR     0x2703
#define GL_CLAMP_TO_EDGE            0x812F
#define GL_REPEAT                   0x2901
#define GL_RGBA                     0x1908
#define GL_RGB                      0x1907
#define GL_RGBA8                    0x8058
#define GL_RGB8                     0x8051
#define GL_UNSIGNED_BYTE            0x1401

// Framebuffer'ы
#define GL_FRAMEBUFFER              0x8D40
#define GL_COLOR_ATTACHMENT0        0x8CE0
#define GL_DEPTH_ATTACHMENT         0x8D00
#define GL_FRAMEBUFFER_COMPLETE     0x8CD5

// Состояние рендера (glEnable/glDisable)
#define GL_DEPTH_TEST               0x0B71
#define GL_BLEND                    0x0BE2
#define GL_CULL_FACE                0x0B44
#define GL_SCISSOR_TEST             0x0C11

// Функции глубины/смешивания
#define GL_LESS                     0x0201
#define GL_LEQUAL                   0x0203
#define GL_GREATER                  0x0204
#define GL_EQUAL                    0x0202
#define GL_ALWAYS                   0x0207
#define GL_NEVER                    0x0200
#define GL_SRC_ALPHA                0x0302
#define GL_ONE_MINUS_SRC_ALPHA      0x0303
#define GL_ONE                      0x0001
#define GL_ZERO                     0x0000

// Cull face
#define GL_FRONT                    0x0404
#define GL_BACK                     0x0405
#define GL_FRONT_AND_BACK           0x0408
#define GL_CW                       0x0900
#define GL_CCW                      0x0901

// WGL
#define WGL_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB       0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB        0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB    0x00000001
#define WGL_CONTEXT_FLAGS_ARB               0x2094
#define WGL_CONTEXT_DEBUG_BIT_ARB           0x00000001