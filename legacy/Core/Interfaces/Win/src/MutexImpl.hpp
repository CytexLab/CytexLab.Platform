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

#include "IMutex.hpp"

class MutexImpl : public CytexLab::Interface::IMutex
{
private:
    HANDLE handle;

public:
    MutexImpl(HANDLE Handle);
    ~MutexImpl();

    HANDLE GetHandle();

    void Lock() override;
    void UnLock() override;
    void TryLock(BOOL& Out) override;
};