/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "RenderWindowImpl.hpp"
#include "WinImports.hpp"

RenderWindowImpl::RenderWindowImpl(WindowImpl *Window)
{
    this->window = Window;
}

RenderWindowImpl::~RenderWindowImpl()
{
    ::wglMakeCurrent(NULLPTR, NULLPTR);
    ::wglDeleteContext(this->context);
    ::ReleaseDC(this->window->GetHandle(), this->hdc);
}

void RenderWindowImpl::SwapBuffers()
{
    ::SwapBuffers(this->hdc);
}

void RenderWindowImpl::loadOpenGL33()
{
    HANDLE hwnd = this->window->GetHandle();
    this->hdc = ::GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {};

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = 0x00000004 | 0x00000020 | 0x00000001;
    pfd.iPixelType = 0;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = 0;

    INT32 pixelFormat = ::ChoosePixelFormat(hdc, &pfd);
    ::SetPixelFormat(hdc, pixelFormat, &pfd);

    HANDLE tempHglrc = ::wglCreateContext(hdc);
    ::wglMakeCurrent(hdc, tempHglrc);

    typedef HANDLE (__stdcall * PFNWGLCREATECONTEXTATTRIBSARBPROC)(
        HANDLE hDC, HANDLE hShareContext, const INT32* attribList
    );

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)::wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglCreateContextAttribsARB)
        ::ExitProcess(-1);

    ::wglMakeCurrent(NULLPTR, NULLPTR);
    ::wglDeleteContext(tempHglrc);

    INT32 attribs[] = {
        0x2091, 3, // WGL_CONTEXT_MAJOR_VERSION_ARB
        0x2092, 3, // WGL_CONTEXT_MINOR_VERSION_ARB
        0x9126, 0x00000001, // WGL_CONTEXT_PROFILE_MASK_ARB = CORE_PROFILE
        0 // Terminator
    };

    HANDLE hglrc = wglCreateContextAttribsARB(hdc, NULLPTR, attribs);
    ::wglMakeCurrent(hdc, hglrc);

    this->context = hglrc;

    HANDLE opengl32 = ::GetModuleHandleA("opengl32.dll");

    GLFunctions funcs;

    funcs.glClear = (PFNGLCLEARPROC)::GetProcAddress(opengl32, "glClear");
    funcs.glClearColor = (PFNGLCLEARCOLORPROC)::GetProcAddress(opengl32, "glClearColor");
    funcs.glViewport = (PFNGLVIEWPORTPROC)::GetProcAddress(opengl32, "glViewport");
    funcs.glCreateShader = (PFNGLCREATESHADERPROC)::wglGetProcAddress("glCreateShader");
    funcs.glShaderSource = (PFNGLSHADERSOURCEPROC)::wglGetProcAddress("glShaderSource");
    funcs.glCompileShader = (PFNGLCOMPILESHADERPROC)::wglGetProcAddress("glCompileShader");
    funcs.glGetShaderiv = (PFNGLGETSHADERIVPROC)::wglGetProcAddress("glGetShaderiv");
    funcs.glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)::wglGetProcAddress("glGetShaderInfoLog");
    funcs.glCreateProgram = (PFNGLCREATEPROGRAMPROC)::wglGetProcAddress("glCreateProgram");
    funcs.glAttachShader = (PFNGLATTACHSHADERPROC)::wglGetProcAddress("glAttachShader");
    funcs.glLinkProgram = (PFNGLLINKPROGRAMPROC)::wglGetProcAddress("glLinkProgram");
    funcs.glUseProgram = (PFNGLUSEPROGRAMPROC)::wglGetProcAddress("glUseProgram");
    funcs.glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)::wglGetProcAddress("glGenVertexArrays");
    funcs.glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)::wglGetProcAddress("glBindVertexArray");
    funcs.glGenBuffers = (PFNGLGENBUFFERSPROC)::wglGetProcAddress("glGenBuffers");
    funcs.glBindBuffer = (PFNGLBINDBUFFERPROC)::wglGetProcAddress("glBindBuffer");
    funcs.glBufferData = (PFNGLBUFFERDATAPROC)::wglGetProcAddress("glBufferData");
    funcs.glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)::wglGetProcAddress("glVertexAttribPointer");
    funcs.glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)::wglGetProcAddress("glEnableVertexAttribArray");
    funcs.glDrawArrays = (PFNGLDRAWARRAYSPROC)::wglGetProcAddress("glDrawArrays");

    if (!funcs.glClear || !funcs.glClearColor || !funcs.glViewport || !funcs.glCreateShader ||
        !funcs.glShaderSource || !funcs.glCompileShader || !funcs.glGetShaderiv || !funcs.glGetShaderInfoLog ||
        !funcs.glCreateProgram || !funcs.glAttachShader || !funcs.glLinkProgram || !funcs.glUseProgram ||
        !funcs.glGenVertexArrays || !funcs.glBindVertexArray || !funcs.glGenBuffers || !funcs.glBindBuffer ||
        !funcs.glBufferData || !funcs.glVertexAttribPointer || !funcs.glEnableVertexAttribArray ||
        !funcs.glDrawArrays)
        ::ExitProcess(-1);

    this->funcs = funcs;
}

GLFunctions RenderWindowImpl::getOpenGL33()
{
    return this->funcs;
}