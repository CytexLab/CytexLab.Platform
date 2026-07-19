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

    UINT64 args;
    ISystemResult result = system->GetArgs(&args);

    ECHAR str1[256];
    ECHAR str2[256];
    ECHAR str3[256];

    LPECHAR buf[3] = {str1, str2, str3};

    ISystemResult result2 = system->GetArgv(buf);

    for (UINT64 i = 0; i < args; i++)
    {
        console->WriteLine(&buf[i][0]);
    }

    system->DestroyConsole(console);
    system->ExitProcess(0);
}