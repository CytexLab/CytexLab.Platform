/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
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

    void Close() override;
    void Process() override;
    BOOL IsOpen() override;
    UINT64 GetWidth() override;
    UINT64 GetHeight() override;
};