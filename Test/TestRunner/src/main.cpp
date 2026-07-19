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

    IConsole* console;
	system->CreateConsole(console);

    IPipe* pipe;
    system->CreatePipe(pipe, U"MyTestPipe");

    IProcess* process;
    system->CreateProcess(process, U"F:\\CytexLab.Platform\\Dist\\Windows.Debug\\SubProcess.exe");

    pipe->Connect();

    ECHAR buf[128];
    pipe->Read(buf, 128, NULLPTR);

    console->WriteLine(buf);

    system->DestroyProcess(process);
    system->DestroyPipe(pipe);
    system->DestroyConsole(console);
    system->ExitProcess(0);
}