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

IConsole* console;
IMutex* mutex;

UINT32 thread(LPVOID Arg)
{
	for (UINT8 i = 0; i < 10; i++)
	{
		mutex->Lock();
		console->WriteLine((LPCECHAR) Arg);
		mutex->UnLock();
	}
		

	return 0;
}

extern "C" void startup()
{
	ISystem* system = Fabric::WinFabric::Create();
	

	system->CreateConsole(console);
	system->CreateMutex(mutex);

	IThread* th1;
	IThread* th2;
	IThread* th3;
	IThread* th4;
	
	system->CreateThread(th1, thread, (LPVOID) U"Thread 1");
	system->CreateThread(th2, thread, (LPVOID) U"Thread 2");
	system->CreateThread(th3, thread, (LPVOID) U"Thread 3");
	system->CreateThread(th4, thread, (LPVOID) U"Thread 4");

	th1->Start();
	th2->Start();
	th3->Start();
	th4->Start();

	th1->Join();
	th2->Join();
	th3->Join();
	th4->Join();

	system->DestroyConsole(console);
	system->DestroyMutex(mutex);
	system->DestroyThread(th1);
	system->DestroyThread(th2);
	system->DestroyThread(th3);
	system->DestroyThread(th4);

	system->ExitProcess(0);
}