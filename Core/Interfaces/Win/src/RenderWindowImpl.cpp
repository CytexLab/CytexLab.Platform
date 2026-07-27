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

#include "RenderWindowImpl.hpp"
#include "WinImports.hpp"

RenderWindowImpl::RenderWindowImpl(WindowImpl* Window)
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
    // 1. Получаем HDC из окна
    HANDLE hwnd = this->window->GetHandle();
    this->hdc = ::GetDC(hwnd);

    // 2. Выбираем формат пикселей (для временного контекста)
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    INT32 pixelFormat = ::ChoosePixelFormat(this->hdc, &pfd);
    ::SetPixelFormat(this->hdc, pixelFormat, &pfd);

    // 3. Создаём временный контекст OpenGL 1.1
    HANDLE tempHglrc = ::wglCreateContext(this->hdc);
    ::wglMakeCurrent(this->hdc, tempHglrc);

    // 4. Загружаем wglCreateContextAttribsARB
    typedef HANDLE (__stdcall * PFNWGLCREATECONTEXTATTRIBSARBPROC)(
        HANDLE hDC, HANDLE hShareContext, const INT32* attribList
    );

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)::wglGetProcAddress("wglCreateContextAttribsARB");

    if (!wglCreateContextAttribsARB)
        ::ExitProcess(-1);

    // 5. Удаляем временный контекст
    ::wglMakeCurrent(NULLPTR, NULLPTR);
    ::wglDeleteContext(tempHglrc);

    // 6. Создаём Core 3.3 контекст
    INT32 attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    this->context = wglCreateContextAttribsARB(this->hdc, NULLPTR, attribs);
    ::wglMakeCurrent(this->hdc, this->context);

    // 7. Загружаем WGL расширения
    this->funcs.wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)::wglGetProcAddress("wglSwapIntervalEXT");

    // 8. Загружаем OpenGL 1.1 функции через GetProcAddress (opengl32.dll)
    HANDLE opengl32 = ::GetModuleHandleA("opengl32.dll");

    this->funcs.glClear = (PFNGLCLEARPROC)::GetProcAddress(opengl32, "glClear");
    this->funcs.glClearColor = (PFNGLCLEARCOLORPROC)::GetProcAddress(opengl32, "glClearColor");
    this->funcs.glViewport = (PFNGLVIEWPORTPROC)::GetProcAddress(opengl32, "glViewport");

    // 9. Загружаем Core 3.3 функции через wglGetProcAddress

    // Шейдеры
    this->funcs.glCreateShader = (PFNGLCREATESHADERPROC)::wglGetProcAddress("glCreateShader");
    this->funcs.glShaderSource = (PFNGLSHADERSOURCEPROC)::wglGetProcAddress("glShaderSource");
    this->funcs.glCompileShader = (PFNGLCOMPILESHADERPROC)::wglGetProcAddress("glCompileShader");
    this->funcs.glGetShaderiv = (PFNGLGETSHADERIVPROC)::wglGetProcAddress("glGetShaderiv");
    this->funcs.glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)::wglGetProcAddress("glGetShaderInfoLog");
    this->funcs.glDeleteShader = (PFNGLDELETESHADERPROC)::wglGetProcAddress("glDeleteShader");

    // Программы
    this->funcs.glCreateProgram = (PFNGLCREATEPROGRAMPROC)::wglGetProcAddress("glCreateProgram");
    this->funcs.glAttachShader = (PFNGLATTACHSHADERPROC)::wglGetProcAddress("glAttachShader");
    this->funcs.glDetachShader = (PFNGLDETACHSHADERPROC)::wglGetProcAddress("glDetachShader");
    this->funcs.glLinkProgram = (PFNGLLINKPROGRAMPROC)::wglGetProcAddress("glLinkProgram");
    this->funcs.glUseProgram = (PFNGLUSEPROGRAMPROC)::wglGetProcAddress("glUseProgram");
    this->funcs.glGetProgramiv = (PFNGLGETPROGRAMIVPROC)::wglGetProcAddress("glGetProgramiv");
    this->funcs.glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)::wglGetProcAddress("glGetProgramInfoLog");
    this->funcs.glDeleteProgram = (PFNGLDELETEPROGRAMPROC)::wglGetProcAddress("glDeleteProgram");

    // VAO/VBO
    this->funcs.glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)::wglGetProcAddress("glGenVertexArrays");
    this->funcs.glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)::wglGetProcAddress("glBindVertexArray");
    this->funcs.glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)::wglGetProcAddress("glDeleteVertexArrays");
    this->funcs.glGenBuffers = (PFNGLGENBUFFERSPROC)::wglGetProcAddress("glGenBuffers");
    this->funcs.glBindBuffer = (PFNGLBINDBUFFERPROC)::wglGetProcAddress("glBindBuffer");
    this->funcs.glBufferData = (PFNGLBUFFERDATAPROC)::wglGetProcAddress("glBufferData");
    this->funcs.glBufferSubData = (PFNGLBUFFERSUBDATAPROC)::wglGetProcAddress("glBufferSubData");
    this->funcs.glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)::wglGetProcAddress("glDeleteBuffers");
    this->funcs.glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)::wglGetProcAddress("glVertexAttribPointer");
    this->funcs.glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)::wglGetProcAddress("glEnableVertexAttribArray");
    this->funcs.glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)::wglGetProcAddress("glDisableVertexAttribArray");

    // Отрисовка
    this->funcs.glDrawArrays = (PFNGLDRAWARRAYSPROC)::wglGetProcAddress("glDrawArrays");
    this->funcs.glDrawElements = (PFNGLDRAWELEMENTSPROC)::wglGetProcAddress("glDrawElements");

    // Uniform'ы
    this->funcs.glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)::wglGetProcAddress("glGetUniformLocation");
    this->funcs.glUniform1f = (PFNGLUNIFORM1FPROC)::wglGetProcAddress("glUniform1f");
    this->funcs.glUniform2f = (PFNGLUNIFORM2FPROC)::wglGetProcAddress("glUniform2f");
    this->funcs.glUniform3f = (PFNGLUNIFORM3FPROC)::wglGetProcAddress("glUniform3f");
    this->funcs.glUniform4f = (PFNGLUNIFORM4FPROC)::wglGetProcAddress("glUniform4f");
    this->funcs.glUniform1i = (PFNGLUNIFORM1IPROC)::wglGetProcAddress("glUniform1i");
    this->funcs.glUniform2i = (PFNGLUNIFORM2IPROC)::wglGetProcAddress("glUniform2i");
    this->funcs.glUniform3i = (PFNGLUNIFORM3IPROC)::wglGetProcAddress("glUniform3i");
    this->funcs.glUniform4i = (PFNGLUNIFORM4IPROC)::wglGetProcAddress("glUniform4i");
    this->funcs.glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)::wglGetProcAddress("glUniformMatrix4fv");

    // Текстуры
    this->funcs.glGenTextures = (PFNGLGENTEXTURESPROC)::wglGetProcAddress("glGenTextures");
    this->funcs.glBindTexture = (PFNGLBINDTEXTUREPROC)::wglGetProcAddress("glBindTexture");
    this->funcs.glTexImage2D = (PFNGLTEXIMAGE2DPROC)::wglGetProcAddress("glTexImage2D");
    this->funcs.glTexParameteri = (PFNGLTEXPARAMETERIPROC)::wglGetProcAddress("glTexParameteri");
    this->funcs.glTexParameterf = (PFNGLTEXPARAMETERFPROC)::wglGetProcAddress("glTexParameterf");
    this->funcs.glActiveTexture = (PFNGLACTIVETEXTUREPROC)::wglGetProcAddress("glActiveTexture");
    this->funcs.glDeleteTextures = (PFNGLDELETETEXTURESPROC)::wglGetProcAddress("glDeleteTextures");

    // Framebuffer'ы
    this->funcs.glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)::wglGetProcAddress("glGenFramebuffers");
    this->funcs.glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)::wglGetProcAddress("glBindFramebuffer");
    this->funcs.glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)::wglGetProcAddress("glFramebufferTexture2D");
    this->funcs.glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)::wglGetProcAddress("glCheckFramebufferStatus");
    this->funcs.glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)::wglGetProcAddress("glDeleteFramebuffers");

    // Состояние
    this->funcs.glEnable = (PFNGLENABLEPROC)::wglGetProcAddress("glEnable");
    this->funcs.glDisable = (PFNGLDISABLEPROC)::wglGetProcAddress("glDisable");
    this->funcs.glDepthFunc = (PFNGLDEPTHFUNCPROC)::wglGetProcAddress("glDepthFunc");
    this->funcs.glDepthMask = (PFNGLDEPTHMASKPROC)::wglGetProcAddress("glDepthMask");
    this->funcs.glBlendFunc = (PFNGLBLENDFUNCPROC)::wglGetProcAddress("glBlendFunc");
    this->funcs.glCullFace = (PFNGLCULLFACEPROC)::wglGetProcAddress("glCullFace");
    this->funcs.glFrontFace = (PFNGLFRONTFACEPROC)::wglGetProcAddress("glFrontFace");

    // 10. Проверка — если критическая функция NULL, падаем
    if (!this->funcs.glClear || !this->funcs.glCreateShader || !this->funcs.glCreateProgram ||
        !this->funcs.glGenVertexArrays || !this->funcs.glGenBuffers || !this->funcs.glDrawArrays)
    {
        ::ExitProcess(-1);
    }
}

GLFunctions RenderWindowImpl::getOpenGL33()
{
    return this->funcs;
}