/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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

    CytexLab::Interface::IThreadResult Start() override;
    CytexLab::Interface::IThreadResult Join() override;
    CytexLab::Interface::IThreadResult Terminate() override;
    CytexLab::Interface::IThreadResult IsRunning(BOOL& Out) override;
    UINT64 GetID() override;
};