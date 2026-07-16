/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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

    CytexLab::Interface::IPipeResult Write(LPCECHAR Str) override;
    CytexLab::Interface::IPipeResult Write(LPCVOID Data, UINT64 Count) override;

    CytexLab::Interface::IPipeResult Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
    CytexLab::Interface::IPipeResult Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    HANDLE GetHandle();
    BOOL IsOwner();
};