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

#include "IProcess.hpp"
#include "WinImports.hpp"

class ProcessImpl : public CytexLab::Interface::IProcess
{
private:
    PROCESS_INFORMATION pi;

public:
    ProcessImpl(PROCESS_INFORMATION PI);
    ~ProcessImpl();

    PROCESS_INFORMATION  GetPi();

    void Terminate(UINT32 Code) override;
    void Join() override;
};