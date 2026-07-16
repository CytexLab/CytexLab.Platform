/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "WinFabric.hpp"
#include "ISystem.hpp"

using namespace CytexLab::Interface;

extern "C" void startup()
{
	ISystem* system = Fabric::WinFabric::Create();

	IConsole* console;
	system->CreateConsole(console);

	console->WriteLine(U"Hello, World!");

	system->DestroyConsole(console);
	system->ExitProcess(0);
}