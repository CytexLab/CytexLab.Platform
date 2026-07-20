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

    IAllocator* allocator;
    system->CreateAllocator(allocator);

    String str1(allocator);
    String str2(allocator);
    String str3(allocator);

    str1 = U"Привет, мир!";
    str2 += str1; str2 += U" Hello, World!";
    str3 += str2; str3 += U" 😁🪟";

    Vector<String> vec(allocator);

    vec.PushBack(str1);
    vec.PushBack(str2);
    vec.PushBack(str3);

    Map<String, Vector<String>> map(allocator);

    String key1(allocator);
    key1 = U"First";

    map.Insert(key1, vec);

    Vector<String> out(allocator);
    map.Find(key1, out);

    for (UINT8 i = 0; i < 3; i++)
        console->WriteLine(out[i].GetData());

    system->DestroyConsole(console);
    system->DestroyAllocator(allocator);
    system->ExitProcess(0);
}