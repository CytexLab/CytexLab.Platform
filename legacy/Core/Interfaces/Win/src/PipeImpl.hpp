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

#include "IPipe.hpp"

class PipeImpl : public CytexLab::Interface::IPipe
{
private:
    HANDLE handle;
    BOOL owner;

public:
    PipeImpl(HANDLE Handle, BOOL Owner);
    ~PipeImpl();

    void Write(LPCECHAR Str) override;
    void Write(LPCVOID Data, UINT64 Count) override;

    void Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
    void Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    void Connect() override;

    HANDLE GetHandle();
    BOOL IsOwner();
};