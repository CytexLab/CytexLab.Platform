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

	IPipe* server;
	ISystemResult result = system->CreatePipe(server, (LPCECHAR) U"MyTestPipe");

	if (!result.Success)
		system->ExitProcess(1);

	IPipe* client;
	result = system->OpenPipe(client, (LPCECHAR) U"MyTestPipe");

	if (!result.Success)
		system->ExitProcess(2);

	server->Connect();

	server->Write((LPCECHAR) U"Hello, World!");

	ECHAR buf[128];
	client->Read(buf, 128, NULLPTR);

	console->WriteLine(buf);

	system->ExitProcess(0);
}