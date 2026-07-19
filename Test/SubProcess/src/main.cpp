/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "SystemFabric.hpp"
#include "ISystem.hpp"

using namespace CytexLab::Interface;

extern "C" void startup()
{
    ISystem* system = Fabric::SystemFabric::Create();

    IPipe* pipe;
    system->OpenPipe(pipe, U"MyTestPipe");

    pipe->Write(U"Hello, World! Subprocess.");

    system->DestroyPipe(pipe);
    system->ExitProcess(0);
}