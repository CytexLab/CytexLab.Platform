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

void Check(IConsole* Console, LPCECHAR Name, BOOL Condition)
{
    Console->Write(Name);
    Console->WriteLine(Condition ? (LPCECHAR) U" - OK" : (LPCECHAR) U" - FAIL");
}

extern "C" void startup()
{
    ISystem* system = Fabric::WinFabric::Create();
    IConsole* console;
	system->CreateConsole(console);

    IAllacator* allacator;
    system->CreateAllacator(allacator);

    // 1. Базовая аллокация + запись/чтение
    IAllacatorHandle h1;
    allacator->Allocate(h1, 5);
    LPUINT8 p1 = (LPUINT8) allacator->Resolve(h1);

    p1[0] = 0; p1[1] = 5; p1[2] = 8; p1[3] = 10; p1[4] = 5;

    Check(console, (LPCECHAR) U"Basic write/read", p1[3] == 10);

    // 2. Создаём фрагментацию: 5 кусков по 100 байт, освобождаем через один
    IAllacatorHandle frag[5];

    for (UINT64 i = 0; i < 5; i++)
        allacator->Allocate(frag[i], 100);

    allacator->Free(frag[1]);
    allacator->Free(frag[3]);

    // 3. Запрос 250 байт - подряд такой дыры нет (макс дыра ~100),
    // но total free в блоке хватает -> должна сработать дефрагментация
    IAllacatorHandle h2;
    IAllacatorResult result2 = allacator->Allocate(h2, 250);

    Check(console, (LPCECHAR) U"Defrag allocate succeeded", result2.Success);

    // 4. После дефрагментации данные в h1 (он ещё жив) должны остаться целы
    p1 = (LPUINT8) allacator->Resolve(h1);

    BOOL dataIntact = p1[0] == 0 && p1[1] == 5 && p1[2] == 8 && p1[3] == 10 && p1[4] == 5;
    Check(console, (LPCECHAR) U"Data survived defrag", dataIntact);

    // 5. Reallocate на увеличение - данные должны корректно перенестись
    LPUINT8 p2 = (LPUINT8) allacator->Resolve(h2);

    for (UINT64 i = 0; i < 250; i++)
        p2[i] = (UINT8)(i % 256);

    IAllacatorResult growResult = allacator->Reallocate(h2, 1000);
    p2 = (LPUINT8) allacator->Resolve(h2);

    BOOL growOk = growResult.Success;

    for (UINT64 i = 0; i < 250 && growOk; i++)
        if (p2[i] != (UINT8)(i % 256))
            growOk = FALSE;

    Check(console, (LPCECHAR) U"Reallocate grow preserves data", growOk);

    // 6. Reallocate на уменьшение - хвост данных тоже должен остаться целым
    IAllacatorResult shrinkResult = allacator->Reallocate(h2, 10);
    p2 = (LPUINT8) allacator->Resolve(h2);

    BOOL shrinkOk = shrinkResult.Success;

    for (UINT64 i = 0; i < 10 && shrinkOk; i++)
        if (p2[i] != (UINT8)(i % 256))
            shrinkOk = FALSE;

    Check(console, (LPCECHAR) U"Reallocate shrink preserves data", shrinkOk);

    // 7. Провоцируем рост пула: запрашиваем больше, чем есть свободного
    // места в текущем (единственном пока) блоке
    UINT64 blocksBefore = allacator->GetTotalAllocatedBlocks();
    UINT64 hugeSize = allacator->GetFree() + 1;

    IAllacatorHandle h3;
    IAllacatorResult growBlockResult = allacator->Allocate(h3, hugeSize);

    Check(console, (LPCECHAR) U"Pool growth allocate succeeded", growBlockResult.Success);
    Check(console, (LPCECHAR) U"Pool growth added a block", allacator->GetTotalAllocatedBlocks() > blocksBefore);

    // 8. Указатель в новый блок реально пишется/читается
    LPUINT8 p3 = (LPUINT8) allacator->Resolve(h3);
    p3[0] = 42;

    Check(console, (LPCECHAR) U"New block memory writable", p3[0] == 42);

    // 9. Освобождаем всё - суммарный used должен вернуться к 0
    allacator->Free(h1);
    allacator->Free(frag[0]);
    allacator->Free(frag[2]);
    allacator->Free(frag[4]);
    allacator->Free(h2);
    allacator->Free(h3);

    Check(console, (LPCECHAR) U"All freed, used == 0", allacator->GetUsed() == 0);

    system->DestroyAllacator(allacator);
    system->DestroyConsole(console);

    system->ExitProcess(0);
}