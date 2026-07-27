/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
 */


#pragma once

#include "IThread.hpp"

class ThreadImpl : public CytexLab::Interface::IThread
{
private:
    HANDLE handle;
    UINT64 id;

public:
    ThreadImpl(HANDLE hThread, UINT64 id);
    ~ThreadImpl();

    HANDLE GetHandle();

    void Start() override;
    void Join() override;
    void Terminate() override;
    void IsRunning(BOOL& Out) override;
    UINT64 GetID() override;
};