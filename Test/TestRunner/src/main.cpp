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

    IConsole* console;
    system->CreateConsole(console);

    console->WriteLine(U"[ WAIT ] Инициализация движка");

    IWindow* window;
    system->CreateWindow(window, U"CytexVox", 0, 0, 500, 400);

    console->WriteLine(U"[ OK ] Создано окно");

    IRenderWindow* renderWindow;
    system->CreateRenderWindow(renderWindow, window);

    console->WriteLine(U"[ OK ] Создано рендер окно");

    renderWindow->loadOpenGL33();
    GLFunctions glFunctions = renderWindow->getOpenGL33();

    console->WriteLine(U"[ OK ] Созданы функции OpenGL 3.3 Core");
    console->WriteLine(U"[ OK ] Движок инициализирован");

    while (window->IsOpen())
    {
        window->Process();

        glFunctions.glClearColor(0, 0, 0, 0.5f);
        glFunctions.glClear(GL_COLOR_BUFFER_BIT);

        renderWindow->SwapBuffers();
    }

    console->WriteLine(U"[ OK ] Завершение работы");

    system->DestroyRenderWindow(renderWindow);
    system->DestroyWindow(window);
    system->DestroyConsole(console);
    system->ExitProcess(0);
}