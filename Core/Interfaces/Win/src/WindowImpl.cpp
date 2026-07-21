/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "WindowImpl.hpp"
#include "WinImports.hpp"

WindowImpl::WindowImpl(HANDLE Window, UINT64 Width, UINT64 Height)
{
    this->hWindow = Window;
    this->isOpen = TRUE;
    this->width = Width;
    this->height = Height;
}

WindowImpl::~WindowImpl()
{

}

HANDLE WindowImpl::GetHandle()
{
    return this->hWindow;
}

void WindowImpl::Process()
{
    MSG msg;

    while (::PeekMessageW(&msg, NULLPTR, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) {
            this->isOpen = FALSE;
            return;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }
}

BOOL WindowImpl::IsOpen()
{
    return this->isOpen;
}

UINT64 WindowImpl::GetHeight()
{
    return this->height;
}

UINT64 WindowImpl::GetWidth()
{
    return this->width;
}