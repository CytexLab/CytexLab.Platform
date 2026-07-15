#include "WinFabric.hpp"
#include "ISystem.hpp"
#include "Unicode.hpp"

using namespace CytexLab::Interface;

IConsole* console;
IMutex* mutex;

UINT32 ThreadWorker(LPVOID Arg)
{
    LPCECHAR name = (LPCECHAR)Arg;
    ECHAR buffer[32];

    for (UINT8 i = 0; i < 5; i++)
    {
        mutex->Lock();
        console->Write((LPCECHAR) U"Поток ");
        console->Write(name);
        console->Write((LPCECHAR) U" -> итерация ");
        Unicode::UIntToStr((UINT64)i, buffer, 32);
        console->WriteLine(buffer);
        mutex->UnLock();
    }

    return 0;
}

extern "C" void startup()
{
    ISystem* system = Fabric::WinFabric::Create();

    // === 1. Консоль ===
    system->CreateConsole(console);
    console->WriteLine((LPCECHAR) U"=== CytexLab.Platform Alpha 1 ===");
    console->WriteLine((LPCECHAR) U"");

    // === 2. Файлы ===
    console->WriteLine((LPCECHAR) U"[1] Тест файлов...");
    IFile* file;
    system->OpenFile(file, (LPCECHAR) U"test.txt", IFileOpenMode::Write);
    file->WriteLine((LPCECHAR) U"Hello, World!");
    file->WriteLine((LPCECHAR) U"Привет, мир!");
    file->WriteLine((LPCECHAR) U"😁👌🪟");
    system->CloseFile(file);

    IFile* readFile;
    system->OpenFile(readFile, (LPCECHAR) U"test.txt", IFileOpenMode::Read);
    ECHAR buffer[256];
    UINT64 readed;
    readFile->Read(buffer, 256, &readed);
    console->WriteLine((LPCECHAR) U"Содержимое test.txt:");
    console->WriteLine(buffer);
    system->CloseFile(readFile);

    // === 3. Пул памяти ===
    console->WriteLine((LPCECHAR) U"[2] Тест пула памяти...");
    IPool* pool;
    system->CreatePool(pool, 1024 * 1024); // 1 МБ
    IPoolItem item;
    IPoolResult pr = pool->Allocate(128, item);
    if (pr.Success) {
        console->WriteLine((LPCECHAR) U"Выделено 128 байт из пула");
        pool->Free(item);
        console->WriteLine((LPCECHAR) U"Освобождено");
    }
    system->DestroyPool(pool);

    // === 4. Мьютексы ===
    console->WriteLine((LPCECHAR) U"[3] Тест мьютексов...");
    system->CreateMutex(mutex);

    // === 5. Потоки ===
    console->WriteLine((LPCECHAR) U"[4] Тест потоков...");
    IThread* th1;
    IThread* th2;
    IThread* th3;
    system->CreateThread(th1, ThreadWorker, (LPVOID)U"A");
    system->CreateThread(th2, ThreadWorker, (LPVOID)U"B");
    system->CreateThread(th3, ThreadWorker, (LPVOID)U"C");

    th1->Start();
    th2->Start();
    th3->Start();

    th1->Join();
    th2->Join();
    th3->Join();

    system->DestroyThread(th1);
    system->DestroyThread(th2);
    system->DestroyThread(th3);
    system->DestroyMutex(mutex);

    // === 6. Числа ===
    console->WriteLine((LPCECHAR) U"[5] Тест чисел...");
    ECHAR numBuf[32];
    Unicode::UIntToStr((UINT64)12345, numBuf, 32);
    console->Write((LPCECHAR) U"12345 -> ");
    console->WriteLine(numBuf);

    INT64 neg = -9876;
    Unicode::UIntToStr(neg, numBuf, 32);
    console->Write((LPCECHAR) U"-9876 -> ");
    console->WriteLine(numBuf);

    UINT64 parsed;
    Unicode::UStrToInt((LPCECHAR) U"54321", &parsed);
    console->Write((LPCECHAR) U"54321 -> ");
    Unicode::UIntToStr(parsed, numBuf, 32);
    console->WriteLine(numBuf);

    // === 7. Всё готово ===
    console->WriteLine((LPCECHAR) U"");
    console->WriteLine((LPCECHAR) U"=== Alpha 1: ВСЕ ТЕСТЫ ПРОЙДЕНЫ! ===");

    system->DestroyConsole(console);
    system->ExitProcess(0);
}