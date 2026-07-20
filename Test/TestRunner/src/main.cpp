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

using namespace CytexLab::Interface;

static void PrintResult(IConsole* console, LPCECHAR msg, BOOL success)
{
    console->Write(msg);
    if (success)
        console->WriteLine(U" [OK]");
    else
        console->WriteLine(U" [FAIL]");
}

static void PrintUInt(IConsole* console, LPCECHAR label, UINT64 value)
{
    ECHAR buf[32];
    Unicode::UIntToStr(value, buf, 32);
    console->Write(label);
    console->WriteLine(buf);
}

extern "C" void startup()
{
    ISystem* system = Fabric::SystemFabric::Create();

    IConsole* console;
    system->CreateConsole(console);

    IAllocator* allocator;
    system->CreateAllocator(allocator);

    console->WriteLine(U"=== Allocator Test ===");

    // Test 1: Basic allocation
    console->WriteLine(U"\n[Test 1] Basic allocation");
    IAllocatorHandle h1, h2, h3;
    IAllocatorResult r1 = allocator->Allocate(h1, 64);
    IAllocatorResult r2 = allocator->Allocate(h2, 128);
    IAllocatorResult r3 = allocator->Allocate(h3, 256);

    PrintResult(console, U"Allocate 64 bytes:  ", r1.Success);
    PrintResult(console, U"Allocate 128 bytes: ", r2.Success);
    PrintResult(console, U"Allocate 256 bytes: ", r3.Success);

    PrintUInt(console, U"Total allocates: ", allocator->GetTotalAllocates());
    PrintUInt(console, U"Total used:      ", allocator->GetUsed());
    PrintUInt(console, U"Total free:      ", allocator->GetFree());

    // Test 2: Resolve pointers
    console->WriteLine(U"\n[Test 2] Resolve pointers");
    LPVOID p1 = allocator->Resolve(h1);
    LPVOID p2 = allocator->Resolve(h2);
    LPVOID p3 = allocator->Resolve(h3);

    // Write magic numbers to verify memory is valid
    if (p1) *(LPUINT64)p1 = 0xDEADBEEF;
    if (p2) *(LPUINT64)p2 = 0xCAFEBABE;
    if (p3) *(LPUINT64)p3 = 0xBADC0FFE;

    PrintResult(console, U"Write to p1: ", p1 != NULLPTR);
    PrintResult(console, U"Write to p2: ", p2 != NULLPTR);
    PrintResult(console, U"Write to p3: ", p3 != NULLPTR);

    // Test 3: Free middle block (creates hole)
    console->WriteLine(U"\n[Test 3] Free middle block");
    IAllocatorResult fr = allocator->Free(h2);
    PrintResult(console, U"Free h2 (128 bytes): ", fr.Success);
    PrintUInt(console, U"Total allocates after free: ", allocator->GetTotalAllocates());
    PrintUInt(console, U"Total used after free:      ", allocator->GetUsed());

    // Test 4: Allocate into hole (should trigger defragmentation if needed)
    console->WriteLine(U"\n[Test 4] Allocate into freed space");
    IAllocatorHandle h4;
    IAllocatorResult r4 = allocator->Allocate(h4, 64); // Fits into hole
    PrintResult(console, U"Allocate 64 into hole: ", r4.Success);
    PrintUInt(console, U"Total allocates: ", allocator->GetTotalAllocates());

    // Test 5: Allocate larger than hole (forces defragmentation)
    console->WriteLine(U"\n[Test 5] Force defragmentation");
    IAllocatorHandle h5;
    IAllocatorResult r5 = allocator->Allocate(h5, 200); // Should fit after defrag
    PrintResult(console, U"Allocate 200 (defrag): ", r5.Success);
    PrintUInt(console, U"Total used: ", allocator->GetUsed());

    // Test 6: Reallocate
    console->WriteLine(U"\n[Test 6] Reallocate");
    IAllocatorResult r6 = allocator->Reallocate(h1, 512);
    PrintResult(console, U"Realloc h1 to 512: ", r6.Success);
    PrintUInt(console, U"Total used after realloc: ", allocator->GetUsed());

    // Test 7: Resolve after realloc (old handle invalid, h1 updated)
    console->WriteLine(U"\n[Test 7] Resolve after realloc");
    LPVOID p1_new = allocator->Resolve(h1);
    PrintResult(console, U"Resolve new h1: ", p1_new != NULLPTR);
    if (p1_new)
        *(LPUINT64)p1_new = 0x12345678;

    // Test 8: Invalid operations
    console->WriteLine(U"\n[Test 8] Invalid operations");
    IAllocatorHandle invalid = {999, 64};
    LPVOID p_invalid = allocator->Resolve(invalid);
    PrintResult(console, U"Resolve invalid handle: ", p_invalid == NULLPTR);

    IAllocatorResult r_zero = allocator->Allocate(h1, 0);
    PrintResult(console, U"Allocate 0 bytes:     ", !r_zero.Success); // Should fail

    // Test 9: Stress - many small allocations
    console->WriteLine(U"\n[Test 9] Stress test");
    IAllocatorHandle handles[16];
    BOOL stress_ok = TRUE;
    for (INT32 i = 0; i < 16; i++)
    {
        IAllocatorResult r = allocator->Allocate(handles[i], 32);
        if (!r.Success) stress_ok = FALSE;
    }
    PrintResult(console, U"16x32 bytes alloc: ", stress_ok);
    PrintUInt(console, U"Total allocates: ", allocator->GetTotalAllocates());
    PrintUInt(console, U"Total blocks:    ", allocator->GetTotalAllocatedBlocks());

    // Cleanup
    console->WriteLine(U"\n[Test 10] Cleanup");
    allocator->Free(h1);
    allocator->Free(h3);
    allocator->Free(h4);
    allocator->Free(h5);
    for (INT32 i = 0; i < 16; i++)
        allocator->Free(handles[i]);

    PrintUInt(console, U"Final allocates: ", allocator->GetTotalAllocates());
    PrintUInt(console, U"Final used:      ", allocator->GetUsed());

    console->WriteLine(U"\n=== Test Complete ===");

    system->DestroyConsole(console);
    system->DestroyAllocator(allocator);
    system->ExitProcess(0);
}