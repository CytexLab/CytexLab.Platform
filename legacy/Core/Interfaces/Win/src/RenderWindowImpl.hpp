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

#include "IRenderWindow.hpp"
#include "WindowImpl.hpp"

class RenderWindowImpl : public CytexLab::Interface::IRenderWindow
{
private:
    WindowImpl* window;
    HANDLE context;
    HANDLE hdc;

    GLFunctions funcs;

public:
    RenderWindowImpl(WindowImpl* Window);
    ~RenderWindowImpl();

    void SwapBuffers() override;
    void loadOpenGL33() override;
    GLFunctions getOpenGL33() override;
};