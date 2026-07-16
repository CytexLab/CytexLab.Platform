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

	IConsole* console1;
	system->CreateConsole(console1);

	IConsole* console2;
	system->CreateConsole(console2);

	IPipe* server;
	ISystemResult result = system->CreatePipe(server, (LPCECHAR) U"MyTestPipe");

	IPipe* client;
	result = system->OpenPipe(client, (LPCECHAR) U"MyTestPipe");

	server->Connect();

	system->RedirectConsole(console1, server);
	system->RedirectConsole(console2, client);

	console1->WriteLine((LPCECHAR) U"Hello, World! Привет, мир! 🪟😁");

	ECHAR buf[128];

	console2->ReadLine(buf, 128, NULLPTR);

	system->RedirectConsole(console1, NULLPTR);

	console1->WriteLine(buf);

	system->ExitProcess(0);
}