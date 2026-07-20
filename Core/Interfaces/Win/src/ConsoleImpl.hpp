/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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