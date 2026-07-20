/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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