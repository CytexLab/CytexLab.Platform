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