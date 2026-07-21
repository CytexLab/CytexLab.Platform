/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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