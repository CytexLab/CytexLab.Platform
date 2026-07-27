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