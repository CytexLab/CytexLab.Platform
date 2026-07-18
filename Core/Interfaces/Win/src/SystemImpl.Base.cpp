/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * CytexLab (c) 2026
 */

#include "SystemImpl.hpp"
#include "WinImports.hpp"

SystemImpl::SystemImpl()
{}

SystemImpl::~SystemImpl()
{}

void SystemImpl::ExitProcess(UINT32 Code)
{
    ::ExitProcess(Code);
}