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

#include "IWindow.hpp"

class WindowImpl : public CytexLab::Interface::IWindow
{
private:
    HANDLE hWindow;
    BOOL isOpen;
    UINT64 width, height;

public:
    WindowImpl(HANDLE Window, UINT64 width, UINT64 height);
    ~WindowImpl();

    HANDLE GetHandle();

    void Process() override;
    BOOL IsOpen() override;
    UINT64 GetWidth() override;
    UINT64 GetHeight() override;
};