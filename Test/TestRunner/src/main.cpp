/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemFabric.hpp"
#include "ISystem.hpp"
#include "Unicode.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Map.hpp"

using namespace CytexLab::Interface;
using namespace CytexLab::Containers;

extern "C" void startup()
{
    ISystem* system = Fabric::SystemFabric::Create();

    IWindow* window;
    system->CreateWindow(window, U"CytexVox", 0, 0, 500, 400);

    IRenderWindow* renderWindow;
    system->CreateRenderWindow(renderWindow, window);

    renderWindow->loadOpenGL33();
    GLFunctions glFunctions = renderWindow->getOpenGL33();

    while (window->IsOpen())
    {
        window->Process();

        glFunctions.glClearColor(0, 0, 0, 0.5f);
        glFunctions.glClear(GL_COLOR_BUFFER_BIT);

        renderWindow->SwapBuffers();
    }

    system->DestroyWindow(window);
    system->ExitProcess(0);
}