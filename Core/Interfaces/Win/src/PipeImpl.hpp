/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#pragma once

#include "IPipe.hpp"

struct PipeLinkImpl
{
    HANDLE Write;
    HANDLE Read;
};

class PipeImpl : public CytexLab::Interface::IPipe
{
private:
    HANDLE write;
    HANDLE read;

public:
    PipeImpl(HANDLE Write, HANDLE Read);
    ~PipeImpl();

    CytexLab::Interface::IPipeResult Write(LPCECHAR Str) override;
    CytexLab::Interface::IPipeResult Write(LPCVOID Data, UINT64 Count) override;

    CytexLab::Interface::IPipeResult Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;
    CytexLab::Interface::IPipeResult Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    PipeLinkImpl GetHandles();
};