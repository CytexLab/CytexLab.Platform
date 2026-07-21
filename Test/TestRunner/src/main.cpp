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
    system->CreateWindow(window, U"Test window", 0, 0, 500, 400);

    while (window->IsOpen())
    {
        window->Process();
    }

    system->ExitProcess(0);
}