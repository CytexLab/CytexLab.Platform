/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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

    CytexLab::Interface::IProcessResult Terminate(UINT32 Code) override;
};