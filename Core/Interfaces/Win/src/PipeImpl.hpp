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

    void Write(LPCECHAR Str) override;
    void Write(LPCVOID Data, UINT64 Count) override;

    void Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
    void Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    void Connect() override;

    HANDLE GetHandle();
    BOOL IsOwner();
};