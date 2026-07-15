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

    CytexLab::Interface::IConsoleResult WriteConsole(LPCECHAR Str);
    CytexLab::Interface::IConsoleResult WriteFile(LPCECHAR Str);
    CytexLab::Interface::IConsoleResult ReadConsole(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed);
    CytexLab::Interface::IConsoleResult ReadFile(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed);

    CytexLab::Interface::IConsoleResult Write(LPCECHAR Str) override;
    CytexLab::Interface::IConsoleResult WriteLine(LPCECHAR Str) override;
    CytexLab::Interface::IConsoleResult ReadLine(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
};