/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */


#pragma once

#include "IFile.hpp"

class FileImpl : public CytexLab::Interface::IFile
{
private:
    HANDLE handle;

public:
    FileImpl(HANDLE Handle);
    ~FileImpl();

    HANDLE GetHandle();

    void Write(LPCECHAR Str) override;
    void WriteLine(LPCECHAR Str) override;
    void Read(LPECHAR Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    void Write(LPCVOID Data, UINT64 Size) override;
    void Read(LPVOID Buffer, UINT64 BufferSize, LPUINT64 Readed) override;

    void GetFileSize(LPUINT64 Out) override;
    void Seek(CytexLab::Interface::IFileSeekMode Mode, INT64 Offset, LPUINT64 NewPos) override;
};