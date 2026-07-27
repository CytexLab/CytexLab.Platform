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

#include "IConsole.hpp"

class ConsoleImpl : public CytexLab::Interface::IConsole
{
private:
    CytexLab::Interface::IConsoleLink link;

public:
    void SetLink(CytexLab::Interface::IConsoleLink Link);

    void WriteConsole(LPCECHAR Str);
    void WriteFile(LPCECHAR Str);
    void ReadConsole(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed);
    void ReadFile(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed);

    void Write(LPCECHAR Str) override;
    void WriteLine(LPCECHAR Str) override;
    void ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
};